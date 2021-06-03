#include "NetVesselControl.h"
NetVesselControl::NetVesselControl(SDL_Keycode right, SDL_Keycode left, SDL_Keycode up) : Component(ecs::NetVesselControl), right(right), left(left), up(up), thrust(1), speed(0) {}

void NetVesselControl::init()
{
    //Consigo el transform del jugador
    tr = GETCMP1_(Transform);
    speed = 1;
    thrust = 1;
    pressedKeys.assign(3, false);
}
void NetVesselControl::update()
{
    InputHandler *ih = InputHandler::instance();
    //Si se ha tocado cualquier tecla
    if (ih->keyDownEvent())
    {
        //Roto Derecha
        if (ih->isKeyDown(right))
        {
            pressedKeys.at(0) = true;
        }
        //Roto Izquierda
        else if (ih->isKeyDown(left))
        {
            pressedKeys.at(1) = true;
        }
        //Impulso en una direccion concreta, dependiendo si el archivo de configuraci�n tenia velocidad o no
        if (ih->isKeyDown(up))
        {
            pressedKeys.at(2) = true;
        }
    }
    else
        pressedKeys.assign(3, false);
    // TODO: send vector
}
void NetVesselControl::to_bin()
{

    int size = sizeof(bool) * 3;
    alloc_data(size);
    memset(_data, 0, size);
    char *aux = _data;
    bool auxBool = pressedKeys.at(0);
    memcpy(aux, &auxBool, sizeof(bool));
    aux += sizeof(bool);
    auxBool = pressedKeys.at(1);
    memcpy(aux, &auxBool, sizeof(bool));
    aux += sizeof(bool);
    auxBool = pressedKeys.at(2);
    memcpy(aux, &auxBool, sizeof(bool));
}
int NetVesselControl::from_bin(char *data)
{
    if (data == 0)
    {
        std::cout << "Error on deserialization, empty object received\n";
        return -1;
    }
    int size = sizeof(bool) * 3;

    alloc_data(size);

    memcpy(static_cast<void *>(_data), data, size);

    //Reconstruir la clase usando el buffer _data
    char *aux = _data;
    bool auxBool;
    memcpy(&auxBool, aux, sizeof(bool));
    pressedKeys.at(0) = auxBool;
    aux += sizeof(bool);
    memcpy(&auxBool, aux, sizeof(bool));
    pressedKeys.at(1) = auxBool;
    aux += sizeof(bool);
    memcpy(&auxBool, aux, sizeof(bool));
    pressedKeys.at(2) = auxBool;
    return 0;
}