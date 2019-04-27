#ifndef MMESHDATA_H
#define MMESHDATA_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

class MMeshData
{
public:

	std::vector<float> vertices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<int> indices;
	std::vector<int> jointIds;
	std::vector<float> vertexWeights;

	std::vector<int> getJointIds();
	std::vector<float> getVertexWeights();
	std::vector<float> getVertices();
	std::vector<float> getTextureCoords();
	std::vector<float> getNormals();
	std::vector<int> getIndices();
	int getVertexCount();


	MMeshData();

	MMeshData(std::vector<float> vertices_,
	std::vector<float> textureCoords_,
	std::vector<float> normals_,
	std::vector<int> indices_,
	std::vector<int> jointIds_,
	std::vector<float> vertexWeights_);
	~MMeshData();
};

#endif

