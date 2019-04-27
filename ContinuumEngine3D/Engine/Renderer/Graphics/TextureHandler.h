#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <memory>
#include <string>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <OpenGL/glew.h>

#include "../../GlobalElements/Debug.h"


namespace ContinuumEngine3D {

	struct Texture {
		GLuint textureID = 0;
		float width = 0.0f;
		float height = 0.0f;
	};

	class TextureHandler
	{
	public:
		TextureHandler(const TextureHandler&) = delete;
		TextureHandler(TextureHandler&&) = delete;
		TextureHandler& operator=(const TextureHandler&) = delete;
		TextureHandler& operator=(TextureHandler&&) = delete;
		static TextureHandler* GetInstance();
		void CreateTexture(const std::string& textureName_, const std::string& textureFilePath_, bool isGlowing_);
		static const GLuint GetTexture(const std::string& textureName_);
		static const Texture* GetTextureData(const std::string& textureName_);
		bool isGlowing = false;

	private:
		TextureHandler();
		~TextureHandler();


		static std::unique_ptr<TextureHandler> textureInstance;
		friend std::default_delete<TextureHandler>;

		static std::map<std::string, Texture*> textures;
	};
}
#endif