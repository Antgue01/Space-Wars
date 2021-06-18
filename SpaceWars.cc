#include "SDL_macros.h"
#include "SpaceWars.h"
#include <assert.h>
#include "Entity.h"
#include "InputHandler.h"
#include "SDLGame.h"
#include "LoginMessage.h"

#include "Vessel.h"
#include "VesselWinManager.h"

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
	BulletsPool *bulletsPool1 = new BulletsPool(game_, entityManager_, 33, Resources::Bullet, true);
	LoginMessage msg(1);
	serverSd = new Socket(host, port);
	serverSd->send(msg, *serverSd);
	msgQueue = new MessageQueue(serverSd, serverSd, true);
	logic_ = nullptr;

	double w = SDLGame::instance()->getWindowWidth() / 2;

	Vessel *player1 = new Vessel(game_, entityManager_, 0, Vector2D(w - (w / 2), SDLGame::instance()->getWindowHeight() / 2), game_->getTextureMngr()->getTexture(Resources::Player1), SDLK_d, SDLK_a, SDLK_w, false, false, bulletsPool1);
	entityManager_->addEntity(player1);
	Vessel *player2 = new Vessel(game_, entityManager_, 1, Vector2D(w + (w / 2), SDLGame::instance()->getWindowHeight() / 2), game_->getTextureMngr()->getTexture(Resources::Player2), SDLK_RIGHT, SDLK_LEFT, SDLK_UP, false, true, bulletsPool1);
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
	serverSd = new Socket(host, port);
	serverSd->bind();

	LoginMessage msg;
	serverSd->recv(msg, clientSd);
	std::cout << msg.a << std::endl;
	msgQueue = new MessageQueue(clientSd, serverSd, false);
	//juego
	// LoginMessage msg2(12);
	// serverSd->send(msg2, *clientSd);

	double w = SDLGame::instance()->getWindowWidth() / 2;
	Vessel *player1 = new Vessel(game_, entityManager_, 0, Vector2D(w - (w / 2), SDLGame::instance()->getWindowHeight() / 2), game_->getTextureMngr()->getTexture(Resources::Player1), SDLK_RIGHT, SDLK_LEFT, SDLK_UP, true, true, bulletsPool1);
	entityManager_->addEntity(player1);
	Vessel *player2 = new Vessel(game_, entityManager_, 1, Vector2D(w + (w / 2), SDLGame::instance()->getWindowHeight() / 2), game_->getTextureMngr()->getTexture(Resources::Player2), SDLK_d, SDLK_a, SDLK_w, true, false, bulletsPool1);
	entityManager_->addEntity(player2);
	logic_ = new GameLogic(player1, player2, asteroidPool_, bulletsPool1, this);

	VesselWinManager *winMngr = new VesselWinManager(game_, entityManager_, 34, player1, player2);
	entityManager_->addEntity(winMngr);
	msgQueue->init(entityManager_->getEntities());

	netMng = new NetManager(msgQueue);
	netMng->init(entityManager_->getEntities());
}

void SpaceWars::closeGame()
{
	delete entityManager_;
	delete clientSd;
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
		netMng->recieve();
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

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}