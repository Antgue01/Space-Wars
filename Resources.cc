#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {


		{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } 
};

vector<Resources::ImageInfo> Resources::images_ {

		
        {Player1,"./resources/images/player1.png"},
        {Player2,"./resources/images/player2.png"},
        {Heart,"./resources/images/heart.png"},
        {Asteroid,"./resources/images/asteroid.png"},
        {PlasmaBall,"./resources/images/bolaPlasma.png"},
		
		{Shield,"./resources/images/escudo.png"},
        {Bullet,"./resources/images/whiterect.png"},
		{Laser,"./resources/images/laser.png"},
		{Space,"./resources/images/space.jpg"}

};

vector<Resources::TextMsgInfo> Resources::messages_ {

		{ ClientWin, "Client wins", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ ServerWin, "Server wins", { COLOR(0xffffbbff) }, ARIAL24 } //

};

vector<Resources::MusicInfo> Resources::musics_ {

	
		
};

vector<Resources::SoundInfo> Resources::sounds_ {

};

