/*#include "NetVesselControl.h"
NetVesselControl::NetVesselControl(MessageQueue *q, SDL_Keycode right, SDL_Keycode left, SDL_Keycode up, bool sends) : Component(ecs::NetVesselControl, netType::netVesselControl, q), right(right), left(left), up(up), thrust(1), speed(0), _sends(sends) {}

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
    //si soy el cliente le mando el input al servidor
    if (_sends)
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

        queue_->addMsg(this);
    }
}
void NetVesselControl::to_bin()
{

    int size = sizeof(bool) * 3 + sizeof(netType);
    alloc_data(size);
    memset(_data, 0, size);
    char *aux = _data;
    int auxBool = pressedKeys.at(0);
    memcpy(aux, &type_, sizeof(netType));
    aux += sizeof(netType);
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
    int size = sizeof(bool) * 3 + sizeof(netType);

    alloc_data(size);

    memcpy(static_cast<void *>(_data), data, size);

    //Reconstruir la clase usando el buffer _data

    return 0;
}
void NetVesselControl::deserialize(char *msg)
{
    char *aux = _data;
    int auxBool;
    memcpy(&auxBool, aux, sizeof(bool));
    pressedKeys.at(0) = auxBool;
    aux += sizeof(bool);
    memcpy(&auxBool, aux, sizeof(bool));
    pressedKeys.at(1) = auxBool;
    aux += sizeof(bool);
    memcpy(&auxBool, aux, sizeof(bool));
    pressedKeys.at(2) = auxBool;
    aux += sizeof(bool);
    memcpy(&type_, aux, sizeof(netType));
}
char *NetVesselControl::Receive(Serializable *msg)
{
    //si soy el servidor me actualizo y le mando la info de vuelta al cliente
    if (!_sends)
    {

        char *data = Component::Receive(msg);
        NetVesselControl *aux;
        aux->deserialize(data);
        std::vector<bool> pressed = aux->getKeys();
        if (pressed[0])
        {
            tr->setRot(tr->getRot() + 5);
        }
        //Roto Izquierda
        else if (pressed[1])
        {
            tr->setRot(tr->getRot() - 5);
        }
        //Impulso en una direccion concreta, dependiendo si el archivo de configuraci�n tenia velocidad o no
        if (pressed[2])
        {
            tr->setVel(tr->getVel() + Vector2D(0, -speed).rotate(tr->getRot() * thrust));
        }
        queue_->addMsg(tr);
        return "";
    }
}
*/