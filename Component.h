#pragma once

#include <SDL2/SDL.h>

#include "ecs.h"
#include "SDLGame.h"
#include "Serializable.h"

class Entity;


class Component:public Serializable{
protected:
	Entity* entity_;
	SDLGame* game_;
	ecs::CmpId id_;
public:
	Component(ecs::CmpId id);
	virtual ~Component();

	void setEntity(Entity* entity) {
		entity_ = entity;
	}

	void setGame(SDLGame* game) {
		game_ = game;
	}

	void setId(ecs::CmpId id) {
		id_ = id;
	}

	ecs::CmpId getId() const {
		return id_;
	}

	virtual void init() {
	}
	virtual void update() {
	}
	virtual void draw() {
	}

};

