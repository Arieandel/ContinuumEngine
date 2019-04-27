#ifndef AUDIO_H
#define AUDIO_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <map>

namespace ContinuumEngine3D {

	class ContinuumEngine;

	class Audio {

	public:
		Audio();
		Audio(Audio&&) = delete;
		Audio& operator=(const Audio&) = delete;
		Audio& operator=(Audio&&) = delete;
		~Audio();

		static void RegisterEngineObject(ContinuumEngine* engine_);

		Mix_Chunk* GetSFX(std::string filename);
		Mix_Music* GetMusic(std::string filename);

	private:
		static ContinuumEngine * engineInstance;
		std::map<std::string, Mix_Music*> mMusic;
		std::map<std::string, Mix_Chunk*> mSFX;
	};
}
#endif // !AUDIO_H