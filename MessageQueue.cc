#include "MessageQueue.h"
void MessageQueue::flushSend()
{
    CountMessage count(_messagesToSend.size());
    Message initial(&count, Message::type::Count);
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

        for (Component *component : _components)
        {
            component->Receive(_messagesToReceive.front());
        }
        _messagesToReceive.pop();
    }
}
void MessageQueue::init(std::vector<unique_ptr<Entity>> &entities)
{
    for (auto &entity : entities)
    {
        for (auto &cmp : (*entity).getComponents())
        {
            _components.push_back(cmp.get());
        }
    }
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
