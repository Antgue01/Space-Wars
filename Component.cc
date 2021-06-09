/*#include "Component.h"
#include "MessageQueue.h"

Component::Component(ecs::CmpId id, netType netType,MessageQueue* q) : entity_(nullptr), //
												 game_(nullptr),   //
												 id_(id),		   //
												 type_(netType),
												 queue_(q)	   //
{
}

char* Component::Receive(Serializable *msg)
{
	netType t;
	char *aux = msg->data();
	memcpy(&t, aux, sizeof(netType));
	if (t == type_)
	{
		aux += sizeof(netType);
	}
	return aux;
}
Component::~Component()
{
}
*/