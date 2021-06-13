#pragma once
#include <queue>

#include "Socket.h"
class Message;
#include "Entity.h"
class MessageQueue
#include "TypeMessage.h"
{

public:
    MessageQueue(Socket* mySocket,Socket* otherSocket):_receiveSocket(mySocket),_sendSocket(otherSocket){}
    inline void addMsg(Serializable *msg) { _messagesToSend.push(msg); }
    void flushSend();
    void flushReceive();
    void receive();
    void init(std::list<Entity*> &entities);

private:
    std::queue<Serializable*> _messagesToSend;
    std::queue<Serializable*> _messagesToReceive;
    Socket* _receiveSocket;
    Socket* _sendSocket;
    Serializable* netTypeSwitch(TypeMessage::NetType t);
    std::list<Entity*> _entities;
};