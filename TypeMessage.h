#pragma once
#include "Serializable.h"
#include <memory.h>
#include <iostream>

class TypeMessage : public Serializable
{

public:
    enum NetType : uint
    {
        Default,
        NetVessel,
        NetBullet,
        NetAsteroid,
        NetGameLogic,
        NetBounceBullet,
        Logout
    };

    TypeMessage(NetType t = Default) : Serializable(), myType_(t) {}

    NetType myType_;
    virtual void to_bin();
    virtual int from_bin(char *bobj);

private:
    int a = 0;
};