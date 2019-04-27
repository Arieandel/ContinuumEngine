#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include "Mesh.h"
#include "../Graphics/TextureHandler.h"
#include <sstream>
#include "BoundaryBox/BoundaryBox.h"


namespace ContinuumEngine3D {

	class LoadOBJModel
	{
	public:
		LoadOBJModel();
		~LoadOBJModel();

		void LoadModel(const std::string& fileName_);
		void LoadModel(const std::string& fileName_, const std::string& matName_, bool isGlowing_, bool isParallax_);
		std::vector<Vertex> GetVerts();
		std::vector<GLuint> GetIndices();
		std::vector<SubMesh> GetMeshes();
		BoundaryBox GetBoundaryBox();
		float tempMaxX, tempMaxY, tempMaxZ;// = -999999.0f;
		float tempMinX, tempMinY, tempMinZ; //= 999999.0f;
		BoundaryBox BoundaryBox;
		bool isGlowing = false;
		bool isParallax = false;
		bool skyboxFlag_ = false;

	private:
		void PostProcessing();
		void LoadMaterial(const std::string& fileName_);
		void LoadMaterialLibrary(const std::string matName_);
		GLuint currentTexture;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureCoords;

		std::vector<GLuint> indices;
		std::vector<GLuint> normalIndices;
		std::vector<GLuint> textureIndices;

		std::vector<Vertex> meshVertices;
		std::vector<SubMesh> meshes;

	};

}
#endif