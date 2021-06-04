#pragma once
#include <queue>
#include "Socket.h"
#include "Message.h"
#include "Entity.h"
class MessageQueue
{

public:
    MessageQueue(Socket mySocket,Socket otherSocket):_mySocket(mySocket),_otherSocket(otherSocket){}
    inline void addMsg(Message *msg) { _messagesToSend.push(msg); }
    void flush();
    void receive(Message::type type);
    void init(std::vector<unique_ptr<Entity>> &entities);
    void setComponents(std::vector<Component*>& cmps){_components = cmps;}

private:
    std::queue<Message *> _messagesToSend;
    std::queue<Message *> _messagesToReceive;
    Socket _mySocket;
    Socket _otherSocket;

    std::vector<Component *> _components;
};