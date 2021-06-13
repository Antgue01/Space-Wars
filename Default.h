#pragma once
#include "Entity.h"
#include "MessageQueue.h"

class Default : public Entity
{
public:
    Default() : Entity(nullptr, nullptr, nullptr, TypeMessage::Default) {}
    virtual ~Default() override;

    virtual void update() override {}
    virtual void draw() override {}
    virtual void to_bin() override {}
    virtual int from_bin(char *data) override {return 0;}
    virtual void Receive(Serializable *msg) override {}
};