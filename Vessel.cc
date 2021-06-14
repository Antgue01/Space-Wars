#include "Vessel.h"
#include "SDL_macros.h"
#include "Message.h"
Vessel::Vessel(SDLGame *game, EntityManager *mngr, int _id, Vector2D pos_, Texture *t_, SDL_Keycode right_, SDL_Keycode left_, SDL_Keycode up_, MessageQueue *q,bool checkkeys_,bool sendInp) : Entity(game, mngr, q, TypeMessage::NetVessel,_id), speed(1), id(_id), thrust(1), velocity(), pos(pos_), size(Vector2D(70, 70)), angle(0.0), t(t_),
                                                                                                                                                                                  right(right_), left(left_), up(up_), input(3, false), netpos(pos_), netvelocity(), netangle(0),sendInput(sendInp),checkkeys(checkkeys_)

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

    if(checkkeys)
        CheckKeys();

    if(sendInput)
    {
        calculatePos(pos, velocity);
    }
/*
    if (id == 0)
    {
        calculatePos(pos, velocity);
        //Send(new Vessel(2, pos, velocity, angle));
        if (input[0])
            netangle += 5;
        else if (input[1])
            netangle -= 5;
        if (input[2])
            netvelocity.set(netvelocity + Vector2D(0, -speed).rotate(netangle * thrust));
        calculatePos(netpos, netvelocity);
        //Send(new Vessel(1, netpos, netvelocity, angle));
        if (other != nullptr)
        {
            other->pos = netpos;
            other->velocity = netvelocity;
            other->angle = netangle;
        }
    }
    */
}
void Vessel::calculatePos(Vector2D &position, Vector2D &vel)
{

    if (input[0] == true)
    { 
        angle += 5; 
        if(angle>=360)angle= 0;
    }               
    else if (input[1]==true)
    { 
        angle -= 5;
        if(angle<=-360)angle= 0;
    }

    if(input[2]==true)velocity.set(velocity + Vector2D(0, -speed).rotate(angle * thrust));     

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
void Vessel::CheckKeys()
{
    InputHandler *ih = InputHandler::instance();
    //Si se ha tocado cualquier tecla
    if (ih->keyDownEvent())
    {
        //Roto Derecha
        if (ih->isKeyDown(right))
        {
            input[0] = true;
        }
        //Roto Izquierda
        else if (ih->isKeyDown(left))
        {
            input[1] = true;
        }
        if (ih->isKeyDown(up))
        {
            input[2] = true;
        }
    }
    else
        input.assign(3, false);
    
}
void Vessel::draw()
{
    SDL_Rect dest = {pos.getX(), pos.getY(), size.getX(), size.getY()};
    t->render(dest, angle);
}

void Vessel::to_bin()
{
    int size = sizeof(int) * 4 + sizeof(double) * 3;
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

}

int Vessel::from_bin(char *data)
{
    if (data == 0)
    {
        std::cout << "Error on deserialization, empty object received\n";
        return -1;
    }
    int size = sizeof(int) * 4 + 3 * sizeof(double);

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
   

    return 0;
}
void Vessel::deliverMsg(Entity *msg)
{
    Vessel* v = static_cast<Vessel*>(msg);
    if(v!=nullptr)
    {
        input = v->input;
        if(!sendInput)
        {
            pos = v->pos;
            angle = v->angle; 
        }
             
    }
        
}
