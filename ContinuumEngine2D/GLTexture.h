#pragma once
#include <OpenGL/glew.h>
#include <string>

namespace ContinuumEngine2D {

	struct GLTexture {
		std::string filePath = "";
		GLuint id;
		int width;
		int height;
	};
}