#pragma once
#include "Entity.h"
#include "Asteroid.h"
#include <array>
class Bullet;
class Vessel;
#include "Vector2D.h"
#define NUM_ASTEROIDS 30
class AsteroidPool
{
private:
    int activeAsteroids;
    std::vector<Asteroid *> myAsteroids;
    int asteroidSize;
    int asteroidIncrease;
    double WinWidth;
    double WinHeight;
    bool isClient_;
    Asteroid *getObj();

public:
    AsteroidPool(SDLGame *game = nullptr, EntityManager *mngr = nullptr, Resources::TextureId t = Resources::Asteroid, int id = -1, int numAsteroits = 0, bool client = false);
    virtual ~AsteroidPool();
    void generateAsteroids(int n);
    void disableAll();
    void onCollision(Asteroid *a, Bullet *b);
     void onCollision(Asteroid *a, Vessel *v);
    int getNumOfAsteroids() { return activeAsteroids; }
    std::vector<Asteroid *> getPool() { return myAsteroids; }
};
