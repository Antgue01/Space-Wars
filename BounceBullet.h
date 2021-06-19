#pragma once
#include"Vector2D.h"
#include "Bullet.h"
class BounceBullet:public Bullet
{
public:
	BounceBullet(SDLGame *g = nullptr, EntityManager *mngr = nullptr,int id = 0, bool client = false, Texture *text = nullptr); 

	virtual ~BounceBullet() {t=nullptr; };

    
    virtual void to_bin();
    virtual int from_bin(char *data);
    virtual void deliverMsg(Entity *msg);
    bool getCanBounce(){return canBounce;}
    void setCanBounce(bool b) {canBounce=b;}
    inline virtual void setInUse(bool v) override { Entity::setInUse(v); canBounce=true; }
	
private:
    bool canBounce;

};