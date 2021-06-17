#include "Asteroid.h"

void Asteroid::SetAngle(double nangle)
{
	angle = nangle;
}
void Asteroid::SetPos(Vector2D npos)
{
	pos = npos;
}
void Asteroid::SetVel(Vector2D nVel)
{
	vel = nVel;
}
void Asteroid::update()
{
	if (!isClient_)
	{

		//Solo si esta en uso lo muevo
		if (inUse)
		{
			pos = pos + vel;
			//EN caso de que se salga por la iquierda
			if (pos.getX() + 25 < 0)
				pos = Vector2D(WinWidth - 50, pos.getY());
			//O por la derecha
			else if (pos.getX() > WinWidth)
				pos = Vector2D(50, pos.getY());

			//En caso de que se salga por arriba
			if (pos.getY() + 25 < 0)
				pos = Vector2D(pos.getX(), WinHeight - 50);
			//O por debajo
			else if (pos.getY() > WinHeight)
				pos = Vector2D(pos.getX(), 50);
			//Lo rotamos
			angle += .5;
		}
	}
}

void Asteroid::draw()
{
	//Consigo el vector de asteroides y dibujo los que están en uso
	if (text->isReady() && inUse)
	{
		SDL_Rect r;
		r.x = pos.getX();
		r.y = pos.getY();
		r.w = width;
		r.h = height;
		text->render(r, angle); // al estar en el archivo solo el asteroide interesa que se dibuje todo
	}
}

void Asteroid::to_bin()
{

	int size = 2 * sizeof(int) + 5 * sizeof(double);
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
	memcpy(aux, &width, sizeof(double));
	aux += sizeof(double);
	memcpy(aux, &height, sizeof(double));
	aux += sizeof(double);
	memcpy(aux, &angle, sizeof(double));
}
int Asteroid::from_bin(char *data)
{
	if (data == 0)
	{
		std::cout << "Error on deserialization, empty object received\n";
		return -1;
	}
	int size = 2 * sizeof(int) + 5 * sizeof(double);

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
	memcpy(&width, data, sizeof(double));
	data += sizeof(double);
	memcpy(&height, data, sizeof(double));
	data += sizeof(double);
	memcpy(&angle, data, sizeof(double));
}
void Asteroid::deliverMsg(Entity *msg)
{
	if (isClient_)
	{
		Asteroid *as = static_cast<Asteroid *>(msg);
		if (as != nullptr)
		{
			{
				inUse = as->inUse;
				pos = as->pos;
				width = as->width;
				height = as->height;
				angle = as->angle;
			}
		}
	}
}