#include "PlasmaPool.h"
#include "Message.h"
#include "SDL_macros.h"
#include "Asteroid.h"
#include "Vessel.h"

PlasmaPool::PlasmaPool(SDLGame *game, EntityManager *mngr, int _id, Resources::TextureId _t, bool client)
{
    for (int i = 0; i < NUM_BULLETS; i++)
    {
        myBullets.push_back(new Bullet(game, mngr, _id + i, client, game->getTextureMngr()->getTexture(_t)));
        myBullets.back()->setInUse(false);
        mngr->addEntity(myBullets.at(i));
    }
}

void PlasmaPool::shoot(Vector2D pos, double speed, double offsetX,  double offsetY, double w, double h)
{
    double angle = 0, delta = 360 / CIRCLE_SIZE;
    Vector2D auxPos, auxVel;
    for (int i = 0; i < CIRCLE_SIZE; i++)
    {

        Bullet *newBullet = getObj();
        //Se busca una bala no en uso y se configura para poder usarla
        if (newBullet != nullptr)
        {
            newBullet->setInUse(true);
            auxPos = pos + Vector2D(offsetX * sin((M_PI * angle) / 180), offsetY * cos((M_PI * angle) / 180));
            auxVel = (auxPos - pos).normalize() * speed;
            newBullet->setPos(auxPos);
            newBullet->setVel(auxVel);
            newBullet->setW(w);
            newBullet->setH(h);
            newBullet->setRot(Vector2D(0, -1).angle(auxVel));
        }
        angle += delta;
    }
}

void PlasmaPool::disableAll()
{
    for (Bullet *a : myBullets)
    {
        a->setInUse(false);
    }
}

const vector<Bullet *> &PlasmaPool::getPool()
{
    return myBullets;
}
Bullet *PlasmaPool::getObj()
{
    int i = 0;
    Bullet *selected = nullptr;
    while (i < myBullets.size() && selected == nullptr)
    {
        if (!myBullets.at(i)->getInUse())
            selected = myBullets.at(i);
        i++;
    }
    return selected;
}

void PlasmaPool::onCollision(Bullet *b, Asteroid *a)
{
    b->setInUse(false);
}
void PlasmaPool::onCollision(Bullet *b, Vessel *ve)
{
    b->setInUse(false);
    ve->LoseLife();
    ve->Reset();
    disableAll();
}
