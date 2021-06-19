#pragma once
#include "Vector2D.h"
#include "InputHandler.h"
#include "Texture.h"
#include "SDLGame.h"
#include "Entity.h"
#include "BulletsPool.h"
#include "PlasmaPool.h"
#include "BounceBulletsPool.h"

class Vessel : public Entity
{
public:
    Vessel(SDLGame *game, EntityManager *mngr, int _id, Vector2D pos_, Texture *t_, SDL_Keycode right_, SDL_Keycode left_, SDL_Keycode up_, bool isServer, bool checkkeys_, BulletsPool *bp,
    PlasmaPool* pP,BounceBulletsPool* bbp);

    Vessel();

    virtual ~Vessel();

    virtual void update();
    virtual void draw();
    vector<bool> &getInput() { return input; }
    virtual void to_bin();
    virtual int from_bin(char *data);
    virtual void deliverMsg(Entity *msg);
    void calculatePos(Vector2D &position, Vector2D &vel);
    void LoseLife();
    int GetHealth();
    bool isDead() { return lives <= 0; }
    bool getCanPlay() { return canPlay; }
    void setCanPlay(bool b) { canPlay = b; }
    void Reset();
    inline Vector2D getPos() { return pos; }
    inline double getW() { return dimensions.getX(); }
    inline double getH() { return dimensions.getY(); }
    inline double getRot() { return angle; }
    bool getActiveShield() {return activeShield;}
    void reduceShieldHits()
    {
        if(!invecibility)
        {
            shieldHits--; 
            invecibility=true;
            if(shieldHits<=0)
            {
                shieldHits=0;
                activeShield=false;
                ready=false;
                readyTime = game_->getTime();
            }
        }
    }
 
private:
    void CheckKeys();
    void drawHearts();
    void manageShield();

    int lives;

    Vector2D pos;
    Vector2D initPos;
    Vector2D dimensions;
    double angle, speed;
    Vector2D velocity;
    int thrust;
    double rotSpeed;
    int limitX, limitY;

    Texture* tShield;
    bool activeShield;
    int shieldTime;
    int shieldHits;
    bool invecibility;
    bool ready;
    int readyTime;

    int recoveryTime;

    Texture *tHeart;
    Texture *t;
    SDL_Keycode right;
    SDL_Keycode left;
    SDL_Keycode up;
    std::vector<bool> input;
    bool server;
    bool checkkeys;

    int startTime;
    BulletsPool *bulletsPool;
    PlasmaPool *plasmaPool;
    BounceBulletsPool* bounceBulletsPool;
    bool canPlay;
};