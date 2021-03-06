#pragma once
#include "Entity.h"
#include "Bullet.h"
#include "Collisions.h"
#include "SDLGame.h"
#include "Texture.h"
class Asteroid;
class Vessel;
#define NUM_BULLETS 16
#define CIRCLE_SIZE 4
class PlasmaPool {
private:
    std::vector<Bullet *> myBullets;

public:
	PlasmaPool(SDLGame *game, EntityManager *mngr, int _id,Resources::TextureId _t,bool client);
    PlasmaPool();
	virtual ~PlasmaPool() {  }


	//"Crea" las balas cogiendolas del pool
	void shoot(Vector2D pos,double speed, double offsetX,double offsetY, double w, double h);

	//Desactiva todas las balas que estén en uso
	void disableAll();
	Bullet* getObj();
	//Comprueba si una bala y un asteroide colisonan
	void onCollision(Bullet* b, Asteroid* a);
	//Comprueba si una bala y un caza colisonan
	void onCollision(Bullet* b, Vessel* ve);

	//Getter del vector de balas de la pool
	const vector<Bullet*>& getPool();
};