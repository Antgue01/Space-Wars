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
    MessageQueue(Socket* mySocket,Socket* otherSocket,bool imClient):_receiveSocket(mySocket),_sendSocket(otherSocket),client(imClient){}
    inline void addMsg(Serializable *msg) { _messagesToSend.push(msg); }
    void flushSend();
    void receive();
    void init(std::list<Entity*> &entities);
    inline std::queue<Entity*>& getMsgToRecieve(){return _messagesToReceive;}
private:
    bool client;
    // std::map<TypeMessage::NetType,EntityFactory<Vessel>> typeTranslator;
    std::queue<Serializable*> _messagesToSend;
    std::queue<Entity*> _messagesToReceive;
    Socket* _receiveSocket;
    Socket* _sendSocket;
    Entity* netTypeSwitch(TypeMessage::NetType t);
    std::list<Entity*> _entities;
};