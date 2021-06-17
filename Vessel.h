#pragma once
#include "Vector2D.h"
#include "InputHandler.h"
#include "Texture.h"
#include "SDLGame.h"
#include "Entity.h"
#include "MessageQueue.h"
// #include "BulletsPool.h"

class Vessel : public Entity
{
public:
    Vessel(SDLGame *game, EntityManager *mngr, int _id, Vector2D pos_, Texture *t_, SDL_Keycode right_, SDL_Keycode left_, SDL_Keycode up_, MessageQueue *q, bool isServer, bool checkkeys_//,BulletsPool* bp
    );

    Vessel();                                                                                                                       

    virtual ~Vessel();

    virtual void update();
    virtual void draw();
    vector<bool>&getInput(){return input;}
    virtual void to_bin();
    virtual int from_bin(char *data);
    virtual void deliverMsg(Entity *msg);
    void calculatePos(Vector2D &position, Vector2D &vel);

private:
    void CheckKeys();

    Vector2D pos;
    Vector2D size;
    double angle, speed;
    Vector2D velocity;
    int thrust;
    double rotSpeed;
    int limitX, limitY;

    Texture *t;
    SDL_Keycode right;
    SDL_Keycode left;
    SDL_Keycode up;
    std::vector<bool> input;
    bool server;
    bool checkkeys;

    int startTime;
    // BulletsPool* bulletsPool;
};