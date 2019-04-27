#include "EventListener.h"
#include "../../ContinuumEngine.h"


namespace ContinuumEngine3D {

	void EventListener::Update()
	{
		SDL_Event SDLEvent;
		while (SDL_PollEvent(&SDLEvent)) {
			switch (SDLEvent.type)
			{
			case SDL_QUIT:
				ContinuumEngine::GetInstance()->ExitGame();
				break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEMOTION:
			case SDL_MOUSEWHEEL:
				MouseEventListener::Update(SDLEvent);
				break;
			case SDL_KEYDOWN:
				KeyboardEventListener::Update(SDLEvent);
				break;
			case SDL_KEYUP:
				KeyboardEventListener::Update(SDLEvent);
				break;
			case SDL_CONTROLLERAXISMOTION:
				GameControllerListener::Update(SDLEvent);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				GameControllerListener::Update(SDLEvent);
				break;
			case SDL_CONTROLLERBUTTONUP:
				GameControllerListener::Update(SDLEvent);
				break;
			case SDL_CONTROLLERDEVICEADDED:
				GameControllerListener::Update(SDLEvent);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				GameControllerListener::Update(SDLEvent);
			default:
				break;

			}
		}
	}

	bool EventListener::Init() { // This function is not being called at anywhere => Not working currently
		//Initialize SDL
		if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			if (SDL_IsGameController(i))
			{
				gGameController = SDL_GameControllerOpen(i);
				break;
			}
		}
		return true;
	}

	void EventListener::Close() {
		//Close game controller
		SDL_GameControllerClose(gGameController);
		gGameController = NULL;
	}

}
