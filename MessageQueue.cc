#include "MessageQueue.h"
void MessageQueue::flush()
{
    CountMessage count(_messagesToSend.size());
    Message initial(&count, Count);
    initial.send(_socket);
    while (!_messagesToSend.empty())
    {
        _messagesToSend.front()->send(_socket);
        _messagesToSend.pop();
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
    if (_socket.recv(count) != 0)
        for (int i = 0; i < count.getNumMessages(); i++)
        {
            Message* msg;
            _socket.recv(*msg);
            _messagesToReceive.push(msg);
        }
}
