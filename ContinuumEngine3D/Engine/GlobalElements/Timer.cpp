#include "Timer.h"


namespace ContinuumEngine3D {

	Timer::Timer() : prevTicks(0), currentTicks(0) {
	}


	Timer::~Timer() {
	}


	void Timer::Start() {
		prevTicks = SDL_GetTicks();
		currentTicks = SDL_GetTicks();
	}
	void Timer::UpdateFrameTicks() {
		prevTicks = currentTicks;
		currentTicks = SDL_GetTicks();
	}
	float Timer::getDeltaTime() const {
		return (float)((currentTicks - prevTicks) / 1000.0f);
	}
	unsigned int Timer::GetSleepTime(const unsigned int fps_) const {
		unsigned int milliSecsPerFrame = 1000 / fps_;
		if (milliSecsPerFrame == 0) {
			return 0;
		}
		unsigned int sleepTime = milliSecsPerFrame - SDL_GetTicks();
		if (sleepTime > milliSecsPerFrame) {
			return milliSecsPerFrame;
		}
	}
	float Timer::GetCurrentTicks() const {
		return (float)(currentTicks / 1000.0f);
	}

}