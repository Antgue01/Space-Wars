#include "Vessel.h"
#include "SDL_macros.h"
#include "Message.h"
Vessel::Vessel(SDLGame *game, EntityManager *mngr, int _id, Vector2D pos_, Texture *t_, SDL_Keycode right_, SDL_Keycode left_, SDL_Keycode up_, MessageQueue *q, Vessel *Other) : Entity(game, mngr, q, TypeMessage::NetVessel), speed(1), id(_id), thrust(1), velocity(), pos(pos_), size(Vector2D(70, 70)), angle(0.0), t(t_),
                                                                                                                                                                                  right(right_), left(left_), up(up_), input(3, false), netpos(pos_), netvelocity(), netangle(0), other(Other)

{
    limitX = SDLGame::instance()->getWindowWidth();
    limitY = SDLGame::instance()->getWindowHeight();
}

Vessel::~Vessel()
{
    t = nullptr;
}

void Vessel::update()
{

    if (id < 2)
        checkKeys();

    if (id == 0)
    {
        calculatePos(pos, velocity);
        Send(new Vessel(2, pos, velocity, angle));
        if (input[0])
            netangle += 5;
        else if (input[1])
            netangle -= 5;
        if (input[2])
            netvelocity.set(netvelocity + Vector2D(0, -speed).rotate(netangle * thrust));
        calculatePos(netpos, netvelocity);
        Send(new Vessel(1, netpos, netvelocity, angle));
        if (other != nullptr)
        {
            other->pos = netpos;
            other->velocity = netvelocity;
            other->angle = netangle;
        }
    }
}
void Vessel::calculatePos(Vector2D &position, Vector2D &vel)
{
    //En caso de que se salga de la pantalla rebota
    if (position.getX() + vel.getX() + 50 >= limitX || position.getX() + vel.getX() <= 0)
        vel.setX(vel.getX() * -1);

    if (position.getY() + vel.getY() + 50 >= limitY || position.getY() + vel.getY() <= 0)
        vel.setY(vel.getY() * -1);

    if (vel.magnitude() > 2)
        vel.set(vel.normalize() * 2); //Le pongo limite de velocidad

    //La reduzco
    vel.set(vel * 0.995);
    //Pongo la velocidad
    position.set(position + vel);
}
void Vessel::checkKeys()
{
    InputHandler *ih = InputHandler::instance();
    //Si se ha tocado cualquier tecla
    if (ih->keyDownEvent())
    {
        //Roto Derecha
        if (ih->isKeyDown(right))
        {
            if (id == 0)
                angle += 5;
            else
                input[0] = true;
        }
        //Roto Izquierda
        else if (ih->isKeyDown(left))
        {
            if (id == 0)
                angle -= 5;
            else
                input[1] = true;
        }
        if (ih->isKeyDown(up))
        {
            if (id == 0)
                velocity.set(velocity + Vector2D(0, -speed).rotate(angle * thrust));
            else
                input[2] = true;
        }
    }
    else
        input.assign(3, false);
    if (id == 1)
        Send(new Vessel(0, Vector2D(), Vector2D(), 0, input));
}
void Vessel::draw()
{
    SDL_Rect dest = {pos.getX(), pos.getY(), size.getX(), size.getY()};
    t->render(dest, angle);
}

void Vessel::to_bin()
{
    int size = sizeof(int) * 4 + sizeof(double) * 5;
    alloc_data(size);
    memset(_data, 0, size);
    char *aux = _data;
    memcpy(aux, &id, sizeof(int));
    aux += sizeof(int);
    int auxBool;
    for (size_t i = 0; i < 3; i++)
    {
        auxBool = input.at(i);
        memcpy(aux, &auxBool, sizeof(int));
        aux += sizeof(int);
    }

    double auxD = pos.getX();
    memcpy(aux, &auxD, sizeof(double));
    aux += sizeof(double);
    auxD = pos.getY();
    memcpy(aux, &auxD, sizeof(double));
    aux += sizeof(double);
    auxD = angle;
    memcpy(aux, &auxD, sizeof(double));
    aux += sizeof(double);
    auxD = velocity.getX();
    memcpy(aux, &auxD, sizeof(double));
    aux += sizeof(double);
    auxD = velocity.getY();
    memcpy(aux, &auxD, sizeof(double));
}

int Vessel::from_bin(char *data)
{
    if (data == 0)
    {
        std::cout << "Error on deserialization, empty object received\n";
        return -1;
    }
    int size = sizeof(int) * 4 + 5 * sizeof(double);

    alloc_data(size);

    memcpy(static_cast<void *>(_data), data, size);
    memcpy(&id, data, sizeof(int));
    data += sizeof(int);
    int auxBool;
    if (input.size() == 0)
        input.assign(3, false);
    for (size_t i = 0; i < 3; i++)
    {
        memcpy(&auxBool, data, sizeof(int));
        input.at(i) = auxBool;
        data += sizeof(int);
    }

    double auxD;
    memcpy(&auxD, data, sizeof(double));
    pos.setX(auxD);
    data += sizeof(double);
    memcpy(&auxD, data, sizeof(double));
    pos.setY(auxD);
    data += sizeof(double);
    memcpy(&angle, data, sizeof(double));
    data += sizeof(double);
    memcpy(&auxD, data, sizeof(double));
    velocity.setX(auxD);
    data += sizeof(double);
    memcpy(&auxD, data, sizeof(double));
    velocity.setY(auxD);

    //Reconstruir la clase usando el buffer _data

    return 0;
}
void Vessel::Receive(Serializable *msg)
{
    Vessel *other = dynamic_cast<Vessel *>(msg);
    if (other != nullptr)
    {
        if (id == 0 && other->id == 1)
        {

            input = other->input;
            netpos = other->pos;
            netvelocity = other->velocity;
            netangle = other->angle;
        }
        if ((id == 1 && other->id ==1 )|| (id == 2 && other->id==2))
        {
            pos = other->pos;
            angle = other->angle;
        }
    }
}
