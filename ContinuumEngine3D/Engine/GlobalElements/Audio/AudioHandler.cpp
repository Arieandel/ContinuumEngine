#include "AudioHandler.h"


namespace ContinuumEngine3D {

	void AudioHandler::PlayMusic(std::string filename, int loops)
	{
		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(audio->GetMusic(filename), loops);
	}

	void AudioHandler::ResumeMusic()
	{
		if (Mix_PausedMusic() != 0)
			Mix_ResumeMusic();
	}

	void AudioHandler::PauseMusic()
	{
		if (Mix_PlayingMusic() != 0)
			Mix_PauseMusic();
	}

	void AudioHandler::PlaySFX(std::string filename, int loops, int channel)
	{
		if (Mix_Playing(channel) == 0)
			Mix_PlayChannel(channel, SFX->GetSFX(filename), loops);
	}

	AudioHandler::AudioHandler()
	{
		audio = new Audio();
		SFX = new Audio();
	}
	AudioHandler::~AudioHandler()
	{
		audio = nullptr;
		SFX = nullptr;
	}

}