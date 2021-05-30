#include "SDL_macros.h"
#include "SpaceWars.h"
#include <assert.h>
#include "Entity.h"

#include "InputHandler.h"
#include "Transform.h"
#include "SDLGame.h"
#include "VesselViewer.h"


#include "SDL_macros.h"

using namespace std;

SpaceWars::SpaceWars() :
		game_(nullptr), //
		entityManager_(nullptr), //
		exit_(false) {
	initGame();
}

SpaceWars::~SpaceWars() {
	closeGame();
}

void SpaceWars::initGame() {

	game_ = SDLGame::init("SpaceWars", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	//nave
	Entity* player1 = entityManager_->addEntity();
	Transform *player1TR = player1->addComponent<Transform>();
	// player1->addComponent<FighterCtrl>();
	// player1->addComponent<FighterMotion>();
	player1->addComponent<VesselViewer>(game_->getTextureMngr()->getTexture(Resources::Fighter));
	// Health* fighterHealth = player1->addComponent<Health>(game_->getTextureMngr()->getTexture(Resources::Heart));
	player1TR->setPos(0, game_->getWindowHeight() / 2 );
	player1TR->setWH(70, 70);

    Entity* player2= entityManager_->addEntity();
    Transform* player2TR=player2->addComponent<Transform>();
	player2TR->setWH(70, 70);
    player2TR->setPosition(game_->getWindowWidth()-player2TR->getW()/2,game_->getWindowHeight()/2);
	/


	// //pool de balas
	// Entity* bullets = entityManager_->addEntity();
	// BulletsPool* bPool= bullets->addComponent<BulletsPool>();
	// bullets->addComponent<BulletsMotion>();
	// bullets->addComponent<BulletsViewer>(game_->getTextureMngr()->getTexture(Resources::Bullet));

	// fighter->addComponent<Gun>(bPool);

	// //entidad de manejo del juego
	// Entity* gameManager = entityManager_->addEntity();
	// gameManager->addComponent<ScoreManager>(fighterHealth);
	// gameManager->addComponent<GameCtrl>(fighterHealth,astPool);
	// gameManager->addComponent<ScoreViewer>(astPool,fighterHealth);
	// gameManager->addComponent<GameLogic>(fighterTR, astPool, bPool, fighterHealth);

	

	//Configuracion del volumen de música y sonido
	game_->getAudioMngr()->setMusicVolume(40);
	game_->getAudioMngr()->setChannelVolume(5, 0);
	game_->getAudioMngr()->setChannelVolume(5, 1);
	
	

}

void SpaceWars::closeGame() {
	delete entityManager_;
}

void SpaceWars::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void SpaceWars::stop() {
	exit_ = true;
}

void SpaceWars::handleInput() {

	InputHandler *ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			} else {
				SDL_SetWindowFullscreen(game_->getWindow(),
						SDL_WINDOW_FULLSCREEN);
			}
		}
	}

}

void SpaceWars::update() {
	entityManager_->update();
}

void SpaceWars::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}