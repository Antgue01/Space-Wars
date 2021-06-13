#include "MessageQueue.h"
#include "Message.h"
#include "Vessel.h"
#include "DefaultEntity.h"
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
void MessageQueue::flushReceive()
{

    while (!_messagesToReceive.empty())
    {

        for (auto &entity : _entities)
        {
            entity->Receive(_messagesToReceive.front());
        }
        _messagesToReceive.pop();
    }
}
void MessageQueue::init(std::list<Entity *> &entities)
{
    _entities = entities;
}
void MessageQueue::receive()
{
    CountMessage *count = new CountMessage(-1);
    _receiveSocket->recv(*count);
    if (count->getNumMessages() != 0)
        //Cada mensaje envía también el tipo como extra
        for (int i = 0; i < count->getNumMessages(); i++)
        {
            TypeMessage *typem = new TypeMessage();
            _receiveSocket->recv(*typem);

            Serializable *seri = netTypeSwitch(typem->myType_);

            _receiveSocket->recv(*seri);
            _messagesToReceive.push(seri);
        }
    delete count;
}
Serializable *MessageQueue::netTypeSwitch(TypeMessage::NetType t)
{
    switch (t)
    {
    case TypeMessage::NetType::NetVessel:
        return new Vessel();
        break;

    default:
        new DefaultEntity();
        break;
    }
}