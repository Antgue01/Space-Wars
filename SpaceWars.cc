#include "SDL_macros.h"
#include "SpaceWars.h"
#include <assert.h>
#include "Entity.h"
#include "InputHandler.h"
#include "SDLGame.h"
#include "LoginMessage.h"

#include "Vessel.h"
#include "VesselWinManager.h"
#include "PlasmaPool.h"
#include "BounceBulletsPool.h"

using namespace std;

SpaceWars::SpaceWars(const char *host, const char *port, bool client) : game_(nullptr),			 //
																		entityManager_(nullptr), //
																		exit_(false),
																		c(client)
{

	if (client)
		initGameClient(host, port);
	else
		initServer(host, port);

	space = game_->getTextureMngr()->getTexture(Resources::Space);
	dest = {0, 0, _WINDOW_WIDTH_, _WINDOW_HEIGHT_};
}

SpaceWars::~SpaceWars()
{
	closeGame();
}

void SpaceWars::initGameClient(const char *host, const char *port)
{
	game_ = SDLGame::init("client", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);
	AsteroidPool *asteroidPool_ = new AsteroidPool(game_, entityManager_, Resources::Asteroid, 3, 20, true);
	PlasmaPool *plasma = new PlasmaPool(game_, entityManager_, 56, Resources::PlasmaBall, true);
	BulletsPool *bulletsPool1 = new BulletsPool(game_, entityManager_, 33, Resources::Bullet, true);
	BounceBulletsPool* bounceBulletsPool = new BounceBulletsPool(game_, entityManager_, 90, Resources::Laser, true);
	LoginMessage msg(1);
	serverSd = new Socket(host, port);
	serverSd->send(msg, *serverSd);
	clientSd=nullptr;
	msgQueue = new MessageQueue(serverSd, serverSd, true);
	logic_ = nullptr;

	double w = SDLGame::instance()->getWindowWidth() / 2;

	Vessel *player1 = new Vessel(game_, entityManager_, 0, Vector2D(w - (w / 2), SDLGame::instance()->getWindowHeight() / 2), game_->getTextureMngr()->getTexture(Resources::Player1), SDLK_d, SDLK_a, SDLK_w, false, false, bulletsPool1, plasma,bounceBulletsPool);
	entityManager_->addEntity(player1);
	Vessel *player2 = new Vessel(game_, entityManager_, 1, Vector2D(w + (w / 2), SDLGame::instance()->getWindowHeight() / 2), game_->getTextureMngr()->getTexture(Resources::Player2), SDLK_RIGHT, SDLK_LEFT, SDLK_UP, false, true, bulletsPool1, plasma,bounceBulletsPool);
	entityManager_->addEntity(player2);
	VesselWinManager *winMngr = new VesselWinManager(game_, entityManager_, 34, player1, player2);
	entityManager_->addEntity(winMngr);

	msgQueue->init(entityManager_->getEntities());
	netMng = new NetManager(msgQueue);
	netMng->init(entityManager_->getEntities());
}

void SpaceWars::initServer(const char *host, const char *port)
{
	game_ = SDLGame::init("server", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);
	AsteroidPool *asteroidPool_ = new AsteroidPool(game_, entityManager_, Resources::Asteroid, 3, 20, false);
	BulletsPool *bulletsPool1 = new BulletsPool(game_, entityManager_, 33, Resources::Bullet, false);
	PlasmaPool *plasma = new PlasmaPool(game_, entityManager_, 56, Resources::PlasmaBall, false);
	BounceBulletsPool* bounceBulletsPool = new BounceBulletsPool(game_, entityManager_, 90, Resources::Laser, false);
	serverSd = new Socket(host, port);
	serverSd->bind();

	LoginMessage msg;
	serverSd->recv(msg, clientSd);

	msgQueue = new MessageQueue(clientSd, serverSd, false);

	double w = SDLGame::instance()->getWindowWidth() / 2;
	Vessel *player1 = new Vessel(game_, entityManager_, 0, Vector2D(w - (w / 2), SDLGame::instance()->getWindowHeight() / 2),
								 game_->getTextureMngr()->getTexture(Resources::Player1), SDLK_RIGHT, SDLK_LEFT, SDLK_UP, true, true, bulletsPool1, plasma,bounceBulletsPool);
	entityManager_->addEntity(player1);
	Vessel *player2 = new Vessel(game_, entityManager_, 1, Vector2D(w + (w / 2), SDLGame::instance()->getWindowHeight() / 2),
	 game_->getTextureMngr()->getTexture(Resources::Player2), SDLK_d, SDLK_a, SDLK_w, true, false, bulletsPool1,plasma,bounceBulletsPool);
	entityManager_->addEntity(player2);
	logic_ = new GameLogic(player1, player2, asteroidPool_, bulletsPool1, plasma,bounceBulletsPool);

	VesselWinManager *winMngr = new VesselWinManager(game_, entityManager_, 34, player1, player2);

	entityManager_->addEntity(winMngr);
	msgQueue->init(entityManager_->getEntities());

	netMng = new NetManager(msgQueue);
	netMng->init(entityManager_->getEntities());
}

void SpaceWars::closeGame()
{
	delete entityManager_;
	if(clientSd!=nullptr)
		delete clientSd;
	if(serverSd!=nullptr)
		delete serverSd;
	delete msgQueue;
	game_->closeSDL();
	delete logic_;
}

void SpaceWars::start()
{
	exit_ = false;

	if (c)
	{
		netMng->send();
		msgQueue->flushSend();
	}
	while (!exit_)
	{

		Uint32 startTime = game_->getTime();
		exit_ = netMng->recieve();
		handleInput();
		update();
		if (logic_ != nullptr)
			logic_->update();
		render();
		netMng->send();
		msgQueue->flushSend();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void SpaceWars::stop()
{
	exit_ = true;
}

void SpaceWars::handleInput()
{

	InputHandler *ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent())
	{
		if (ih->isKeyDown(SDLK_ESCAPE))
		{
			msgQueue->addMsg(new TypeMessage(TypeMessage::Logout));
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f))
		{
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN)
			{
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			}
			else
			{
				SDL_SetWindowFullscreen(game_->getWindow(),
										SDL_WINDOW_FULLSCREEN);
			}
		}
	}
}

void SpaceWars::update()
{
	entityManager_->update();
}

void SpaceWars::render()
{
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());
	
	space->render(dest);
	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}