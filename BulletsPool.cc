#include "BulletsPool.h"
#include "Message.h"
#include "SDL_macros.h"
#include "Asteroid.h"
#include "Vessel.h"

BulletsPool::BulletsPool(SDLGame *game, EntityManager *mngr, int _id, Resources::TextureId _t, bool client)
{
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		myBullets.push_back(new Bullet(game, mngr, _id + i, client, game->getTextureMngr()->getTexture(_t)));
		myBullets.back()->setInUse(false);
		mngr->addEntity(myBullets.at(i));
	}
}

void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h)
{
	Bullet *newBullet = getObj();
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

void BulletsPool::disableAll()
{
	for (Bullet *a : myBullets)
	{
		a->setInUse(false);
	}
}

const vector<Bullet *> &BulletsPool::getPool()
{
	return myBullets;
}
Bullet *BulletsPool::getObj()
{
	int i = 0;
	Bullet *selected = nullptr;
	while (i < myBullets.size() && selected == nullptr)
	{
		if (!myBullets.at(i)->getInUse())
			selected = myBullets.at(i);
		i++;
	}
	return selected;
}

void BulletsPool::onCollision(Bullet *b, Asteroid *a)
{
	b->setInUse(false);
}
void BulletsPool::onCollision(Bullet *b, Vessel *ve)
{
	b->setInUse(false);
	ve->LoseLife();
	ve->Reset();
	disableAll();
}
