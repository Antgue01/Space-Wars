#include "AsteroidPool.h"
#include "Bullet.h"
#include "Vessel.h"

using namespace std;
AsteroidPool::AsteroidPool(SDLGame *game, EntityManager *mngr, Resources::TextureId t, int id, int numAsteroits, bool client) : activeAsteroids(0), myAsteroids(), asteroidSize(10), asteroidIncrease(3), isClient_(client)
{
    for (int i = 0; i < NUM_ASTEROIDS; i++)
    {
        myAsteroids.push_back(new Asteroid(game, mngr, id + i, client, game->getTextureMngr()->getTexture(t)));
        myAsteroids.back()->setInUse(false);
        mngr->addEntity(myAsteroids.at(i));
    }
    WinWidth = SDLGame::instance()->getWindowWidth();
    WinHeight = SDLGame::instance()->getWindowHeight();
    generateAsteroids(5);
}

AsteroidPool::~AsteroidPool()
{
    for (Asteroid *i : myAsteroids)
    {
        delete i;
    }
    myAsteroids.clear();
}

void AsteroidPool::generateAsteroids(int n)
{
    if (!isClient_)
    {

        RandomNumberGenerator *r = SDLGame::instance()->getRandGen();
        for (int i = 0; i < n; i++)
        {
            Vector2D pos;
            int horizontal = r->nextInt(0, 2);
            //SI el asteroide es horizontal
            if (horizontal == 0)
            {
                int origen = r->nextInt(0, 2);
                int ancho = r->nextInt(0, WinWidth);
                if (origen == 0)
                {
                    pos.setY(50);
                }
                else
                {
                    pos.setY(WinHeight - 50);
                }
            }

            //Si el asteride es vertical
            else
            {
                int origen = r->nextInt(0, 2);
                int alto = r->nextInt(0, WinWidth);
                pos.setY(alto);
                if (origen == 0)
                {
                    pos.setX(50);
                }
                else
                {
                    pos.setX(WinWidth - 50);
                }
            }
            // Pongo la direccion a una posicion aleatoria en el centro de la pantalla
            Vector2D vel;
            int randomx = r->nextInt(0, 100);
            int randomy = r->nextInt(0, 100);
            vel.setX((((WinWidth / 2) - 50) + randomx) - pos.getX());
            vel.setY((((WinHeight / 2) - 50) + randomy) - pos.getY());
            vel = vel.normalize()*0.5;
            ///////////////////////////////////////////////////////////
            int generacion = r->nextInt(1, 4);
            Asteroid *a = getObj();
            if (a != nullptr)
            {

                a->SetPos(pos);
                a->SetVel(vel);
                a->SetAngle(0);
                a->SetGeneraciones(generacion);
                a->SetWidth(asteroidSize + asteroidIncrease * generacion);
                a->SetHeight(asteroidSize + asteroidIncrease * generacion);
                a->setInUse(true);
                activeAsteroids++;
            }
        }
    }
}

void AsteroidPool::disableAll()
{
    if (!isClient_)
    {

        for (int i = 0; i < myAsteroids.size(); i++)
        {
            myAsteroids.at(i)->setInUse(false);
        }
        activeAsteroids = 0;
    }
}
void AsteroidPool::onCollision(Asteroid *a, Bullet *b)
{
    if (!isClient_)
    {
        // EL asteroide principal desaparece
        a->setInUse(false);
        activeAsteroids--;
        // Se divide si le quedan generaciones
        if (a->GetGenarations() > 0)
        {
            //Pregunto si pueden haber m�s asteroides en el juego
            Asteroid *a1 = getObj();
            if (a1 != nullptr)
            {
                a1->setInUse(true);
                a1->SetGeneraciones(a->GetGenarations() - 1);
                //DImensiones
                a1->SetWidth(asteroidSize + asteroidIncrease * a1->GetGenarations());
                a1->SetHeight(asteroidSize + asteroidIncrease * a1->GetGenarations());
                //VElocidad
                a1->SetVel(a->GetVel().rotate(45));
                a1->SetPos(a->GetPos() + a->GetVel().normalize());
                activeAsteroids++;
            }
            Asteroid *a2 = getObj();
            //Pregunto si puede haber otro asteroide
            if (a2 != nullptr)
            {
                a2->setInUse(true);
                a2->SetGeneraciones(a1->GetGenarations());
                //Dimensiones;
                a2->SetWidth(asteroidSize + asteroidIncrease * a2->GetGenarations());
                a2->SetHeight(asteroidSize + asteroidIncrease * a2->GetGenarations());
                //Velocidad
                a2->SetVel(a1->GetVel().rotate(45));
                a2->SetPos(a1->GetPos() + a2->GetVel().normalize());
                activeAsteroids++;
            }
        }
    }
}


void AsteroidPool::onCollision(Asteroid *a, Vessel *b)
{

    a->SetVel(a->GetVel()*-1);
}

Asteroid *AsteroidPool::getObj()
{
    int i = 0;
    Asteroid *selected = nullptr;
    while (i < myAsteroids.size() && selected == nullptr)
    {
        if (!myAsteroids.at(i)->getInUse())
            selected = myAsteroids.at(i);
        i++;
    }
    return selected;
}