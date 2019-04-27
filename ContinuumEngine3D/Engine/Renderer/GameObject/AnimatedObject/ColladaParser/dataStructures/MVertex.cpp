#include "MVertex.h"



MVertex::MVertex(int index_, glm::vec3 position_, MVertexSkinData weightsData_)
{
	index = index_;
	weightsData = weightsData_;
	position = position_;
	length = position.length();

}


MVertex::~MVertex()
{
}


MVertexSkinData MVertex::getWeightsData() {
	return weightsData;
}

void MVertex::addTangent(glm::vec3 tangent) {
	tangents.push_back(tangent);
}

void  MVertex::averageTangents() {
	if (tangents.empty()) {
		return;
	}
	for (glm::vec3 tangent : tangents) {
		averagedTangent += tangent;
	}
	float averagedMag = std::sqrt((averagedTangent.x * averagedTangent.x) + (averagedTangent.y * averagedTangent.y) + (averagedTangent.z * averagedTangent.z));
	averagedTangent /= averagedMag;
}

glm::vec3 MVertex::getAverageTangent() {
	return averagedTangent;
}

int MVertex::getIndex() {
	return index;
}

float MVertex::getLength() {
	return length;
}

bool MVertex::isSet() {
	return textureIndex != -1 && normalIndex != -1;
}

bool MVertex::hasSameTextureAndNormal(int textureIndexOther_, int normalIndexOther_) {
	return textureIndexOther_ == textureIndex && normalIndexOther_ == normalIndex;
}

void MVertex::setTextureIndex(int textureIndex_) {
	textureIndex = textureIndex_;
}

void MVertex::setNormalIndex(int normalIndex_) {
	normalIndex = normalIndex_;
}
glm::vec3 MVertex::getPosition() {
	return position;
}

int MVertex::getTextureIndex() {
	return textureIndex;
}

int MVertex::getNormalIndex() {
	return normalIndex;
}

MVertex MVertex::getDuplicateVertex() {
	return *duplicateVertex;
}

void MVertex::setDuplicateVertex(MVertex duplicateVertex_) {
	duplicateVertex = &duplicateVertex_;
}
