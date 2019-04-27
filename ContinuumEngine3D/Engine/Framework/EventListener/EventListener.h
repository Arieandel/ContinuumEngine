#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "MouseEventListener.h"
#include "KeyboardEventListener.h"
#include "GameControllerListener.h"


namespace ContinuumEngine3D {

	class EventListener
	{
	public:
		EventListener() = delete;
		EventListener(const EventListener&) = delete;
		EventListener(EventListener&&) = delete;
		EventListener& operator=(const EventListener&) = delete;
		EventListener& operator=(EventListener&&) = delete;

		static void Update();

		//Game Controller 1 handler
		SDL_GameController* gGameController;
		bool Init();
		void Close();
	};
}
#endif