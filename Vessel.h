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
    
    Vessel(SDLGame *game, EntityManager *mngr, int _id, Vector2D pos_, Texture *t_, SDL_Keycode right_, SDL_Keycode left_, SDL_Keycode up_, MessageQueue *q,bool sendInp,bool checkkeys_);

    Vessel(bool checkkeys_=false,bool sendInp=false,int Id=0,Vector2D Pos = Vector2D(), Vector2D Vel = Vector2D(), double Angle = 0, vector<bool> Input = vector<bool>(3, false)) :
     Entity(nullptr, nullptr, nullptr, TypeMessage::NetVessel,Id), t(nullptr), pos(Pos), size(), angle(Angle), speed(), id(Id), velocity(velocity), rotSpeed(), limitX(),
    limitY(), right(), left(), up(), thrust(), input(Input),netpos(Pos),netvelocity(Vel),netangle(Angle),sendInput(sendInp) {}
        

    virtual ~Vessel();

    virtual void update();
    virtual void draw();
    virtual void to_bin();
    virtual int from_bin(char *data);
    virtual void deliverMsg(Entity *msg);
    void calculatePos(Vector2D &position, Vector2D &vel);


private:
    Vector2D pos;
    Vector2D netpos;
    Vector2D size;
    double angle, speed,netangle;
    int id;
    Vector2D velocity;
    Vector2D netvelocity;
    double rotSpeed;
    int limitX, limitY;
    Texture *t;
    SDL_Keycode right;
    SDL_Keycode left;
    SDL_Keycode up;
    int thrust;
    std::vector<bool> input;
    void CheckKeys();
    bool sendInput;
    bool checkkeys;
};