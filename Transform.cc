#include "Transform.h"

Transform::Transform() : Component(ecs::Transform), position_(), //
						 velocity_(),							 //
						 width_(),								 //
						 height_(),								 //
						 rotation_()							 //
{
}

Transform::Transform(Vector2D pos, Vector2D vel, double width,
					 double height, double rotation) : Component(ecs::Transform), position_(pos), //
													   velocity_(vel),							  //
													   width_(width),							  //
													   height_(height),							  //
													   rotation_(0.0)							  //
{
}
void Transform::to_bin()
{
	int size = sizeof(double) * 7;
	alloc_data(size);
	memset(_data, 0, size);
	char *aux = _data;
	double auxDouble = position_.getX();
	memcpy(aux, &auxDouble, sizeof(double));
	aux += sizeof(double);
	auxDouble = position_.getY();
	memcpy(aux, &auxDouble, sizeof(double));
	aux += sizeof(double);
	auxDouble = velocity_.getX();
	memcpy(aux, &auxDouble, sizeof(double));
	aux += sizeof(double);
	auxDouble = velocity_.getY();
	memcpy(aux, &auxDouble, sizeof(double));
	aux += sizeof(double);
	memcpy(aux, &width_, sizeof(double));
	aux += sizeof(double);
	memcpy(aux, &height_, sizeof(double));
	aux += sizeof(double);
	memcpy(aux, &rotation_, sizeof(double));
}
int Transform::from_bin(char *bobj)
{
	if (bobj == 0)
	{
		std::cout << "Error on deserialization, empty object received\n";
		return -1;
	}
	int size = sizeof(double) * 7;

	alloc_data(size);

	memcpy(static_cast<void *>(_data), bobj, size);

	//Reconstruir la clase usando el buffer _data
	char *aux = _data;
	double auxDouble;
	memcpy(&auxDouble, aux, sizeof(double));
	position_.setX(auxDouble);
	aux += sizeof(double);
	memcpy(&auxDouble, aux, sizeof(double));
	position_.setY(auxDouble);
	aux += sizeof(double);
	memcpy(&auxDouble, aux, sizeof(double));
	velocity_.setX(auxDouble);
	aux += sizeof(double);
	memcpy(&auxDouble, aux, sizeof(double));
	velocity_.setY(auxDouble);
	aux += sizeof(double);
	memcpy(&width_, aux, sizeof(double));
	aux += sizeof(double);
	memcpy(&height_, aux, sizeof(double));
	aux += sizeof(double);
	memcpy(&rotation_, aux, sizeof(double));

	return 0;
}
Transform::~Transform()
{
}
