#include "ParallaxBackground.h"


namespace ContinuumEngine3D {

	ParallaxBackground::ParallaxBackground(const char* filepath_)
	{
		loadBackground(filepath_);
	}


	ParallaxBackground::~ParallaxBackground()
	{
	}



	void ParallaxBackground::loadBackground(const char* filepath_) {
		//SDL_Texture* newTexture = NULL;
		//loadedSurface = IMG_Load(filepath_);
		//if (loadedSurface == NULL)
		//{
		//	printf("Unable to load image %s! SDL_image Error: %s\n", filepath_, IMG_GetError());
		//}

		//else
		//{
		//	//Get image dimensions
		//	mWidth = loadedSurface->w;
		//	mHeight = loadedSurface->h;
		//	

		//}
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &parallaxVAO);
		glGenBuffers(1, &parallaxVBO);
		glBindVertexArray(parallaxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, parallaxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		int width, height, nrChannels;
		unsigned char *data = stbi_load(filepath_, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << filepath_ << std::endl;
			stbi_image_free(data);
		}


	}


	void ParallaxBackground::Render(Camera* camera_) {

	}


	int ParallaxBackground::getWidth() {
		return mWidth;
	}
	int ParallaxBackground::getHeight() {
		return mHeight;
	}
	glm::vec2 ParallaxBackground::getPosition() {
		return position;
	}

}