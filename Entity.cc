#include "Entity.h"
#include "MessageQueue.h"
Entity::Entity(SDLGame *game, EntityManager *mngr,TypeMessage::NetType t,int id) : game_(game), 
																		  mngr_(mngr),																		  
																		  myType_(t),
																		  id_(id),
																		  inUse(true) 
{
}

Entity::~Entity()
{
}
