#include "NetManager.h"
#include "Entity.h"
#include "MessageQueue.h"
#include "Vessel.h"

void NetManager::init(std::list<Entity*>& ent)
{
    for(auto& e: ent)
    {
        entities.insert(std::pair<int,Entity*>(e->getId(),e));
    }
}

void NetManager::send()
{
    //para cada entidad añade a la cola un mensaje con el tipo y otro con la propia entidad
    for(auto& e : entities)
    {
        TypeMessage *typem = new TypeMessage(e.second->getType());
        msgQueue->addMsg(typem);
        msgQueue->addMsg(e.second);
    }
}

bool NetManager::recieve()
{
    bool e = msgQueue->receive();
    //cogemos cada mensaje de la cola y se lo hacemos llegar a la entidad correspondiente
    while (!msgQueue->getMsgToRecieve().empty() && !e)
    {
        if(msgQueue==nullptr)std::cout<<"NULL\n";
        Entity* e = msgQueue->getMsgToRecieve().front();
        int aux=e->getId();
        auto e2 = entities.find(e->getId());
        if( e2 != entities.end())
        {
            (*e2).second->deliverMsg(e);
        }
        delete e;
        msgQueue->getMsgToRecieve().pop();       
    }

    return e;
}