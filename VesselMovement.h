#pragma once
#include "Component.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Transform.h"
class VesselMovement : public Component
{
	Transform *tr;
	int limitX, limitY;

public:
	VesselMovement();
	virtual ~VesselMovement() {}
	void init() override;
	void update() override;
	virtual void to_bin() override {}

	virtual int from_bin(char *data) override { return 0; }
};
