#include "MessageQueue.h"
#include "Message.h"
#include "Vessel.h"
#include "DefaultEntity.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "BounceBullet.h"


MessageQueue::~MessageQueue()
{
    while (!_messagesToReceive.empty())
    {
        _messagesToReceive.pop();
    }
    while (!_messagesToSend.empty())
    {
        _messagesToSend.pop();
    }
}

void MessageQueue::flushSend()
{
    if (!_messagesToSend.empty())
    {
        //primero mandamos un mensaje con la cantidad de mensajes que enviaremos
        CountMessage *count = new CountMessage(_messagesToSend.size());
        count->to_bin();
        //hacemos un mensaje con este serializable y lo mandamos
        Message initial(count);
        initial.send(_sendSocket, _receiveSocket);
        delete count;
        while (!_messagesToSend.empty())
        {
            //mandamos todos los mensajes
            _sendSocket->send(*_messagesToSend.front(), *_receiveSocket);
            _messagesToSend.pop();
        }
    }
}
bool MessageQueue::receive()
{
    //primero recibimos cuántos mensajes vienen
    CountMessage *count = new CountMessage(-1);
    if (_sendSocket->recv(*count) < 0)
        std::cout << strerror(errno) << '\n';
    if (count->getNumMessages() != 0)
        //Cada mensaje envía también el tipo como extra, así que realmente hay que procesar n/2 mensajes
        for (int i = 0; i < count->getNumMessages() / 2; i++)
        {
            TypeMessage *typem = new TypeMessage();
            _sendSocket->recv(*typem);

            //creamos una entidad de tipo adecuado para que se deserialize correctamente
            Entity *seri = netTypeSwitch(typem->myType_,exit);
            delete typem;
            if(exit)
            {
                delete seri;
                return true;
            }
            _sendSocket->recv(*seri);
            //llenamos la cola
            _messagesToReceive.push(seri);
        }
    delete count;
    return false;
}
Entity *MessageQueue::netTypeSwitch(TypeMessage::NetType t,bool &exit)
{
    switch (t)
    {
    case TypeMessage::NetType::NetVessel:
    {

        Vessel *a = new Vessel();
        a->getInput().assign(7, false);
        return a;
        break;
    }
    case TypeMessage::NetBullet:
    {
        Bullet *b = new Bullet();
        return b;
        break;
    }
    case TypeMessage::NetAsteroid:
    {
        Asteroid *a = new Asteroid();
        return a;
        break;
    }
    case TypeMessage::NetBounceBullet:
    {
        BounceBullet *a = new BounceBullet();
        return a;
        break;
    }
    case TypeMessage::Logout:
    {
        while (!_messagesToReceive.empty())
        {
            _messagesToReceive.pop();
        }
        while (!_messagesToSend.empty())
        {
            _messagesToSend.pop();
        }
        exit=true;
        return new DefaultEntity();
        break;
    }
    default:
    {
        DefaultEntity *def = new DefaultEntity();
        return def;
        break;
    }
    }
}