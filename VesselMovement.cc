
/*#include "VesselMovement.h"

VesselMovement::VesselMovement(MessageQueue* q) : Component(ecs::VesselMovement,netType::vesselMovement,q)
{
}

void VesselMovement::init()
{
    //Cojo el transform del jugador
    tr = GETCMP1_(Transform);
    limitX = SDLGame::instance()->getWindowWidth();
    limitY = SDLGame::instance()->getWindowHeight();
}

void VesselMovement::update()
{
    //EN caso de que se salga de la pantalla rebota
    if (tr->getPos().getX() + tr->getVel().getX() + 50 >= limitX ||
        tr->getPos().getX() + tr->getVel().getX() <= 0)
        tr->setVelX(tr->getVel().getX() * -1);
    if (tr->getPos().getY() + tr->getVel().getY() + 50 >= limitY ||
        tr->getPos().getY() + tr->getVel().getY() <= 0)
        tr->setVelY(tr->getVel().getY() * -1);
    //Pongo la velocidad
    tr->setPos(tr->getPos() + tr->getVel());
    if (tr->getVel().magnitude() > 2)
        tr->setVel(tr->getVel().normalize() * 2); //Le pongo l�mite de velocidad
    //La reduzco
    tr->setVel(tr->getVel() * 0.995);
}
*/