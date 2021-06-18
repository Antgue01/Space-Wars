#include "VesselWinManager.h"
#include "Vessel.h"
void VesselWinManager::update()
{
    
}

void VesselWinManager::draw()
{
    
       if(v1->isDead())
        {
            Texture *hitanykey = game_->getTextureMngr()->getTexture(Resources::ClientWin);				
		    hitanykey->render(
				game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				game_->getWindowHeight() - hitanykey->getHeight() - 50);
        }

        if(v2->isDead())
        {
            Texture *hitanykey = game_->getTextureMngr()->getTexture(Resources::ServerWin);				
		    hitanykey->render(
				game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				game_->getWindowHeight() - hitanykey->getHeight() - 50);
        }
           
}

void VesselWinManager::to_bin()
{
    
}

int VesselWinManager::from_bin(char *data)
{
    return 0;
}

void VesselWinManager::deliverMsg(Entity* msg)
{
    
}