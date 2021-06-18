#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

using namespace std;

class Resources {
public:

	enum TextureId : std::size_t {
		// images		
		Player1,
		Player2,
		Heart,
		Asteroid,
		Bullet,

		// text
		ServerWin,
		ClientWin,
		ServerLose,
		ClientLose
	};

	enum AudioId : std::size_t {
		// music
		ImperialMarch,

		// sound effects
		GunShoot,
		Explosion
	};

	enum FontId : std::size_t {
		ARIAL16, ARIAL24,
	};

	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};

	struct ImageInfo {
		TextureId id;
		string fileName;
	};

	struct TextMsgInfo {
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct MusicInfo {
		AudioId id;
		string fileName;
	};

	struct SoundInfo {
		AudioId id;
		string fileName;

	};

	static vector<FontInfo> fonts_; // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<TextMsgInfo> messages_; // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp

};
