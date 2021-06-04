#include "MessageQueue.h"
void MessageQueue::flush()
{
    CountMessage count(_messagesToSend.size());
    Message initial(&count, Message::type::Count);
    initial.send(_mySocket,_otherSocket);
    while (!_messagesToSend.empty())
    {
        _messagesToSend.front()->send(_mySocket,_otherSocket);
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
void MessageQueue::receive(Message::type type)
{
    CountMessage count(0);
    if (_mySocket.recv(count) != 0)
        for (int i = 0; i < count.getNumMessages(); i++)
        {
            Serializable* seri;
            Message* msg = new Message(seri,type);
            _mySocket.recv(*seri);
            _messagesToReceive.push(msg);
        }
}
