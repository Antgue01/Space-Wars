#pragma once
#include <queue>
#include "Socket.h"
#include "Message.h"
#include "Entity.h"
class MessageQueue
{

public:
    inline void addMsg(Message *msg) { _messagesToSend.push(msg); }
    void flush();
    void receive();
    void init(std::vector<unique_ptr<Entity>> &entities);

private:
    std::queue<Message *> _messagesToSend;
    std::queue<Message *> _messagesToReceive;
    Socket _socket;
    std::vector<Component *> _components;
};