#include "GameLogic.h"
#include "Vessel.h"
#include "AsteroidPool.h"
#include "BulletsPool.h"
#include "PlasmaPool.h"
// GameLogic::GameLogic(SDLGame *game, EntityManager *mngr, int _id, Vessel *v1, Vessel *v2, AsteroidPool *ap, BulletsPool *bp, MessageQueue *q,bool isServer) :
//  Entity(game, mngr, q, TypeMessage::NetGameLogic, _id), server(isServer), bulletsPool(bp),asteroidPool(ap)

// {
//     vessels.push_back(v1);
//     vessels.push_back(v2);
// }
GameLogic::GameLogic(Vessel *v1, Vessel *v2, AsteroidPool *ap, BulletsPool *bp, PlasmaPool *pP) : bulletsPool(bp), asteroidPool(ap), plasmaPool(pP)

{
    vessels.push_back(v1);
    vessels.push_back(v2);
}
void GameLogic::update()
{
    vector<Asteroid *> asteroidsv = asteroidPool->getPool();
    //Recorro todos los asteroides
    for (Asteroid *as : asteroidsv)
    {
        //colision asteroide-bala
        vector<Bullet *> bulletsv = bulletsPool->getPool();
        vector<Bullet *> plasmav = plasmaPool->getPool();
        for (Bullet *b : bulletsv)
        {
            if (b->getInUse() && as->getInUse() && Collisions::collidesWithRotation(b->getPos(), b->getW(), b->getH(), b->getRot(), as->GetPos(), as->GetWidth(), as->GetHeight(), as->GetAngle()))
            {
                bulletsPool->onCollision(b, as);
                asteroidPool->onCollision(as, b);
            }
        }
        for (Bullet *b : plasmav)
        {
            if (b->getInUse() && as->getInUse() && Collisions::collidesWithRotation(b->getPos(), b->getW(), b->getH(), b->getRot(), as->GetPos(), as->GetWidth(), as->GetHeight(), as->GetAngle()))
            {
                bulletsPool->onCollision(b, as);
                asteroidPool->onCollision(as, b);
            }
        }
        for (Vessel *ve : vessels)
        {

            //colision caza-asteroide
            if (as->getInUse() && Collisions::collidesWithRotation(ve->getPos(), ve->getW(), ve->getH(), ve->getRot(), as->GetPos(), as->GetWidth(), as->GetHeight(),
                                                                   as->GetAngle()))
            {
                Hit(ve);
            }
        }
        for (Vessel *ve : vessels)
        {

            // colision con el resto de jugadores
            for (Vessel *ve2 : vessels)
            {
                if (ve->getId() != ve2->getId() && Collisions::collidesWithRotation(ve->getPos(), ve->getW(), ve->getH(), ve->getRot(), ve2->getPos(), ve2->getW(), ve2->getH(),
                                                                                    ve2->getRot()))
                {

                    ve->LoseLife();
                    ve2->LoseLife();
                    ve->Reset();
                    ve2->Reset();
                    plasmaPool->disableAll();
                    asteroidPool->disableAll();
                    bulletsPool->disableAll();
                    if (ve->GetHealth() <= 0 || ve2->GetHealth() <= 0)
                    {
                        SDLGame::instance()->getAudioMngr()->haltMusic();
                        ve->setCanPlay(false);
                        ve2->setCanPlay(false);
                    }

                    else
                    {

                        SDLGame::instance()->getAudioMngr()->pauseMusic();
                        asteroidPool->generateAsteroids(5);
                    }
                }
            }
            //Colision caza-balas
            for (Bullet *b : bulletsv)
            {
                if (b->getInUse() && Collisions::collidesWithRotation(b->getPos(), b->getW(), b->getH(), b->getRot(), ve->getPos(), ve->getW(), ve->getH(), ve->getRot()))
                {
                    Hit(ve);
                }
            }
            for (Bullet *b : plasmav)
            {
                if (b->getInUse() && Collisions::collidesWithRotation(b->getPos(), b->getW(), b->getH(), b->getRot(), ve->getPos(), ve->getW(), ve->getH(), ve->getRot()))
                {
                    Hit(ve);
                }
            }
        }
    }
}

GameLogic::~GameLogic()
{
    bulletsPool = nullptr;
    vessels.clear();
    asteroidPool = nullptr;
}
void GameLogic::Hit(Vessel *ve)
{
    ve->LoseLife();
    asteroidPool->disableAll();
    bulletsPool->disableAll();
    plasmaPool->disableAll();
    ve->Reset();
    if (ve->GetHealth() <= 0)
    {
        SDLGame::instance()->getAudioMngr()->haltMusic();
        for (Vessel *vess : vessels)
        {
            vess->setCanPlay(false);
        }
    }
    else
    {
        SDLGame::instance()->getAudioMngr()->pauseMusic();
        asteroidPool->generateAsteroids(5);
    }
}