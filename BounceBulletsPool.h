#pragma once
#include "Entity.h"
#include "BounceBullet.h"
#include "Collisions.h"
#include "SDLGame.h"
#include "Texture.h"
class Asteroid;
class Vessel;
#define NUM_BULLETS 20
class BounceBulletsPool {
private:
    std::vector<BounceBullet *> myBullets;
	void bounce(BounceBullet* b);

public:
	BounceBulletsPool(SDLGame *game, EntityManager *mngr, int _id,Resources::TextureId _t,bool client);
    BounceBulletsPool();
	virtual ~BounceBulletsPool() {  }


	//"Crea" una bala cogiendola del pool
	void shoot(Vector2D pos, Vector2D vel, double w, double h);

	//Desactiva todas las balas que estén en uso
	void disableAll();
	BounceBullet* getObj();
	//Comprueba si una bala y un asteroide colisonan
	void onCollision(BounceBullet* b, Asteroid* a);
	//Comprueba si una bala y un caza colisonan
	void onCollision(BounceBullet* b, Vessel* ve);

	//Getter del vector de balas de la pool
	const vector<BounceBullet*>& getPool();
};