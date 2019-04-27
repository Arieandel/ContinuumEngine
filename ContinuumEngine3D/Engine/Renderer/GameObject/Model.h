#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
#include <OpenGL/glm/gtc/matrix_transform.hpp>
#include "LoadOBJModel.h"
#include "../Graphics/ShaderHandler.h"


namespace ContinuumEngine3D {

	class Model
	{
	public:
		Model(const std::string& objPath_, const std::string& matPath_, const std::string& shaderProgram_, bool isGlowing_, bool isParallax_);
		~Model();
		void Render(Camera* camera_, const std::string& shaderProgram_);
		void AddMesh(Mesh* mesh_);
		GLuint CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
		void DeleteInstance(GLuint index_);
		void UpdateInstance(GLuint index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
		glm::mat4 GetTransform(GLuint index_) const;
		BoundaryBox GetBoundaryBox();
		BoundaryBox BoundaryBox;
		bool isGlowing;
		bool isParallax;
		std::vector<glm::mat4> modelInstances;
		std::string name;

	private:
		std::vector<Mesh*> subMeshes;
		std::map<std::string, GLuint> shaderProgram;
		glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
		void LoadModel();


		LoadOBJModel* obj;


	};
}
#endif // !MODEL_H