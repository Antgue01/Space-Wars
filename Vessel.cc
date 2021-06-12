#include "Vessel.h"
#include "SDL_macros.h"
#include "Message.h"
Vessel::Vessel(SDLGame *game, EntityManager *mngr, int _id, Vector2D pos_, Texture *t_, SDL_Keycode right_, SDL_Keycode left_, SDL_Keycode up_, MessageQueue *q) : Entity(game, mngr), speed(1),
                                                                                                                                                                   thrust(1), velocity(), pos(pos_), size(Vector2D(70, 70)), angle(0.0), t(t_), queue(q),
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
    //sendKeys
}
void Vessel::draw()
{
    SDL_Rect dest = {pos.getX(), pos.getY(), size.getX(), size.getY()};
    t->render(dest, angle);
}

void Vessel::to_bin()
{
}

int Vessel::from_bin(char *data)
{
    return 0;
}

void Vessel::Receive(Serializable *msg)
{
    Vessel *other = static_cast<Vessel *>(msg);
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
