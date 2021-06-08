#pragma once

#include <SDL2/SDL.h>
#include "ecs.h"
#include "SDLGame.h"
class MessageQueue;
#include "Serializable.h"
class Entity;

enum netType
{
	NotSerialize,
	Count,
	vesselMovement,
	TransformNet,
	netVesselControl
};
class Component : public Serializable
{

public:
	Component(ecs::CmpId id, netType netType, MessageQueue *q);
	virtual ~Component();

	void setEntity(Entity *entity)
	{
		entity_ = entity;
	}

	void setGame(SDLGame *game)
	{
		game_ = game;
	}

	void setId(ecs::CmpId id)
	{
		id_ = id;
	}

	ecs::CmpId getId() const
	{
		return id_;
	}

	virtual void init()
	{
	}
	virtual void update()
	{
	}
	virtual void draw()
	{
	}
	virtual void Receive(Serializable *msg);

protected:
	Entity *entity_;
	SDLGame *game_;
	ecs::CmpId id_;
	netType type_;
	MessageQueue *queue_;
};
