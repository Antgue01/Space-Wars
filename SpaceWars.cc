#include "SDL_macros.h"
#include "SpaceWars.h"
#include <assert.h>
#include "Entity.h"
#include "InputHandler.h"
#include "SDLGame.h"

#include "LoginMessage.h"
#include "Vessel.h"
using namespace std;

SpaceWars::SpaceWars(const char *host, const char *port, bool client) : game_(nullptr),			 //
																		entityManager_(nullptr), //
																		exit_(false)
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
/*
	LoginMessage msg;
	serverSd = new Socket(host, port);
	serverSd->send(msg, *serverSd);
	msgQueue = new MessageQueue(*serverSd, *serverSd);
*/
	game_ = SDLGame::init("SpaceWars", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	Vessel* player1 = new Vessel(game_,entityManager_,1,Vector2D(120,120),game_->getTextureMngr()->getTexture(Resources::Player1),SDLK_d,SDLK_a,SDLK_w);
	
	entityManager_->addEntity(player1);


	Vessel* player2 = new Vessel(game_,entityManager_,1,Vector2D(300,120),game_->getTextureMngr()->getTexture(Resources::Player2),SDLK_RIGHT,SDLK_LEFT,SDLK_UP);
	
	entityManager_->addEntity(player2);

	//nave
	#pragma region deprecated
	// Entity *player1 = entityManager_->addEntity();
	// Transform *player1TR = player1->addComponent<Transform>(msgQueue);
	// player1->addComponent<VesselMovement>(msgQueue);
	// player1->addComponent<VesselViewer>(msgQueue,game_->getTextureMngr()->getTexture(Resources::Player1));
	// // Health* fighterHealth = player1->addComponent<Health>(game_->getTextureMngr()->getTexture(Resources::Heart));
	// player1TR->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
	// player1TR->setWH(70, 70);

	// Entity *player2 = entityManager_->addEntity();
	// Transform *player2TR = player2->addComponent<Transform>(msgQueue);
	// player2->addComponent<VesselViewer>(msgQueue,game_->getTextureMngr()->getTexture(Resources::Player2));
	// player2->addComponent<NetVesselControl>(msgQueue,SDLK_d, SDLK_a, SDLK_w,true);
	// player2TR->setPos(0, game_->getWindowHeight() / 2);
	// player2TR->setWH(70, 70);

	// // //pool de balas
	// // Entity* bullets = entityManager_->addEntity();
	// // BulletsPool* bPool= bullets->addComponent<BulletsPool>();
	// // bullets->addComponent<BulletsMotion>();
	// // bullets->addComponent<BulletsViewer>(game_->getTextureMngr()->getTexture(Resources::Bullet));

	// fighter->addComponent<Gun>(bPool);

	// //entidad de manejo del juego
	// Entity* gameManager = entityManager_->addEntity();
	// gameManager->addComponent<ScoreManager>(fighterHealth);
	// gameManager->addComponent<GameCtrl>(fighterHealth,astPool);
	// gameManager->addComponent<ScoreViewer>(astPool,fighterHealth);
	// gameManager->addComponent<GameLogic>(fighterTR, astPool, bPool, fighterHealth);

	//Configuracion del volumen de música y sonido
	//game_->getAudioMngr()->setMusicVolume(40);
	//game_->getAudioMngr()->setChannelVolume(5, 0);
	//game_->getAudioMngr()->setChannelVolume(5, 1);
#pragma endregion
	/*msgQueue->init(entityManager_->getEntities());
	CountMessage msg2(0);
	msgQueue->addMsg(&msg);
	msgQueue->flushSend();
	*/
}

void SpaceWars::initServer(const char *host, const char *port)
{
	/*serverSd = new Socket(host, port);
	serverSd->bind();

	LoginMessage msg;
	serverSd->recv(msg, clientSd);
	msgQueue = new MessageQueue(*serverSd, *clientSd);*/
	//juego
	game_ = SDLGame::init("SpaceWars", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	// //nave
	#pragma region deprecated
	// Entity *player1 = entityManager_->addEntity();
	// Transform *player1TR = player1->addComponent<Transform>(msgQueue);
	// player1->addComponent<VesselControl>(msgQueue,SDLK_d, SDLK_a, SDLK_w);
	// player1->addComponent<VesselMovement>(msgQueue);
	// player1->addComponent<VesselViewer>(msgQueue,game_->getTextureMngr()->getTexture(Resources::Player1));
	// // Health* fighterHealth = player1->addComponent<Health>(game_->getTextureMngr()->getTexture(Resources::Heart));
	// player1TR->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
	// player1TR->setWH(70, 70);

	// Entity *player2 = entityManager_->addEntity();
	// Transform *player2TR = player2->addComponent<Transform>(msgQueue);
	// player2->addComponent<NetVesselControl>(msgQueue,SDLK_d, SDLK_a, SDLK_w,false);
	// player2->addComponent<VesselViewer>(msgQueue,game_->getTextureMngr()->getTexture(Resources::Player2));
	// player2TR->setPos(0, game_->getWindowHeight() / 2);
	// player2TR->setWH(70, 70);
#pragma endregion
	/*msgQueue->init(entityManager_->getEntities());
	CountMessage msg2(0);
	msgQueue->addMsg(&msg2);
	msgQueue->flushSend();*/
}

void SpaceWars::closeGame()
{
	delete entityManager_;
	/*delete clientSd;
	delete serverSd;
	delete msgQueue;*/
	game_->closeSDL();
}

void SpaceWars::start()
{
	exit_ = false;

	while (!exit_)
	{

		Uint32 startTime = game_->getTime();
		//msgQueue->receive();
		//msgQueue->flushReceive();
		handleInput();
		update();
		render();
		//msgQueue->flushSend();

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