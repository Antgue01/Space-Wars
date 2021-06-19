#pragma once
#include <queue>
#include <map>
#include "Socket.h"
class Message;
#include "Entity.h"
class MessageQueue
#include "TypeMessage.h"
{

public:
    MessageQueue(Socket* mySocket,Socket* otherSocket,bool imClient):_receiveSocket(mySocket),_sendSocket(otherSocket),client(imClient),exit(false){}
    ~MessageQueue();
    inline void addMsg(Serializable *msg) { _messagesToSend.push(msg); }
    void flushSend();
    bool receive();
    void init(std::list<Entity*> &entities);
    inline std::queue<Entity*>& getMsgToRecieve(){return _messagesToReceive;}
    bool exit;
private:
    bool client;
    std::queue<Serializable*> _messagesToSend;
    std::queue<Entity*> _messagesToReceive;
    Socket* _receiveSocket;
    Socket* _sendSocket;
    Entity* netTypeSwitch(TypeMessage::NetType t, bool &exit);
    std::list<Entity*> _entities;
};