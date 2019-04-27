#include "MMeshData.h"


MMeshData::MMeshData() {
	vertices = std::vector<float>();
	textureCoords = std::vector<float>();
	normals = std::vector<float>();
	indices = std::vector<int>();
	jointIds = std::vector<int>();
	vertexWeights = std::vector<float>();
}


MMeshData::MMeshData(std::vector<float> vertices_,
	std::vector<float> textureCoords_,
	std::vector<float> normals_,
	std::vector<int> indices_,
	std::vector<int> jointIds_,
	std::vector<float> vertexWeights_)
{
	vertices = vertices_;
	textureCoords = textureCoords_;
	normals = normals_;
	indices = indices_;
	jointIds = jointIds_;
	vertexWeights = vertexWeights_;
}


MMeshData::~MMeshData()
{
}


std::vector<int> MMeshData::getJointIds(){
	return jointIds;
}
std::vector<float> MMeshData::getVertexWeights() {
	return vertexWeights;
}
std::vector<float> MMeshData::getVertices() {
	return vertices;
}
std::vector<float> MMeshData::getTextureCoords() {
	return textureCoords;
}
std::vector<float> MMeshData::getNormals() {
	return normals;
}
std::vector<int> MMeshData::getIndices() {
	return indices;
}
int MMeshData::getVertexCount() {
	return vertices.size();
}