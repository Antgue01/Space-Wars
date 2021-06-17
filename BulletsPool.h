#pragma once
#include "Entity.h"
#include "Bullet.h"
#include "Collisions.h"
#include "SDLGame.h"
#include "MessageQueue.h"
#include "Texture.h"

class BulletsPool : public Entity
{
private:

	// ObjectPool<Bullet, 20> bulletsPool;
    Texture* t;

public:
	BulletsPool(SDLGame *game, EntityManager *mngr, int _id, MessageQueue *q,Texture* _t);
    BulletsPool();
	virtual ~BulletsPool() { t=nullptr; }

    virtual void update();
    virtual void draw();
    virtual void to_bin();
    virtual int from_bin(char *data);
    virtual void deliverMsg(Entity *msg);

	//"Crea" una bala cogiendola del pool
	void shoot(Vector2D pos, Vector2D vel, double w, double h);

	//Desactiva todas las balas que estén en uso
	void disablAll();

	//Comprueba si una bala y un asteroide colisonan
	//void onCollision(Bullet* b, Asteroid* a);

	//Getter del vector de balas de la pool
	const vector<Bullet*>& getPool();
};