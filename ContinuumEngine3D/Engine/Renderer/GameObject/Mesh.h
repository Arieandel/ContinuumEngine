#ifndef MESH_H
#define MESH_H

#include <OpenGL/glew.h>
#include <vector>
#include <OpenGL/glm/glm.hpp>
#include <OpenGL/glm/gtc/type_ptr.hpp>
#include <map>
#include "../../Camera/Camera.h"
#include "../../GlobalElements/Debug.h"
#include <reactPhysics/reactphysics3d.h>


namespace ContinuumEngine3D {

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	struct SubMesh {
		std::vector<Vertex> vertexList;
		std::vector<GLuint> indices;
		GLuint textureID;
		bool isGlowing;
		bool isParallax;
		bool skyboxFlag;
	};

	class Mesh
	{
	public:

		Mesh(SubMesh subMesh_, std::map<std::string, GLuint> shaderPrograms_);



		~Mesh();
		void Render(Camera* camera_, std::vector<glm::mat4> instances_, const std::string& shaderProgram_);
		void RenderMesh();

	private:
		GLuint VAO, VBO, meshVAO, meshVBO;
		void GenerateBuffers();
		SubMesh subMesh;
		std::map<std::string, GLuint> shaderPrograms;

		GLuint modelLoc, viewLoc, projLoc, textureLoc, cubeTextureLoc;
		GLuint viewPositionLoc, lightPosLoc, lightAmbientLoc, lightDiffuseLoc, lightColourLoc;
	};
}
#endif