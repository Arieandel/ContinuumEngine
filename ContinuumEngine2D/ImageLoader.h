#pragma once
#include <string>

#include "GLTexture.h"

namespace ContinuumEngine2D {

	class ImageLoader
	{
	public:

		static GLTexture loadPNG(std::string filePath);


	};

}