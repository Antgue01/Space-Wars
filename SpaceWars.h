#pragma once

#include <vector>

#include "Manager.h"
#include "SDLGame.h"
#include  "Socket.h"
#include  "MessageQueue.h"
#include "AsteroidPool.h"
#include "NetManager.h"
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
    AsteroidPool* asteroidPool_;
    bool exit_;
    
    const static int _WINDOW_WIDTH_ = 640;
    const static int _WINDOW_HEIGHT_ = 480;

};