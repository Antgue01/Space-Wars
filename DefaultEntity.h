#pragma once
#include "Entity.h"
#include "MessageQueue.h"

class DefaultEntity
    : public Entity
{
public:
    DefaultEntity();
    virtual ~DefaultEntity();

    virtual void update() override {}
    virtual void draw() override {}
    virtual void to_bin() override {}
    virtual int from_bin(char *data) override { return 0; }
    virtual void deliverMsg(Entity *msg) override {}
};