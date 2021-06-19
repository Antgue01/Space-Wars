#include "BounceBulletsPool.h"
#include "Message.h"
#include "SDL_macros.h"
#include "Asteroid.h"
#include "Vessel.h"

BounceBulletsPool::BounceBulletsPool(SDLGame *game, EntityManager *mngr, int _id, Resources::TextureId _t, bool client)
{
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		myBullets.push_back(new BounceBullet(game, mngr, _id + i, client, game->getTextureMngr()->getTexture(_t)));
		myBullets.back()->setInUse(false);
		mngr->addEntity(myBullets.at(i));
	}
}

void BounceBulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h)
{
	BounceBullet *newBullet = getObj();
	//Se busca una bala no en uso y se configura para poder usarla
	if (newBullet != nullptr)
	{
		newBullet->setInUse(true);
		newBullet->setPos(pos);
		newBullet->setVel(vel);
		newBullet->setW(w);
		newBullet->setH(h);
		newBullet->setRot(Vector2D(0, -1).angle(vel));
	}
}

void BounceBulletsPool::disableAll()
{
	for (BounceBullet *a : myBullets)
	{
		a->setInUse(false);
	}
}

const vector<BounceBullet *> &BounceBulletsPool::getPool()
{
	return myBullets;
}
BounceBullet *BounceBulletsPool::getObj()
{
	int i = 0;
	BounceBullet *selected = nullptr;
	while (i < myBullets.size() && selected == nullptr)
	{
		if (!myBullets.at(i)->getInUse())
			selected = myBullets.at(i);
		i++;
	}
	return selected;
}

void BounceBulletsPool::onCollision(BounceBullet *b, Asteroid *a)
{	
	bounce(b);	
}
void BounceBulletsPool::onCollision(BounceBullet *b, Vessel *ve)
{
	bounce(b);	
}

void BounceBulletsPool::bounce(BounceBullet* b)
{
	if(b->getCanBounce())
	{
		Vector2D v = Vector2D(-1*b->getVel().getY(),b->getVel().getX());

		if(rand()%2==1)
		{
			v = v*-1;
		}

		b->setVel(v);
		b->setRot(Vector2D(0, -1).angle(v));
		b->setCanBounce(false);
	}
	else
	{
		b->setCanBounce(true);
		b->setInUse(false);
	}
}