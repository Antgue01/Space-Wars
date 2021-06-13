#pragma once
#include "Vector2D.h"
#include "InputHandler.h"
#include "Texture.h"
#include "SDLGame.h"
#include "Entity.h"
#include "MessageQueue.h"

class Vessel : public Entity
{
public:
    Vessel(SDLGame *game, EntityManager *mngr, int _id, Vector2D pos_, Texture *t_, SDL_Keycode right_, SDL_Keycode left_, SDL_Keycode up_, MessageQueue *q);
    Vessel() : Entity(nullptr, nullptr, nullptr, TypeMessage::NetVessel), t(nullptr), pos(), size(), angle(), speed(), id(), velocity(), rotSpeed(), limitX(),
               limitY(), right(), left(), up(), thrust(), input(3, false) {}
    virtual ~Vessel();

    virtual void update();
    virtual void draw();
    virtual void to_bin();
    virtual int from_bin(char *data);
    virtual void Receive(Serializable *msg);

private:
    Vector2D pos;
    Vector2D size;
    double angle, speed;
    int id;
    Vector2D velocity;
    double rotSpeed;
    int limitX, limitY;
    Texture *t;
    SDL_Keycode right;
    SDL_Keycode left;
    SDL_Keycode up;
    int thrust;
    std::vector<bool> input;
    void checkKeys();
};