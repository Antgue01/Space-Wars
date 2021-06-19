#pragma once
#include "SDLGame.h"
#include "MessageQueue.h"
class Vessel;
class AsteroidPool;
class BulletsPool;
class Bullet;
class PlasmaPool;
class BounceBulletsPool;

//Gestiona las colisiones entre entidades
class GameLogic
{
public:

    GameLogic(Vessel *v1 , Vessel *v2 , AsteroidPool *ap , BulletsPool *bp,PlasmaPool* pP,BounceBulletsPool* bbp);
    ~GameLogic();

    void update();

private:
    BulletsPool *bulletsPool;
    AsteroidPool *asteroidPool;
    PlasmaPool* plasmaPool;
    BounceBulletsPool* bounceBulletsPool;
    std::vector<Vessel *> vessels;
    bool server;
    void Hit(Vessel* ve,Bullet* b=nullptr);
};