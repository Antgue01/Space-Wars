#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {
//
		{ Blank, "resources/images/blank.png" }, //
		{ TennisBall, "resources/images/tennis_ball.png" }, //
		{ KeyBoardIcon, "resources/images/keyboard.png" }, //
		{ MouseIcon, "resources/images/mouse.png" }, //
		{ AIIcon, "resources/images/ai.png" }, //
		{ SpaceShips, "resources/images/spaceships.png" }, //
		{ Star, "resources/images/star.png" }, //
        {Player1,"./resources/images/player1.png"},
        {Player2,"./resources/images/player2.png"},
        {Heart,"./resources/images/heart.png"},
        {Asteroid,"./resources/images/asteroid.png"},
        {Bullet,"./resources/images/whiterect.png"}

};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
		{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }, //
		{ PressAnyKey, "Press Any Key to Start", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		{ GameOverWin, "Game Over,You Win", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ GameOverLost, "Game Over,You Lost", { COLOR(0xffffbbff) }, ARIAL24 } //
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

