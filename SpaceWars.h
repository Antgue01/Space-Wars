#pragma once

#include <vector>

#include "Manager.h"
#include "SDLGame.h"
#include  "Socket.h"
#include  "MessageQueue.h"
#include "AsteroidPool.h"
#include "NetManager.h"
#include "GameLogic.h"
class SpaceWars {

public:
    SpaceWars(const char* host,const char* port, bool client);
    virtual ~SpaceWars();

    // from SDLGame
    void start();
    void stop();



private:
    void initGameClient(const char* host,const char* port);
    void initServer(const char* host,const char* port);
    void closeGame();
    void handleInput();
    void update();
    void render();
    bool c;

    SDLGame* game_;
    EntityManager* entityManager_;
    Socket* clientSd;
    Socket* serverSd;
    MessageQueue* msgQueue;
    NetManager* netMng;
    GameLogic* logic_;
    bool exit_;
    Texture* space;
    SDL_Rect dest;
    
    const static int _WINDOW_WIDTH_ = 800;
    const static int _WINDOW_HEIGHT_ = 600;

};