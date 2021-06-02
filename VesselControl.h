#pragma once
#include"Component.h"
#include"SDL_macros.h"
#include"Entity.h"
#include"InputHandler.h"
#include"Transform.h"
class VesselControl:public Component
{
private:
	Transform* tr;
	SDL_Keycode right;
	SDL_Keycode left;
	SDL_Keycode up;
	int thrust;
	int speed;

public:
	VesselControl(SDL_Keycode right, SDL_Keycode left, SDL_Keycode up);
	virtual ~VesselControl(){}
	void init() override;
	void update() override;
};