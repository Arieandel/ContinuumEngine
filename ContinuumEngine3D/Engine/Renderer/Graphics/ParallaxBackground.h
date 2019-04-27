#ifndef PARALLAXBACKGROUND_H
#define PARALLAXBACKGROUND_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string>
#include <OpenGL/glm/glm.hpp>
#include <OpenGL/stb_image.h>
#include "../GameObject/GameObject.h"


namespace ContinuumEngine3D {

	class ParallaxBackground
	{
	public:
		ParallaxBackground(const char* filepath_);
		~ParallaxBackground();

		ParallaxBackground(const ParallaxBackground&) = delete;
		ParallaxBackground(ParallaxBackground&&) = delete;
		ParallaxBackground& operator=(const ParallaxBackground&) = delete;
		ParallaxBackground& operator=(ParallaxBackground&&) = delete;
		void loadBackground(const char* filepath_);
		int getWidth();
		int getHeight();
		glm::vec2 getPosition();

		void Render(Camera* camera_);
		unsigned int textureID;

		SDL_Surface* textSurface;
		int mWidth;
		int mHeight;
		glm::vec2 position;
		SDL_Surface* loadedSurface;

		unsigned int parallaxVAO, parallaxVBO;


	};
}
#endif
