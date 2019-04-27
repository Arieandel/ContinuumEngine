#include "GeometryLoader.h"



GeometryLoader::GeometryLoader(XmlNode* geometryNode_, std::vector<MVertexSkinData> vertexWeights_)
{
	glm::vec3 rotation = glm::vec3(1.0f, 0.0f, 0.0f);
	float angle = -90.0f;
	correction = glm::rotate(correction, angle, rotation);

	vertexWeights = vertexWeights_;
	meshData = geometryNode_->getChild("geometry")->getChild("mesh");
}


GeometryLoader::~GeometryLoader()
{
}

MMeshData GeometryLoader::extractModelData() {
	readRawData();
	assembleVertices();
	removeUnusedVertices();
	convertDataToArrays();
	convertIndicesListToArray();
	return MMeshData(verticesArray, texturesArray, normalsArray, indicesArray, jointIdsArray, weightsArray);
}


void GeometryLoader::readRawData(){
	readPositions();
	readNormals();
	readTextureCoords();
}
void GeometryLoader::readPositions() {
	std::string positionsId = meshData->getChild("vertices")->getChild("input")->getAttribute("source").substr(1); //??
	XmlNode* positionsData = meshData->getChildWithAttribute("source", "id", positionsId)->getChild("float_array");

	int count = std::stoi(positionsData->getAttribute("count"));

	std::string posData = positionsData->getData();

	std::istringstream iss(posData);
	std::vector<std::string> posDataResults((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	for (int i = 0; i < count / 3; i++) {
		float x = std::stof(posDataResults[i * 3]);
		float y = std::stof(posDataResults[i * 3 + 1]);
		float z = std::stof(posDataResults[i * 3 + 2]);
		
		glm::vec4 position = glm::vec4(x, y, z, 1);
		position = correction * position;
		//Matrix4f.transform(CORRECTION, position, position);
		vertices.push_back(MVertex(vertices.size(), glm::vec3(position.x, position.y, position.z), vertexWeights[vertices.size()]));
	}
}
void GeometryLoader::readNormals() {
	std::string normalsId = meshData->getChild("polylist")->getChildWithAttribute("input", "semantic", "NORMAL")->getAttribute("source").substr(1);
	XmlNode* normalsData = meshData->getChildWithAttribute("source", "id", normalsId)->getChild("float_array");
	int count = std::stoi(normalsData->getAttribute("count"));
	std::string normData = normalsData->getData();

	std::istringstream iss(normData);
	std::vector<std::string> normDataResults((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	for (int i = 0; i < count / 3; i++) {
		float x = std::stof(normDataResults[i * 3]);
		float y = std::stof(normDataResults[i * 3 + 1]);
		float z = std::stof(normDataResults[i * 3 + 2]);
		glm::vec4 norm = glm::vec4(x, y, z, 0.0f);
		norm = correction * norm;
		normals.push_back(glm::vec3(norm.x, norm.y, norm.z));
	}
}
void GeometryLoader::readTextureCoords() {
	std::string texCoordsId = meshData->getChild("polylist")->getChildWithAttribute("input", "semantic", "TEXCOORD")->getAttribute("source").substr(1);
	XmlNode* texCoordsData = meshData->getChildWithAttribute("source", "id", texCoordsId)->getChild("float_array");
	int count = std::stoi(texCoordsData->getAttribute("count"));

	std::string texData = texCoordsData->getData();

	std::istringstream iss(texData);
	std::vector<std::string> texDataResults((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	for (int i = 0; i < count / 2; i++) {
		float s = std::stof(texDataResults[i * 2]);
		float t = std::stof(texDataResults[i * 2 + 1]);
		textures.push_back(glm::vec2(s, t));
	}
}
void GeometryLoader::assembleVertices() {
	XmlNode* poly = meshData->getChild("polylist");
	int typeCount = poly->getChildren("input").size();

	std::string indexData = poly->getChild("p")->getData();

	std::istringstream iss(indexData);
	std::vector<std::string> indexDataResults((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	for (int i = 0; i < indexDataResults.size() / typeCount; i++) {
		int positionIndex = std::stoi(indexDataResults[i * typeCount]);
		int normalIndex = std::stoi(indexDataResults[i * typeCount + 1]);
		int texCoordIndex = std::stoi(indexDataResults[i * typeCount + 2]);
		processVertex(positionIndex, normalIndex, texCoordIndex);
	}
}
MVertex GeometryLoader::processVertex(int posIndex_, int normIndex_, int texIndex_) {
	MVertex currentVertex = vertices[posIndex_];
	if (!currentVertex.isSet()) {
		currentVertex.setTextureIndex(texIndex_);
		currentVertex.setNormalIndex(normIndex_);
		indices.push_back(posIndex_);
		return currentVertex;
	}
	else {
		return dealWithAlreadyProcessedVertex(currentVertex, texIndex_, normIndex_);
	}
}

std::vector<int> GeometryLoader::convertIndicesListToArray() {
	std::vector<int> indicesArray_;
	for (int i = 0; i < indices.size(); i++) {
		indicesArray_.push_back(indices[i]);
	}
	return indicesArray_;
}

float GeometryLoader::convertDataToArrays() {
	float furthestPoint = 0;
	for (int i = 0; i < vertices.size(); i++) {
		MVertex currentVertex = vertices[i];
		if (currentVertex.getLength() > furthestPoint) {
			furthestPoint = currentVertex.getLength();
		}
		glm::vec3 position = currentVertex.getPosition();
		glm::vec2 textureCoord = textures[currentVertex.getTextureIndex()];
		glm::vec3 normalVector = normals[currentVertex.getNormalIndex()];
		verticesArray[i * 3] = position.x;
		verticesArray[i * 3 + 1] = position.y;
		verticesArray[i * 3 + 2] = position.z;
		texturesArray[i * 2] = textureCoord.x;
		texturesArray[i * 2 + 1] = 1 - textureCoord.y;
		normalsArray[i * 3] = normalVector.x;
		normalsArray[i * 3 + 1] = normalVector.y;
		normalsArray[i * 3 + 2] = normalVector.z;
		MVertexSkinData weights = currentVertex.getWeightsData();
		jointIdsArray[i * 3] = weights.jointIds[0];
		jointIdsArray[i * 3 + 1] = weights.jointIds[1];
		jointIdsArray[i * 3 + 2] = weights.jointIds[2];
		weightsArray[i * 3] = weights.weights[0];
		weightsArray[i * 3 + 1] = weights.weights[1];
		weightsArray[i * 3 + 2] = weights.weights[2];

	}
	return furthestPoint;
}

MVertex GeometryLoader::dealWithAlreadyProcessedVertex(MVertex previousVertex_, int newTextureIndex_, int newNormalIndex_) {
	if (previousVertex_.hasSameTextureAndNormal(newTextureIndex_, newNormalIndex_)) {
		indices.push_back(previousVertex_.getIndex());
		
		return previousVertex_;
	}
	else {
		MVertex anotherVertex = previousVertex_.getDuplicateVertex();
		if (previousVertex_.duplicateVertex != nullptr) {
			return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex_, newNormalIndex_);
		}
		else {
			MVertex duplicateVertex = MVertex(vertices.size(), previousVertex_.getPosition(), previousVertex_.getWeightsData());
			duplicateVertex.setTextureIndex(newTextureIndex_);
			duplicateVertex.setNormalIndex(newNormalIndex_);
			previousVertex_.setDuplicateVertex(duplicateVertex);
			vertices.push_back(duplicateVertex);
			indices.push_back(duplicateVertex.getIndex());
			return duplicateVertex;
		}

	}
}

void GeometryLoader::removeUnusedVertices() {
	for (MVertex vertex : vertices) {
		vertex.averageTangents();
		if (!vertex.isSet()) {
			vertex.setTextureIndex(0);
			vertex.setNormalIndex(0);
		}
	}
}