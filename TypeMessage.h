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
        NetBulletsPool,
        NetAsteroidsPool
    };

    TypeMessage(NetType t = Default) : Serializable(), myType_(t) {}

    NetType myType_;
    virtual void to_bin();
    virtual int from_bin(char *bobj);
    //virtual void deserialize(char* data) override;
private:
    int a = 0;
};