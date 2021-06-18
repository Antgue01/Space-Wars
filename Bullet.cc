#include "Bullet.h"

Bullet::Bullet(SDLGame *g, EntityManager *mngr, MessageQueue *q, int id, bool client, Texture *text) : Entity(g, mngr, q, TypeMessage::NetBullet, id)
{
	pos = Vector2D(0, 0);
	vel = Vector2D(0, 0);
	rotation = 0;
	w = 5;
	h = 20;
	inUse = false;
	t = text;
	isClient_ = client;
}
void Bullet::update()
{
	if (!isClient_)
		if (inUse)
		{
			Vector2D auxPos = pos + vel;
			if (pos.getY() <= 0 || pos.getY() >= game_->getWindowHeight() || pos.getX() <= 0 || pos.getX() >= game_->getWindowWidth())
			{
				inUse = false;
			}

			pos = auxPos;
		}
}
void Bullet::draw()
{
	if (inUse)
	{
		SDL_Rect dest = {pos.getX(), pos.getY(), w, h};
		t->render(dest, rotation);
	}
}

void Bullet::to_bin()
{
	int size = 2 * sizeof(int) + 3 * sizeof(double);
	alloc_data(size);
	memset(_data, 0, size);
	char *aux = _data;
	memcpy(aux, &id_, sizeof(int));
	aux += sizeof(int);
	int auxBool = (int)inUse;
	memcpy(aux, &auxBool, sizeof(int));
	aux += sizeof(int);
	double auxDouble = pos.getX();
	memcpy(aux, &auxDouble, sizeof(double));
	aux += sizeof(double);
	auxDouble = pos.getY();
	memcpy(aux, &auxDouble, sizeof(double));
	aux += sizeof(double);
	memcpy(aux, &rotation, sizeof(double));
}

int Bullet::from_bin(char *data)
{
	if (data == 0)
	{
		std::cout << "Error on deserialization, empty object received\n";
		return -1;
	}
	int size = 2 * sizeof(int) + 3 * sizeof(double);

	alloc_data(size);

	memcpy(static_cast<void *>(_data), data, size);
	memcpy(&id_, data, sizeof(int));
	data += sizeof(int);
	int auxBool;
	double auxDouble;
	memcpy(&auxBool, data, sizeof(int));
	inUse = (bool)(auxBool);
	data += sizeof(int);
	memcpy(&auxDouble, data, sizeof(double));
	pos.setX(auxDouble);
	data += sizeof(double);
	memcpy(&auxDouble, data, sizeof(double));
	pos.setY(auxDouble);
	data += sizeof(double);
	memcpy(&rotation, data, sizeof(double));
}

void Bullet::deliverMsg(Entity *msg)
{
	if (isClient_)
	{
		Bullet *bu = static_cast<Bullet *>(msg);
		if (bu != nullptr)
		{
			{
				inUse = bu->inUse;
				pos = bu->pos;
				rotation = bu->rotation;
			}
		}
	}
}