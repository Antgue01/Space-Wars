#pragma once
#include "SDLGame.h"
#include "MessageQueue.h"
class Vessel;
class AsteroidPool;
class BulletsPool;
class Bullet;
class PlasmaPool;
class GameLogic
{
public:
    // GameLogic(SDLGame *game = nullptr, EntityManager *mngr = nullptr, int _id = 0, Vessel *v1 = nullptr, Vessel *v2 = nullptr, AsteroidPool *ap = nullptr, BulletsPool *bp = nullptr,
    //           MessageQueue *q = nullptr, bool isServer = false);

    GameLogic(Vessel *v1 , Vessel *v2 , AsteroidPool *ap , BulletsPool *bp,PlasmaPool* pP);
    ~GameLogic();

    void update();

private:
    BulletsPool *bulletsPool;
    AsteroidPool *asteroidPool;
    PlasmaPool* plasmaPool;
    std::vector<Vessel *> vessels;
    bool server;
    void Hit(Vessel* ve,Bullet* b=nullptr);
};