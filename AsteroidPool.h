#pragma once
#include "Entity.h"
#include "Asteroid.h"
#include <array>
class Bullet;
#include "Vector2D.h"
#define NUM_ASTEROIDS 30
class AsteroidPool
{
private:
    int activeAsteroids;
    std::vector<Asteroid*> myAsteroids;
    int asteroidSize;
    int asteroidIncrease;
    double WinWidth;
    double WinHeight;
    bool isClient_;
    Asteroid* getObj();

public:
    AsteroidPool();
    virtual ~AsteroidPool();
    void generateAsteroids(int n);
    void disableAll();
    void onCollision(Asteroid *a, Bullet *b);
    int getNumOfAsteroids() { return activeAsteroids; }
    vector<Asteroid *> getPool() { return myAsteroids; }
    void init(SDLGame *game = nullptr, EntityManager *mngr = nullptr, MessageQueue *q = nullptr, Resources::TextureId t = Resources::Asteroid, int id = -1, int numAsteroits = 0, bool client = false);

};
