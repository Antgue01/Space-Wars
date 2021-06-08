#include "VesselControl.h"
#include "NetVesselControl.h"
VesselControl::VesselControl(MessageQueue*q,SDL_Keycode right, SDL_Keycode left, SDL_Keycode up) : Component(ecs::VesselControl, netType::NotSerialize,q), right(right), left(left), up(up), thrust(1), speed(0) {}

void VesselControl::init()
{
    //Consigo el transform del jugador
    tr = GETCMP1_(Transform);
    speed = 1;
    thrust = 1;
}
void VesselControl::update()
{
    InputHandler *ih = InputHandler::instance();
    //Si se ha tocado cualquier tecla
    if (ih->keyDownEvent())
    {
        //Roto Derecha
        if (ih->isKeyDown(right))
        {
            tr->setRot(tr->getRot() + 5);
        }
        //Roto Izquierda
        else if (ih->isKeyDown(left))
        {
            tr->setRot(tr->getRot() - 5);
        }
        //Impulso en una direccion concreta, dependiendo si el archivo de configuraci�n tenia velocidad o no
        if (ih->isKeyDown(up))
        {
            tr->setVel(tr->getVel() + Vector2D(0, -speed).rotate(tr->getRot() * thrust));
        }
    }
}
