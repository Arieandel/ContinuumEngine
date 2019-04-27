#include "AudioEngine.h"

#include "CEErr.h"

namespace ContinuumEngine2D {
	void SoundEffect::play(int loops) {
		if (Mix_PlayChannel(-1, chunk, loops) == -1) {
			if (Mix_PlayChannel(1, chunk, loops) == -1) {
				fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
			}
		}
	}

	void Music::pause() {
		Mix_PauseMusic();
	}

	void Music::stop() {
		Mix_HaltMusic();
	}

	void Music::resume() {
		Mix_ResumeMusic();
	}

	void Music::play(int loops) {
		if (Mix_PlayMusic(music, loops) == -1) {
			fatalError("Mix_PlayMusic error: " + std::string(Mix_GetError()));
		}
	}

	AudioEngine::AudioEngine() {}

	AudioEngine::~AudioEngine() {
		destroy();
	}

	void AudioEngine::init() {
		if (isInitialized) {
			fatalError("Tried to initialize Audio Engine twice!\n");
		}

		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
			fatalError("Mix_Init error: " + std::string(Mix_GetError()));
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			fatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
		}

		Mix_Volume(-1, 32);

		isInitialized = true;
	}

	void AudioEngine::destroy() {
		if (isInitialized) {
			isInitialized = false;
			Mix_Quit();

			for (auto& it : effectMap) {
				Mix_FreeChunk(it.second);
			}

			for (auto& it : musicMap) {
				Mix_FreeMusic(it.second);
			}

			effectMap.clear();
			musicMap.clear();

			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath) {
		SoundEffect effect;

		auto it = effectMap.find(filePath);
		if (it == effectMap.end()) {
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			if (chunk == nullptr) {
				fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
			}
			effect.chunk = chunk;
			effectMap[filePath] = chunk;
		}
		else {
			effect.chunk = it->second;
		}

		return effect;
	}

	Music AudioEngine::loadMusic(const std::string& filePath) {
		Music music;

		auto it = musicMap.find(filePath);
		if (it == musicMap.end()) {
			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
			if (mixMusic == nullptr) {
				fatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
			}
			music.music = mixMusic;
			musicMap[filePath] = mixMusic;
		}
		else {
			music.music = it->second;
		}

		return music;
	}
}