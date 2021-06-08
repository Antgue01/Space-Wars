#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
class VesselViewer : public Component
{
private:
    Texture *t = nullptr;
    Transform *tr = nullptr;

public:
    VesselViewer(Texture *t_);
    virtual ~VesselViewer() { t = nullptr; };
    void init() override;
    void update() override;
    void draw() override;
    virtual void to_bin() override {}
    virtual int from_bin(char *data) override {return 0;}
	virtual void deserialize() override {}
};