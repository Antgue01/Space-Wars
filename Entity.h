#pragma once

#include <iostream>
#include <array>
#include "Manager.h"
#include "SDLGame.h"
#include "Serializable.h"
#include "TypeMessage.h"
class MessageQueue;
class EntityManager;

class Entity:public Serializable
{
public:
	Entity(SDLGame *game, EntityManager *mngr,MessageQueue* queue,TypeMessage::NetType t);
	virtual ~Entity();

	EntityManager *getEntityMangr()
	{
		return mngr_;
	}

	// template <typename T, typename... TArgs>
	// T *addComponent(TArgs &&... mArgs)
	// {
	// 	T *c(new T(std::forward<TArgs>(mArgs)...));
	// 	std::unique_ptr<Component> uPtr(c);
	// 	components_.push_back(std::move(uPtr));
	// 	componentsArray_[c->getId()] = c;
	// 	c->setEntity(this);
	// 	c->setGame(game_);
	// 	c->init();
	// 	return c;
	// }

	// template <typename T>
	// T *getComponent(ecs::CmpIdType id)
	// {
	// 	return static_cast<T *>(componentsArray_[id]);
	// }

	// bool hasComponent(ecs::CmpIdType id)
	// {
	// 	return componentsArray_[id] != nullptr;
	// }
	
	virtual void update() = 0;
	// {
	// 	for (auto &c : components_)
	// 	{
	// 		c->update();
	// 	}
	// }

	virtual void draw() = 0;
	// {
	// 	for (auto &c : components_)
	// 	{
	// 		c->draw();
	// 	}
	// }
	// std::vector<unique_ptr<Component>> &getComponents() { return components_; }
	virtual void Receive(Serializable *msg)=0;

protected:
	SDLGame *game_;
	EntityManager *mngr_;
	MessageQueue* queue_;
	TypeMessage::NetType myType_;
	void Send();

	// std::vector<unique_ptr<Component>> components_;
	// std::array<Component *, ecs::maxComponents> componentsArray_ = {};
};
