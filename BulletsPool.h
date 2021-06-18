#pragma once
#include "Entity.h"
#include "Bullet.h"
#include "Collisions.h"
#include "SDLGame.h"
#include "Texture.h"
#define NUM_BULLETS 20
class BulletsPool {
private:
    std::vector<Bullet *> myBullets;


public:
	BulletsPool(SDLGame *game, EntityManager *mngr, int _id,Resources::TextureId _t,bool client);
    BulletsPool();
	virtual ~BulletsPool() {  }


	//"Crea" una bala cogiendola del pool
	void shoot(Vector2D pos, Vector2D vel, double w, double h);

	//Desactiva todas las balas que estén en uso
	void disablAll();
	Bullet* getObj();
	//Comprueba si una bala y un asteroide colisonan
	//void onCollision(Bullet* b, Asteroid* a);

	//Getter del vector de balas de la pool
	const vector<Bullet*>& getPool();
};