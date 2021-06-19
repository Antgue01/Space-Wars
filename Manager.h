#pragma once

#include "SDLGame.h"
#include <list>
class Entity;

class EntityManager
{
public:
	EntityManager(SDLGame *game);
	virtual ~EntityManager();

	void update();
	void draw();

	void addEntity(Entity *entity);
	std::list<Entity*> &getEntities() { return entities; }

private:
	SDLGame *game_;

	std::list<Entity*> entities;
};
