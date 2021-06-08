#include "MessageQueue.h"
#include "Message.h"

void MessageQueue::flushSend()
{
    CountMessage count(_messagesToSend.size());
    Message initial(&count, netType::Count);
    initial.send(_receiveSocket, _sendSocket);
    while (!_messagesToSend.empty())
    {
        _sendSocket.send(*_messagesToSend.front(), _receiveSocket);
        _messagesToSend.pop();
    }
}
void MessageQueue::flushReceive()
{

    while (!_messagesToReceive.empty())
    {

        for (auto& entity : _entities)
        {
            entity->Receive(_messagesToReceive.front());
        }
        _messagesToReceive.pop();
    }
}
void MessageQueue::init(std::list<Entity*> &entities)
{
    _entities = entities;
}
void MessageQueue::receive()
{
    CountMessage count(0);
    if (_receiveSocket.recv(count) != 0)
        for (int i = 0; i < count.getNumMessages(); i++)
        {
            Serializable *seri;
            _receiveSocket.recv(*seri);
            _messagesToReceive.push(seri);
        }
}
