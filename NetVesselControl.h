#pragma once
#include"Component.h"
#include"SDL_macros.h"
#include"Entity.h"
#include"Transform.h"
class NetVesselControl:public Component
{
private:
	Transform* tr;
	SDL_Keycode right;
	SDL_Keycode left;
	SDL_Keycode up;
	int thrust;
	int speed;
	std::vector<bool> pressedKeys;

public:
	NetVesselControl(SDL_Keycode right, SDL_Keycode left, SDL_Keycode up);
	virtual ~NetVesselControl(){}
	void init() override;
	void update() override;
	virtual void to_bin() override;
    virtual int from_bin(char * data) override;
};