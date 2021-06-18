#pragma once
#include "SDLGame.h"
#include "MessageQueue.h"
class Vessel;
class AsteroidPool;
class BulletsPool;
class SpaceWars;
class GameLogic
{
public:
    // GameLogic(SDLGame *game = nullptr, EntityManager *mngr = nullptr, int _id = 0, Vessel *v1 = nullptr, Vessel *v2 = nullptr, AsteroidPool *ap = nullptr, BulletsPool *bp = nullptr,
    //           MessageQueue *q = nullptr, bool isServer = false);

    GameLogic(Vessel *v1 , Vessel *v2 , AsteroidPool *ap , BulletsPool *bp,SpaceWars* wars);
    ~GameLogic();

    void update();

private:
    BulletsPool *bulletsPool;
    AsteroidPool *asteroidPool;
    std::vector<Vessel *> vessels;
    SpaceWars* spaceWars;
    bool server;
    void Hit(Vessel* ve);
};