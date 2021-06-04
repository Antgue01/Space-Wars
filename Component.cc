#include "Component.h"

Component::Component(ecs::CmpId id,type type) :
		entity_(nullptr), //
		game_(nullptr), //
		id_(id), //
		type_(type) //
{
}

Component::~Component() {
}
