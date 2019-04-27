#include "ContinuumEngine2D.h"
#include <SDL/SDL.h>
#include<OpenGL/glew.h>

namespace ContinuumEngine2D {

	int init() {
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}