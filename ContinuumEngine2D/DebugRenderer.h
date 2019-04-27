#pragma once

#include "GLSLProgram.h"
#include "Vertex.h"
#include <OpenGL/glm/glm.hpp>
#include <vector>

namespace ContinuumEngine2D {
	class DebugRenderer {
	public:
		DebugRenderer();
		~DebugRenderer();

		void init();
		void end();
		void drawLine(const glm::vec2& a, const glm::vec2& b, const ColorRGB8& color);
		void drawBox(const glm::vec4& destRect, const ColorRGB8& color, float angle);
		void drawCircle(const glm::vec2& center, const ColorRGB8& color, float radius);
		void render(const glm::mat4& projectionMatrix, float lineWidth);
		void dispose();

		struct DebugVertex {
			glm::vec2 position;
			ContinuumEngine2D::ColorRGB8 color;
		};
	private:
		ContinuumEngine2D::GLSLProgram m_program;
		std::vector<DebugVertex> m_verts;
		std::vector<GLuint> m_indices;
		GLuint m_vbo = 0, m_vao = 0, m_ibo = 0;
		int m_numElements = 0;
	};

}