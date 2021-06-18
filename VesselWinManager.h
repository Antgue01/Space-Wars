#pragma once
#include "Entity.h"
#include "Texture.h"
class Vessel;

class VesselWinManager : public Entity
{
public:
    VesselWinManager(SDLGame *game, EntityManager *mngr, int _id,Vessel* v1_,Vessel* v2_):Entity(game,mngr,TypeMessage::Default,_id),
    v1(v1_),v2(v2_) 
    {
    }

    VesselWinManager():Entity(nullptr,nullptr,TypeMessage::Default,0),v1(nullptr),v2(nullptr) {}

    virtual ~VesselWinManager() {}
    virtual void update();
    virtual void draw();
    virtual void to_bin();
    virtual int from_bin(char *data);
    virtual void deliverMsg(Entity *msg);


private:
    Vessel* v1;
    Vessel* v2;
};