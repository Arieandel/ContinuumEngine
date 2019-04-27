#pragma once

#include <map>
#include <string>

#include <SDL/SDL_mixer.h>>

namespace ContinuumEngine2D {
	class SoundEffect {
	public:
		friend class AudioEngine;

		void play(int loops = 0);

	private:
		Mix_Chunk* chunk = nullptr;
	};

	class Music {
	public:
		friend class AudioEngine;

		void play(int loops = 1);
		static void pause();
		static void stop();
		static void resume();

	private:
		Mix_Music* music = nullptr;
	};

	class AudioEngine {
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);

	private:
		bool isInitialized = false;
		std::map<std::string, Mix_Chunk*> effectMap;
		std::map<std::string, Mix_Music*> musicMap;
	};
}
