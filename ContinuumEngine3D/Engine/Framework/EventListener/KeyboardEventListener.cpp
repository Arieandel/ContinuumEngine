#include "KeyboardEventListener.h"
#include "../../ContinuumEngine.h"
#include <stdio.h>

namespace ContinuumEngine3D {

	ContinuumEngine* KeyboardEventListener::engineInstance = nullptr;


	KeyboardEventListener::~KeyboardEventListener() {
		engineInstance = nullptr;
	}
	void KeyboardEventListener::RegisterEngineObject(ContinuumEngine* engine_) {
		engineInstance = engine_;
	}


	void KeyboardEventListener::Update(SDL_Event e_)
	{
		if (e_.key.repeat)
		{
			onKeyHold(e_);
		}
		else
		{
			onKeyDown(e_);
		}

		if (e_.key.state == SDL_RELEASED) //When state is at 0
		{
			onKeyReleased(e_);
		}
	}

	void KeyboardEventListener::onKeyDown(SDL_Event e_)
	{
		engineInstance->NotifyOfKeyDown(e_);
	}
	void KeyboardEventListener::onKeyHold(SDL_Event e_)
	{
		engineInstance->NotifyOfKeyHold(e_);
	}

	void KeyboardEventListener::onKeyReleased(SDL_Event e_)
	{
		engineInstance->NotifyOfKeyReleased(e_);
	}



}