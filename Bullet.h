#pragma once
#include"Vector2D.h"

class Bullet
{
private:
	Vector2D pos;
	Vector2D vel;
	double w;
	double h;
	double rotation;
	bool inUse = false;

public:
	Bullet();
	~Bullet() { };
	bool GetInUse() { return inUse; }
 	void SetInUse(bool b) { inUse = b; }
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
	
};