#include "Vector2D.h"
#include "Entity.h"
#include <memory.h>
class Asteroid : public Entity
{
private:
	Vector2D pos;
	Vector2D vel;
	double angle;
	double width;
	double height;
	int generations;
	bool isClient_;
	double WinWidth;
	double WinHeight;
	Texture *text;

public:
	Asteroid(SDLGame *g = nullptr, EntityManager *mngr = nullptr, MessageQueue *q = nullptr, int id = 0, bool client = false, Texture *t = nullptr) : Entity(g, mngr, q, TypeMessage::NetAsteroid, id)
	{
		angle = 0;
		width = 25;
		height = 25;
		inUse = false;
		generations = 3;
		pos = Vector2D(0, 0);
		vel = Vector2D(0, 0);
		isClient_ = client;
		WinWidth = SDLGame::instance()->getWindowWidth();
		WinHeight = SDLGame::instance()->getWindowHeight();
		text = t;
	}
	~Asteroid() {}
	double GetWidth() { return width; }
	double GetHeight() { return height; }
	Vector2D GetPos() { return pos; }
	Vector2D GetVel() { return vel; }
	double GetAngle() { return angle; }
	double GetGenarations() { return generations; }

	void SetPos(Vector2D npos);
	void SetAngle(double nangle);
	void SetVel(Vector2D vel);
	void SetGeneraciones(int gen)
	{
		generations = gen;
	}
	void SetWidth(int w) { width = w; }
	void SetHeight(int h) { height = h; }
	virtual void update() override;
	virtual void draw() override;
	virtual void deliverMsg(Entity *msg) override;
	virtual void to_bin() override;
	virtual int from_bin(char *data) override;
};