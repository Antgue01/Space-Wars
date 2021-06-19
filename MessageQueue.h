#pragma once
#include <queue>
#include "Socket.h"
class Message;
#include "Entity.h"
class MessageQueue
#include "TypeMessage.h"
{
//clase que almacena los mensajes a mandar y a recibir y que los manda y recibe
public:
    MessageQueue(Socket* mySocket,Socket* otherSocket,bool imClient):_receiveSocket(mySocket),_sendSocket(otherSocket),client(imClient),exit(false){}
    ~MessageQueue();
    inline void addMsg(Serializable *msg) { _messagesToSend.push(msg); }
    void flushSend();
    bool receive();
  
    inline std::queue<Entity*>& getMsgToRecieve(){return _messagesToReceive;}
    bool exit;
private:
    bool client;
    std::queue<Serializable*> _messagesToSend;
    std::queue<Entity*> _messagesToReceive;
    Socket* _receiveSocket;
    Socket* _sendSocket;
    Entity* netTypeSwitch(TypeMessage::NetType t, bool &exit);
   
};