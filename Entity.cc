#include "Entity.h"
#include "MessageQueue.h"
Entity::Entity(SDLGame *game, EntityManager *mngr, MessageQueue *queue,TypeMessage::NetType t) : game_(game), //
																		  mngr_(mngr),
																		  queue_(queue),
																		  myType_(t) //
{
}
void Entity::Send(Serializable* ser)
{
	// to_bin();
	queue_->addMsg(new TypeMessage(myType_));
	queue_->addMsg(ser);
}
Entity::~Entity()
{
}
