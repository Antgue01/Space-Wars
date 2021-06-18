#pragma once
#include"Vector2D.h"
#include "Entity.h"
class Bullet:public Entity
{
private:
	Vector2D pos;
	Vector2D vel;
	double w;
	double h;
	double rotation;
	Texture* t;
	bool isClient_;

public:
	Bullet(SDLGame *g = nullptr, EntityManager *mngr = nullptr, MessageQueue *q = nullptr, int id = 0, bool client = false, Texture *text = nullptr); 

	~Bullet() { };
	void setPos(Vector2D p) { pos = p; };
	void setVel(Vector2D v) { vel = v; };
	void setRot(int r) { rotation = r; };
	void setH(int h_) { h = h_; };
	void setW(int w_) { w = w_; };
	int getW() { return w; };
	int getH() { return h; };
	int getRot() { return rotation; };
	Vector2D getPos() { return pos; };
	Vector2D getVel() { return vel; };
	virtual void update();
    virtual void draw();
    virtual void to_bin();
    virtual int from_bin(char *data);
    virtual void deliverMsg(Entity *msg);
	
};