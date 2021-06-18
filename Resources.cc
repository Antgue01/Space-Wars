#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {
//
		
        {Player1,"./resources/images/player1.png"},
        {Player2,"./resources/images/player2.png"},
        {Heart,"./resources/images/heart.png"},
        {Asteroid,"./resources/images/asteroid.png"},
        {Bullet,"./resources/images/whiterect.png"}

};

vector<Resources::TextMsgInfo> Resources::messages_ {

		{ ClientWin, "Client wins", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ ServerWin, "Server wins", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ ClientLose, "Client loses", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ ServerLose, "Server loses", { COLOR(0xffffbbff) }, ARIAL24 } //
};

vector<Resources::MusicInfo> Resources::musics_ {
//
		{ ImperialMarch, "resources/sound/imperial_march.wav" } //
		
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ GunShoot, "resources/sound/gunshot.wav" }, //
		{ Explosion, "resources/sound/explosion.wav" } //
};

