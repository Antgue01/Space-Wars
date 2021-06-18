#pragma once

#include <iostream>
#include <array>
#include "Manager.h"
#include "SDLGame.h"
#include "Serializable.h"
#include "TypeMessage.h"
class EntityManager;

class Entity : public Serializable
{
public:
	Entity(SDLGame *game, EntityManager *mngr,TypeMessage::NetType t, int id);
	virtual ~Entity();

	EntityManager *getEntityMangr()
	{
		return mngr_;
	}

	inline bool getInUse() { 
		
		return inUse; }
	inline void setInUse(bool v) { inUse = v; }
	inline int getId() { return id_; }
	inline TypeMessage::NetType getType() { return myType_; }

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void deliverMsg(Entity *msg) = 0;

protected:
	SDLGame *game_;
	EntityManager *mngr_;
	TypeMessage::NetType myType_;
	int id_;
	bool inUse;
};
