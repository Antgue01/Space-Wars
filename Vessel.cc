#include "Vessel.h"
#include "SDL_macros.h"
#include "Message.h"
Vessel::Vessel(SDLGame *game, EntityManager *mngr, int _id, Vector2D pos_, Texture *t_, SDL_Keycode right_, SDL_Keycode left_, SDL_Keycode up_, MessageQueue *q) : Entity(game, mngr, q, TypeMessage::NetVessel), speed(1), id(_id),
                                                                                                                                                                   thrust(1), velocity(), pos(pos_), size(Vector2D(70, 70)), angle(0.0), t(t_),
                                                                                                                                                                   right(right_), left(left_), up(up_), input(3, false)

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

    checkKeys();

    //En caso de que se salga de la pantalla rebota
    if (id == 0)
    {

        if (pos.getX() + velocity.getX() + 50 >= limitX || pos.getX() + velocity.getX() <= 0)
            velocity.setX(velocity.getX() * -1);

        if (pos.getY() + velocity.getY() + 50 >= limitY || pos.getY() + velocity.getY() <= 0)
            velocity.setY(velocity.getY() * -1);

        //Pongo la velocidad
        pos.set(pos + velocity);

        if (velocity.magnitude() > 2)
            velocity.set(velocity.normalize() * 2); //Le pongo limite de velocidad

        //La reduzco
        velocity.set(velocity * 0.995);
        //sendPos
        Send();
    }
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
        //Impulso en una direccion concreta, dependiendo si el archivo de configuraci�n tenia velocidad o no
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
        Send();
}
void Vessel::draw()
{
    SDL_Rect dest = {pos.getX(), pos.getY(), size.getX(), size.getY()};
    t->render(dest, angle);
}

void Vessel::to_bin()
{
    int size = sizeof(int) * 3 + sizeof(double) * 3;
    alloc_data(size);
    memset(_data, 0, size);
    char *aux = _data;
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
    std::cout<<_data<<'\n';
}

int Vessel::from_bin(char *data)
{
    if (data == 0)
    {
        std::cout << "Error on deserialization, empty object received\n";
        return -1;
    }
    int size = sizeof(int) * 3 + 3 * sizeof(double);

    alloc_data(size);

    memcpy(static_cast<void *>(_data), data, size);
    int auxBool;
    if (input.size() == 0)
        input.assign(3, false);
    for (size_t i = 0; i < 3; i++)
    {
        memcpy(&auxBool, &data, sizeof(int));
        input.at(i) = auxBool;
        data += sizeof(int);
    }

    double auxD;
    memcpy(&auxD, &data, sizeof(double));
    pos.setX(auxD);
    data += sizeof(double);
    memcpy(&auxD, &data, sizeof(double));
    pos.setY(auxD);
    data += sizeof(double);
    memcpy(&angle, &data, sizeof(double));


    //Reconstruir la clase usando el buffer _data

    return 0;
}

void Vessel::Receive(Serializable *msg)
{
    Vessel *other = dynamic_cast<Vessel *>(msg);
    if (other != nullptr)
    {
        if (id == 0)
            input = other->input;
        if (id == 1)
        {
            pos = other->pos;
        }
    }
}
