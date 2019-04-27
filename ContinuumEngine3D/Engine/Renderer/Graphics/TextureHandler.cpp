#include "TextureHandler.h"
#define STB_IMAGE_IMPLEMENTATION
#include <OpenGL/stb_image.h>


namespace ContinuumEngine3D {

	std::unique_ptr<TextureHandler> TextureHandler::textureInstance = nullptr;
	std::map<std::string, Texture*> TextureHandler::textures = std::map<std::string, Texture*>();

	TextureHandler::TextureHandler()
	{
	}


	TextureHandler::~TextureHandler()
	{
		if (textures.size() > 0) {
			for (auto t : textures) {
				glDeleteTextures(sizeof(GLuint), &t.second->textureID);
				delete t.second;
				t.second = nullptr;
			}
			textures.clear();
			
		}
	}


	TextureHandler* TextureHandler::GetInstance() {
		if (textureInstance.get() == nullptr) {
			textureInstance.reset(new TextureHandler);
		}
		return textureInstance.get();
	}


	void TextureHandler::CreateTexture(const std::string& textureName_, const std::string& textureFilePath_, bool isGlowing_) {
		isGlowing = isGlowing_;
		Texture* t = new Texture();

		int mode = GL_RGBA;
		int width, height, nrComponents;
		unsigned char *data = stbi_load(textureFilePath_.c_str(), &width, &height, &nrComponents, 0);
		t->width = width;
		t->height = height;
		glGenTextures(1, &t->textureID);
		glBindTexture(GL_TEXTURE_2D, t->textureID);
		if (data)
		{
			GLenum internalFormat;
			GLenum dataFormat;
			if (nrComponents == 1)
			{
				internalFormat = dataFormat = GL_RED;
			}
			else if (nrComponents == 3)
			{
				internalFormat = isGlowing ? GL_SRGB : GL_RGB;
				dataFormat = GL_RGB;
			}
			else if (nrComponents == 4)
			{
				internalFormat = isGlowing ? GL_SRGB_ALPHA : GL_RGBA;
				dataFormat = GL_RGBA;
			}


			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//!!
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//!!
			//glBindTexture(GL_TEXTURE_2D, 0);//!!texture.cpp
			//glBindTexture(GL_TEXTURE_2D, t->textureID);
			textures[textureName_] = t;
			//SDL_FreeSurface(surface);
			stbi_image_free(data);
			//surface = nullptr;
		}
		else
		{
			std::cout << "Texture failed to load at path: " << textureFilePath_.c_str() << std::endl;
			stbi_image_free(data);
		}


	}

	const GLuint TextureHandler::GetTexture(const std::string& textureName_) {
		if (textures.find(textureName_.c_str()) != textures.end()) {
			return textures[textureName_]->textureID;
		}
		return 0;
	}
	const Texture* TextureHandler::GetTextureData(const std::string& textureName_) {

		if (textures.find(textureName_.c_str()) != textures.end()) {
			return textures[textureName_];
		}
		return 0;
	}

}