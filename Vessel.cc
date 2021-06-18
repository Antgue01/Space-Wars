#include "Vessel.h"
#include "SDL_macros.h"
#include "Message.h"

Vessel::Vessel(SDLGame *game, EntityManager *mngr, int _id, Vector2D pos_, Texture *t_, SDL_Keycode right_, SDL_Keycode left_, SDL_Keycode up_, bool sendInp, bool checkkeys_ ,BulletsPool* bp) : Entity(game, mngr, TypeMessage::NetVessel, _id), speed(1), thrust(1), velocity(), pos(pos_), size(Vector2D(70, 70)), angle(0.0), t(t_),
                                                                                                                                                                                                                       right(right_), left(left_), up(up_), input(), server(sendInp), checkkeys(checkkeys_), startTime(0) ,bulletsPool(bp),lives(3)

{
    tHeart = game->getTextureMngr()->getTexture(Resources::Heart);
    limitX = SDLGame::instance()->getWindowWidth();
    limitY = SDLGame::instance()->getWindowHeight();
    input.assign(4, false);
    startTime = game_->getTime();
}
Vessel::Vessel() : Entity(nullptr, nullptr, TypeMessage::NetVessel, 0), t(nullptr), pos(), size(), angle(0), speed(),
                   velocity(velocity), rotSpeed(), limitX(), limitY(), right(), left(), up(), thrust(), input(), server(false), checkkeys(false),lives(3)
{
    input.assign(4, false);
}

Vessel::~Vessel()
{
    t = nullptr;
    bulletsPool = nullptr;
    tHeart=nullptr;
}

void Vessel::update()
{
    if (checkkeys)
        CheckKeys();

    if (server)
    {
        calculatePos(pos, velocity);
    }
}
void Vessel::calculatePos(Vector2D &position, Vector2D &vel)
{

    if (input[0] == true)
    {
        angle += 5;
        if (angle >= 360)
            angle = 0;
    }
    else if (input[1] == true)
    {
        angle -= 5;
        if (angle <= -360)
            angle = 0;
    }

    if (input[2] == true)
        velocity.set(velocity + Vector2D(0, -speed).rotate(angle * thrust));

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
    if (input[3])
    {
        Vector2D bulletPos = pos + Vector2D(size.getX() / 2, size.getY() / 2) + Vector2D(0, -(size.getX() / 2 + 5.0)).rotate(angle);
        Vector2D bulletVel = Vector2D(0, -1).rotate(angle) * 2;
        bulletsPool->shoot(bulletPos,bulletVel,5,20);
        // input[3]=false;
    }
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
        if (id_ == 0)
            if (angle == 360 || angle == -360)
                angle = 0;
        if (ih->isKeyDown(up))
        {
            input[2] = true;
        }
        if (ih->isKeyDown(SDLK_SPACE) && game_->getTime() >= startTime + 250)
        {
            input[3] = true;
            startTime = game_->getTime(); //Reseteamos el tiempo de retroceso
        }
        
    }
    else
        input.assign(4, false);
}

void Vessel::draw()
{
    SDL_Rect dest = {pos.getX(), pos.getY(), size.getX(), size.getY()};
    t->render(dest, angle);

    drawHearts();
}

void Vessel::drawHearts()
{
    int i = 0;
	SDL_Rect dest = { 10,10,40,40 };
	while (i < lives)
	{
		dest.x= 10 + (i*40);
		tHeart->render(dest);
		i++;
	}
}

void Vessel::LoseLife()
{
    lives--;
    if(lives<=0)lives=0;
}

int Vessel::GetHealth()
{
    return lives;
}


void Vessel::to_bin()
{
    int size = sizeof(int) * 6 + sizeof(double) * 3;
    alloc_data(size);
    memset(_data, 0, size);
    char *aux = _data;
    memcpy(aux, &id_, sizeof(int));
    aux += sizeof(int);
    int auxBool;
    for (size_t i = 0; i < 4; i++)
    {
        auxBool = input.at(i);
        memcpy(aux, &auxBool, sizeof(int));
        aux += sizeof(int);
    }

    memcpy(aux, &lives, sizeof(int));
    aux += sizeof(int);

    double auxD = pos.getX();
    memcpy(aux, &auxD, sizeof(double));
    aux += sizeof(double);
    auxD = pos.getY();
    memcpy(aux, &auxD, sizeof(double));
    aux += sizeof(double);
    auxD = angle;
    memcpy(aux, &auxD, sizeof(double));
}

int Vessel::from_bin(char *data)
{
    if (data == 0)
    {
        std::cout << "Error on deserialization, empty object received\n";
        return -1;
    }
    int size = sizeof(int) * 6 + 3 * sizeof(double);

    alloc_data(size);

    memcpy(static_cast<void *>(_data), data, size);
    memcpy(&id_, data, sizeof(int));
    data += sizeof(int);
    int auxBool;
    for (size_t i = 0; i < 4; i++)
    {
        memcpy(&auxBool, data, sizeof(int));
        input.at(i) = auxBool;
        data += sizeof(int);
    }

    memcpy(&lives, data, sizeof(int));
    data += sizeof(int);

    double auxD;
    memcpy(&auxD, data, sizeof(double));
    pos.setX(auxD);
    data += sizeof(double);
    memcpy(&auxD, data, sizeof(double));
    pos.setY(auxD);
    data += sizeof(double);
    memcpy(&angle, data, sizeof(double));
    data += sizeof(double);
    return 0;
}
void Vessel::deliverMsg(Entity *msg)
{
    Vessel *v = static_cast<Vessel *>(msg);
    if (v != nullptr)
    {
        input = v->input;
        if (!server)
        {
            pos = v->pos;
            angle = v->angle;
        }
    }
}
