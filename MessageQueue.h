#pragma once
#include <queue>
#include "Socket.h"
#include "Message.h"
#include "Entity.h"
class MessageQueue
{

public:
    MessageQueue(Socket mySocket,Socket otherSocket):_receiveSocket(mySocket),_sendSocket(otherSocket){}
    inline void addMsg(Serializable *msg) { _messagesToSend.push(msg); }
    void flushSend();
    void flushReceive();
    void receive();
    void init(std::vector<unique_ptr<Entity>> &entities);
    void setComponents(std::vector<Component*>& cmps){_components = cmps;}

private:
    std::queue<Serializable *> _messagesToSend;
    std::queue<Serializable *> _messagesToReceive;
    Socket _receiveSocket;
    Socket _sendSocket;

    std::vector<Component *> _components;
};