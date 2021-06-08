#include "VesselViewer.h"
#include "Entity.h"

VesselViewer::VesselViewer(MessageQueue *q,Texture *t_) : Component(ecs::VesselViewer, netType::NotSerialize, q)
{
    t = t_;
}

void VesselViewer::init()
{
    tr = GETCMP1_(Transform); //coge el Transform de la nave
}
void VesselViewer::update()
{
}
//Dibuja la nave con su posicion y rotacion
void VesselViewer::draw()
{
    SDL_Rect dest = {tr->getPos().getX(), tr->getPos().getY(), tr->getW(), tr->getH()};
    t->render(dest, tr->getRot());
}