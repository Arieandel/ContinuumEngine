#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace ContinuumEngine2D {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}


	GLTexture TextureCache::getTexture(std::string texturePath) {

		//lookup texture and see if it is in the map
		auto mit = _textureMap.find(texturePath);

		//check if it is not in the map
		if (mit == _textureMap.end()) {
			//load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//insert it into map
			_textureMap.insert(make_pair(texturePath, newTexture));

			std::cout << "Loaded texture\n";
			return newTexture;
		}

		//return second value from mit
		std::cout << "Loaded cached texture\n";
		return mit->second;

	}

}