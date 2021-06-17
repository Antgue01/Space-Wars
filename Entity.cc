#include "Entity.h"
#include "MessageQueue.h"
Entity::Entity(SDLGame *game, EntityManager *mngr, MessageQueue *queue,TypeMessage::NetType t,int id) : game_(game), //
																		  mngr_(mngr),
																		  queue_(queue),
																		  myType_(t),
																		  id_(id),
																		  inUse(true) //
{
}
void Entity::Send(Serializable* ser)
{
	
	queue_->addMsg(new TypeMessage(myType_));
	queue_->addMsg(ser);
}
Entity::~Entity()
{
}
