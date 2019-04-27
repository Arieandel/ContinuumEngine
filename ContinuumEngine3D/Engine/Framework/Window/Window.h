#ifndef WINDOW_H
#define WINDOW_H

#include <SDL/SDL.h>
#include <OpenGL/glew.h>
#include <SDL/SDL_opengl.h>

#include <string>
#include <iostream>
#include <SDL/SDL_mixer.h>

#include "../../GlobalElements/Debug.h"

namespace ContinuumEngine3D {

#define GL3PROTOTYPES 1
	class Window
	{
		enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	public:
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;


		Window();
		~Window();
		void swapBuffer();

		bool Initialize(std::string name, int width, int height, unsigned int currentFlags);
		void Shutdown();
		int GetWidth();
		int GetHeight();
		SDL_Window* GetWindow() const;
	private:
		void SetAttributes();
		int width;
		int height;
		SDL_Window* window;
		SDL_GLContext context;
	};
}
#endif // !WINDOW_H