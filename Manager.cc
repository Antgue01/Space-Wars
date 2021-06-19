#include "Manager.h"
#include "Entity.h"

EntityManager::EntityManager(SDLGame *game) : game_(game)
{
}

EntityManager::~EntityManager()
{
	for (auto &ent : entities)
	{
		delete ent;
	}
	entities.clear();
}

void EntityManager::update()
{
	for (auto &e : entities)
	{
		if (e != nullptr)
			e->update();
	}
}

void EntityManager::draw()
{
	for (auto &e : entities)
	{
		if (e != nullptr)
			e->draw();
	}
}

void EntityManager::addEntity(Entity *ent)
{
	entities.push_back(ent);	
}
