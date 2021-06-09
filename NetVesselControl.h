/*
#pragma once
#include"Component.h"
#include"SDL_macros.h"
#include"Entity.h"
#include"Transform.h"
#include "MessageQueue.h"
class NetVesselControl:public Component
{
private:
	Transform* tr;
	SDL_Keycode right;
	SDL_Keycode left;
	SDL_Keycode up;
	int thrust;
	int speed;
	bool _sends;
	std::vector<bool> pressedKeys;

public:
	NetVesselControl(MessageQueue* q,SDL_Keycode right, SDL_Keycode left, SDL_Keycode up,bool sends);
	virtual ~NetVesselControl(){}
	void init() override;
	void update() override;
	virtual void to_bin() override;
    virtual int from_bin(char * data) override;
	virtual void deserialize(char* data) override;
	virtual char *Receive(Serializable *msg) override;
	std::vector<bool>getKeys(){return pressedKeys;}
};
*/