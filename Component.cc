#include "Component.h"

Component::Component(ecs::CmpId id, type type) : entity_(nullptr), //
												 game_(nullptr),   //
												 id_(id),		   //
												 type_(type)	   //
{
}

void Component::Receive(Serializable *msg)
{
	type t;
	char *aux = msg->data();
	memcpy(&t, aux, sizeof(type));
	if (t == type_)
	{
		aux += sizeof(type);
		deserialize(aux);
	}
}
Component::~Component()
{
}
