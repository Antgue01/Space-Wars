#include "Manager.h"
#include "Entity.h"

EntityManager::EntityManager(SDLGame *game) :
		game_(game) {
}

EntityManager::~EntityManager() {
	for (auto &ent : entities)
	{
		delete ent;

	}
	entities.clear();
	
}

void EntityManager::update() {
	for (auto &e : entities) {
		e->update();
	}
}

void EntityManager::draw() {
	for (auto &e : entities) {
		e->draw();
	}
}

void EntityManager::addEntity(Entity* ent) {
	// Entity* e = new Entity(game_,this);
	// std::unique_ptr<Entity> uPtr( /*e*/ent );
	// entities.emplace_back(std::move(uPtr));
	entities.emplace_back(ent);
	// return e;
}
