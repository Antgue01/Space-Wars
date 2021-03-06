#pragma once
#include <map>
#include <list>
class Entity;
class MessageQueue;

class NetManager {
public:
    //clase que recorre las entidades consultando si tienen mensajes que mandar y entregándole a cada uno el suyo
    NetManager(MessageQueue* msgQueue_): msgQueue(msgQueue_){}
    virtual ~NetManager(){}
    void init(std::list<Entity*>& ent);
    void send();
    bool recieve();

private:
    
    std::map<int,Entity*> entities;
    MessageQueue* msgQueue;
};