#ifndef JOYSTICKLISTENER_H
#define JOYSTICKLISTENER_H

#include <SDL/SDL.h>


namespace ContinuumEngine3D {

	class ContinuumEngine;

	class GameControllerListener {

	public:
		GameControllerListener() = delete;
		GameControllerListener(const GameControllerListener&) = delete;
		GameControllerListener(GameControllerListener&&) = delete;
		GameControllerListener& operator=(const GameControllerListener&) = delete;
		GameControllerListener& operator=(GameControllerListener&&) = delete;
		~GameControllerListener();
		static void RegisterEngineObject(ContinuumEngine* engine_);
		static void Update(SDL_Event e_);

		static void onAxisEvents(SDL_Event e_);
		static void onButtonPressed(SDL_Event e_);
		static void onButtonReleased(SDL_Event e_);
		static void onControllerConnected(SDL_Event e_, int controllerIndex_);
		static void onControllerDisconnected(SDL_Event e_, int controllerIndex_);


	private:
		static ContinuumEngine * engineInstance;

	};

}
#endif // !JOYSTICKLISTENER_H
