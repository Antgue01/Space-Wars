#include "BulletsPool.h"
#include "Message.h"
#include "SDL_macros.h"

BulletsPool::BulletsPool(SDLGame *game, EntityManager *mngr, int _id, MessageQueue *q,Texture* _t) : Entity(game, mngr, q, TypeMessage::NetBulletsPool, _id), bulletsPool([](Bullet* o) { return o->GetInUse(); }),t(_t)
{
}

BulletsPool::BulletsPool():Entity(nullptr, nullptr, nullptr, TypeMessage::NetVessel, 2),bulletsPool([](Bullet* o) { return o->GetInUse(); }),t(nullptr)
{

}

void BulletsPool::update()
{
    for(auto& a:bulletsPool.getPool())
	{
		if (a->GetInUse())
		{
           Vector2D pos = a->getPos() + a->getVel();
		   if (pos.getY() <= 0 || pos.getY() >= game_->getWindowHeight() || pos.getX() <= 0 || pos.getX() >= game_->getWindowWidth())
		   {
			   a->SetInUse(false);
		   }

		   a->setPos(pos);
		}		
	}
}

void BulletsPool::draw()
{
    for (auto& a : bulletsPool.getPool())
	{
		if (a->GetInUse())
		{
			SDL_Rect dest = { a->getPos().getX(),a->getPos().getY(),a->getW(),a->getH() };
			t->render(dest, a->getRot());
		}
	}
}

void BulletsPool::to_bin()
{

}

int BulletsPool::from_bin(char *data)
{
    return 0;
}


void BulletsPool::deliverMsg(Entity *msg)
{

}


void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h) {
	Bullet* newBullet = bulletsPool.getObj();
	//Se busca una bala no en uso y se configura para poder usarla
	if (newBullet != nullptr)
	{
       newBullet->SetInUse(true);
	   newBullet->setPos(pos);
	   newBullet->setVel(vel);
	   newBullet->setW(w);
	   newBullet->setH(h);
	   newBullet->setRot(Vector2D(0,-1).angle(vel));
	}
}

void BulletsPool::disablAll() {
	for (Bullet* a : bulletsPool.getPool()) {
		a->SetInUse(false);
	}
}

const vector<Bullet*>& BulletsPool::getPool() {
	return bulletsPool.getPool();
}

/*
void BulletsPool::onCollision(Bullet* b, Asteroid* a) {
	if (Collisions::collidesWithRotation(b->getPos(), b->getW(), b->getH(), b->getRot(), a->getPos(), a->getW(), a->getH() ,a->getRot())) {
		b->SetInUse(false);
	}
}
*/