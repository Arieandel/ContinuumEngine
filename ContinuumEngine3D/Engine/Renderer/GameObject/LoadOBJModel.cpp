#include "LoadOBJModel.h"


namespace ContinuumEngine3D {

	LoadOBJModel::LoadOBJModel() : currentTexture(0) {

	}


	LoadOBJModel::~LoadOBJModel() {
		vertices.clear();
		vertices.shrink_to_fit();
		normals.clear();
		normals.shrink_to_fit();
		textureCoords.clear();
		textureCoords.shrink_to_fit();

		indices.clear();
		indices.shrink_to_fit();
		normalIndices.clear();
		normalIndices.shrink_to_fit();
		textureIndices.clear();
		textureIndices.shrink_to_fit();

		meshVertices.clear();
		meshVertices.shrink_to_fit();
		meshes.clear();
		meshes.shrink_to_fit();
	}

	void LoadOBJModel::LoadModel(const std::string& fileName_) {
		std::ifstream in(fileName_, std::ios::in);
		if (!in) {
			Debug::Error("Cannot load OBJ file: " + fileName_, __FILE__, __LINE__);
			return;
		}
		std::string line;
		tempMaxX = tempMaxY = tempMaxZ = FLT_MIN;
		tempMinX = tempMinY = tempMinZ = FLT_MAX;
		while (std::getline(in, line)) {
			//VERTEX DATA
			if (line.substr(0, 2) == "v ") {
				std::istringstream v(line.substr(2));
				double x, y, z;
				v >> x >> y >> z;
				vertices.push_back(glm::vec3(x, y, z));
				if (x > tempMaxX)
					tempMaxX = x;

				if (y > tempMaxY)
					tempMaxY = y;

				if (z > tempMaxZ)
					tempMaxZ = z;

				if (x < tempMinX)
					tempMinX = x;

				if (y < tempMinY)
					tempMinY = y;

				if (z < tempMinZ)
					tempMinZ = z;

				BoundaryBox.maxVert = glm::vec3(tempMaxX, tempMaxY, tempMaxZ);
				BoundaryBox.minVert = glm::vec3(tempMinX, tempMinY, tempMinZ);

			}
			//NORMAL DATA
			if (line.substr(0, 3) == "vn ") {
				std::istringstream vn(line.substr(2));
				double x, y, z;
				vn >> x >> y >> z;
				normals.push_back(glm::vec3(x, y, z));
			}
			//TEXTURE COORDINATE 
			if (line.substr(0, 3) == "vt ") {
				std::istringstream vt(line.substr(2));
				double x, y;
				vt >> x >> y;

				textureCoords.push_back(glm::vec2(x, y));
			}
			//FACE DATA
			///vertex/texture/normal
			if (line.substr(0, 2) == "f ") {

				bool f_flag = false;
				int indx = 0;
				while (indx < line.size() - 1) {


					std::size_t f_found = line.find("//");
					if (f_found != 4294967295) {
						f_flag = false;
						line.replace(f_found, 2, " 1 ");
					}
					else
					{
						f_flag = true;
					}

					if (f_flag == true) {
						std::size_t found = line.find("/");
						if (found != 4294967295) {
							line.replace(found, 1, " ");
						}
					}
					indx++;
				}
				std::istringstream vi(line.substr(1));
				GLuint firstTriVert;
				GLuint firstTriText;
				GLuint firstTriNorm;
				GLuint secondTriVert;
				GLuint secondTriText;
				GLuint secondTriNorm;
				GLuint thirdTriVert;
				GLuint thirdTriText;
				GLuint thirdTriNorm;
				GLuint forthTriVert;
				GLuint forthTriText;
				GLuint forthTriNorm;
				vi >> firstTriVert >> firstTriText >> firstTriNorm >> secondTriVert >> secondTriText >> secondTriNorm >> thirdTriVert >> thirdTriText >> thirdTriNorm >> forthTriVert >> forthTriText >> forthTriNorm;
				indices.push_back(GLuint(firstTriVert));
				textureIndices.push_back(GLuint(firstTriText));
				normalIndices.push_back(GLuint(firstTriNorm));
				indices.push_back(GLuint(secondTriVert));
				textureIndices.push_back(GLuint(secondTriText));
				normalIndices.push_back(GLuint(secondTriNorm));
				indices.push_back(GLuint(thirdTriVert));
				textureIndices.push_back(GLuint(thirdTriText));
				normalIndices.push_back(GLuint(thirdTriNorm));
				if (forthTriNorm != 3435973836) {
					indices.push_back(GLuint(forthTriVert));
					textureIndices.push_back(GLuint(forthTriText));
					normalIndices.push_back(GLuint(forthTriNorm));
				}

			}

			//Material Data
			else if (line.substr(0, 7) == "usemtl ") {
				if (indices.size() > 0) {
					PostProcessing();
				}
				LoadMaterial(line.substr(7));
			}
		}
		PostProcessing();
	}
	void LoadOBJModel::LoadModel(const std::string& fileName_, const std::string& matName_, bool isGlowing_, bool isParallax_) {
		isGlowing = isGlowing_;
		isParallax = isParallax_;
		if (matName_ != "Skybox") {
			LoadMaterialLibrary(matName_);
			skyboxFlag_ = false;
		}
		else {
			skyboxFlag_ = true;
		}

		LoadModel(fileName_);
	}
	std::vector<Vertex> LoadOBJModel::GetVerts() {
		return meshVertices;
	}
	std::vector<GLuint> LoadOBJModel::GetIndices() {
		return indices;
	}
	std::vector<SubMesh> LoadOBJModel::GetMeshes() {
		return meshes;
	}

	void LoadOBJModel::PostProcessing() {
		for (unsigned int i = 0; i < indices.size(); i++) {
			Vertex vert;
			vert.position = vertices[indices[i] - 1];
			vert.normal = normals[normalIndices[i] - 1];
			vert.texCoords = textureCoords[textureIndices[i] - 1];
			meshVertices.push_back(vert);
		}
		SubMesh mesh;
		mesh.vertexList = meshVertices;
		mesh.indices = indices;
		mesh.textureID = currentTexture;
		mesh.isGlowing = isGlowing;
		mesh.isParallax = isParallax;
		mesh.skyboxFlag = skyboxFlag_;
		meshes.push_back(mesh);

		indices.clear();
		indices.shrink_to_fit();
		normalIndices.clear();
		normalIndices.shrink_to_fit();
		textureIndices.clear();
		textureIndices.shrink_to_fit();

		meshVertices.clear();
		meshVertices.shrink_to_fit();

		currentTexture = 0;
	}
	void LoadOBJModel::LoadMaterial(const std::string& fileName_) {
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
		if (currentTexture == 0) {
			//
			TextureHandler::GetInstance()->CreateTexture(fileName_, "../Resources/Textures/" + fileName_ + ".jpg", isGlowing);
			currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
		}
	}
	void LoadOBJModel::LoadMaterialLibrary(const std::string matName_) {
		std::ifstream in(matName_.c_str(), std::ios::in);
		if (!in) {
			Debug::Error("Cannot open MTL file: " + matName_, __FILE__, __LINE__);
			return;
		}
		std::string line;
		while (std::getline(in, line)) {
			if (line.substr(0, 7) == "newmtl ") {
				LoadMaterial(line.substr(7));
			}
		}
	}

	BoundaryBox LoadOBJModel::GetBoundaryBox() {
		return BoundaryBox;
	}


	/*void LoadOBJModel::LoadMaterial(const std::string& fileName_)
	{
		currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
	}

	void LoadOBJModel::LoadMaterialLibrary(const std::string& materialName_)
	{
		MaterialLoader::LoadMaterial(materialName_);
	}*/

}