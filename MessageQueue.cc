#include "MessageQueue.h"
#include "Message.h"
#include "Vessel.h"
#include "DefaultEntity.h"
#include "Bullet.h"
#include "Asteroid.h"

void MessageQueue::flushSend()
{
    if (!_messagesToSend.empty())
    {

        CountMessage *count = new CountMessage(_messagesToSend.size());
        count->to_bin();
        Message initial(count);
        initial.send(_sendSocket, _receiveSocket);
        delete count;
        while (!_messagesToSend.empty())
        {
            _sendSocket->send(*_messagesToSend.front(), *_receiveSocket);
            _messagesToSend.pop();
        }
    }
}

void MessageQueue::init(std::list<Entity *> &entities)
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        _entities.push_back((*it));
    }
}
void MessageQueue::receive()
{
    CountMessage *count = new CountMessage(-1);
    if (_sendSocket->recv(*count) < 0)
        std::cout << strerror(errno) << '\n';
    if (count->getNumMessages() != 0)
        //Cada mensaje envía también el tipo como extra
        for (int i = 0; i < count->getNumMessages() / 2; i++)
        {
            TypeMessage *typem = new TypeMessage();
            _sendSocket->recv(*typem);

            Entity *seri = netTypeSwitch(typem->myType_);
            delete typem;
            _sendSocket->recv(*seri);
            _messagesToReceive.push(seri);
        }
    delete count;
}
Entity *MessageQueue::netTypeSwitch(TypeMessage::NetType t)
{
    switch (t)
    {
    case TypeMessage::NetType::NetVessel:
    {

        Vessel *a = new Vessel();
        a->getInput().assign(4, false);
        return a;
        break;
    }
    case TypeMessage::NetBullet:
    {
        Bullet* b = new Bullet();
        return b;
        break;
    }
    case TypeMessage::NetAsteroid:
    {
        Asteroid* a = new Asteroid();
        return a;
        break;
    }
    default:
        new DefaultEntity();
        break;
    }
}