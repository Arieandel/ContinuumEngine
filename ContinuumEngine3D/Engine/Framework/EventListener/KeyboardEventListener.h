#ifndef KEYBOARDEVENTHANDLER_H
#define KEYBOARDEVENTHANDLER_H
#include <SDL/SDL.h>
#include <string>


namespace ContinuumEngine3D {

	class ContinuumEngine;

	class KeyboardEventListener
	{
	public:
		KeyboardEventListener() = delete;
		KeyboardEventListener(const KeyboardEventListener&) = delete;
		KeyboardEventListener(KeyboardEventListener&&) = delete;
		KeyboardEventListener& operator=(const KeyboardEventListener&) = delete;
		KeyboardEventListener& operator=(KeyboardEventListener&&) = delete;
		~KeyboardEventListener();
		static void RegisterEngineObject(ContinuumEngine* engine_);
		static void Update(SDL_Event e_);

		static void onKeyDown(SDL_Event e_);
		static void onKeyHold(SDL_Event e_);
		static void onKeyReleased(SDL_Event e_);

	private:
		static ContinuumEngine * engineInstance;
	};
}
#endif