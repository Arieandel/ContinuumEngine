#pragma once
#include <string>
#include "TextureCache.h"

namespace ContinuumEngine2D {

	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};

}