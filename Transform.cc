
/*#include "Transform.h"

Transform::Transform(MessageQueue *q) : Component(ecs::Transform, netType::TransformNet, q), position_(), //
										velocity_(),													  //
										width_(),														  //
										height_(),														  //
										rotation_()														  //
{
}

Transform::Transform(MessageQueue *q, Vector2D pos, Vector2D vel, double width,
					 double height, double rotation) : Component(ecs::Transform, netType::TransformNet, q), position_(pos), //
													   velocity_(vel),														//
													   width_(width),														//
													   height_(height),														//
													   rotation_(0.0)														//
{
}
void Transform::to_bin()
{
	int size = sizeof(double) * 7 + sizeof(netType);
	alloc_data(size);
	memset(_data, 0, size);
	char *readNext = _data;
	memcpy(readNext, &type_, sizeof(netType));
	readNext += sizeof(netType);
	double readNextDouble = position_.getX();
	memcpy(readNext, &readNextDouble, sizeof(double));
	readNext += sizeof(double);
	readNextDouble = position_.getY();
	memcpy(readNext, &readNextDouble, sizeof(double));
	readNext += sizeof(double);
	readNextDouble = velocity_.getX();
	memcpy(readNext, &readNextDouble, sizeof(double));
	readNext += sizeof(double);
	readNextDouble = velocity_.getY();
	memcpy(readNext, &readNextDouble, sizeof(double));
	readNext += sizeof(double);
	memcpy(readNext, &width_, sizeof(double));
	readNext += sizeof(double);
	memcpy(readNext, &height_, sizeof(double));
	readNext += sizeof(double);
	memcpy(readNext, &rotation_, sizeof(double));
}
int Transform::from_bin(char *bobj)
{
	if (bobj == 0)
	{
		std::cout << "Error on deserialization, empty object received\n";
		return -1;
	}
	int size = sizeof(double) * 7 + sizeof(netType);

	alloc_data(size);

	memcpy(static_cast<void *>(_data), bobj, size);

	return 0;
}
void Transform::deserialize(char *readNext)
{
	//Reconstruir la clase usando el buffer _data
	double readNextDouble;
	memcpy(&readNextDouble, readNext, sizeof(double));
	position_.setX(readNextDouble);
	readNext += sizeof(double);
	memcpy(&readNextDouble, readNext, sizeof(double));
	position_.setY(readNextDouble);
	readNext += sizeof(double);
	memcpy(&readNextDouble, readNext, sizeof(double));
	velocity_.setX(readNextDouble);
	readNext += sizeof(double);
	memcpy(&readNextDouble, readNext, sizeof(double));
	velocity_.setY(readNextDouble);
	readNext += sizeof(double);
	memcpy(&width_, readNext, sizeof(double));
	readNext += sizeof(double);
	memcpy(&height_, readNext, sizeof(double));
	readNext += sizeof(double);
	memcpy(&rotation_, readNext, sizeof(double));
	readNext += sizeof(double);
	memcpy(&type_, readNext, sizeof(netType));
}
char *Transform::Receive(Serializable *msg)
{
	char *aux = Component::Receive(msg);
	deserialize(aux);
	return "";
}
Transform::~Transform()
{
}*/
