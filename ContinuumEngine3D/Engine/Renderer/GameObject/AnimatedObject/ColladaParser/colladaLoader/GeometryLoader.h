#ifndef GEOMETRYLOADER_H
#define GEOMETRYLOADER_H

#include "../dataStructures/MMeshData.h"
#include "../dataStructures/MVertex.h"
#include "../dataStructures/MVertexSkinData.h"
#include "../xmlParser/XmlNode.h"

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <sstream>

class GeometryLoader
{
public:

	glm::mat4 correction;

	XmlNode* meshData;
	std::vector<MVertexSkinData> vertexWeights;
	std::vector<float> verticesArray;
	std::vector<float> normalsArray;
	std::vector<float> texturesArray;
	std::vector<int> indicesArray;
	std::vector<int> jointIdsArray;
	std::vector<float> weightsArray;

	std::vector<MVertex> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;


	MMeshData extractModelData();
	void readRawData();
	void readPositions();
	void readNormals();
	void readTextureCoords();
	void assembleVertices();
	MVertex processVertex(int posIndex_, int normIndex_, int texIndex_);
	std::vector<int> convertIndicesListToArray();
	float convertDataToArrays();
	MVertex dealWithAlreadyProcessedVertex(MVertex previousVertex_, int newTextureIndex_, int newNormalIndex_);
	void removeUnusedVertices();
	


	GeometryLoader(XmlNode* geometryNode_, std::vector<MVertexSkinData> vertexWeights_);
	~GeometryLoader();
};

#endif