#include "Audio.h"


namespace ContinuumEngine3D {

	ContinuumEngine* Audio::engineInstance = nullptr;

	void Audio::RegisterEngineObject(ContinuumEngine * engine_)
	{
		engineInstance = nullptr;
	}

	Audio::Audio() {}

	Audio::~Audio()
	{
		engineInstance = nullptr;
		mMusic.clear();
		mSFX.clear();
	}

	Mix_Chunk * Audio::GetSFX(std::string filename)
	{
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("../Resources/Assets/Sound/Effects/" + filename);

		if (mSFX[fullPath] == nullptr) {
			mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
			if (mSFX[fullPath] == NULL)
				printf("SFX Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
		return mSFX[fullPath];
	}

	Mix_Music * Audio::GetMusic(std::string filename)
	{
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("../Resources/Assets/Sound/" + filename);

		if (mMusic[fullPath] == nullptr) {
			mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
			if (mMusic[fullPath] == NULL)
				printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
		return mMusic[fullPath];
	}
}