#pragma once

#include "SDLGame.h"

class Entity;

class EntityManager {
public:
	EntityManager(SDLGame* game);
	virtual ~EntityManager();

	void update();
	void draw();
	Entity* addEntity();
	std::vector<std::unique_ptr<Entity>>& getEntities(){return entities;}

private:
	SDLGame* game_;
	std::vector<std::unique_ptr<Entity>> entities;
};
