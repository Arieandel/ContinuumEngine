#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <map>
#include "Audio.h"


namespace ContinuumEngine3D {

	class AudioHandler {
	public:
		AudioHandler();
		~AudioHandler();
		void PlayMusic(std::string filename, int loops = -1);
		void ResumeMusic();
		void PauseMusic();

		void PlaySFX(std::string filename, int loops = 0, int channel = 0);

		Audio* audio;
		Audio* SFX;

	};
}
#endif // !AUDIOHANDLER_H 