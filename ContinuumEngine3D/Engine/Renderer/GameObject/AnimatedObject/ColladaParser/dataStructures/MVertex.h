#ifndef MVERTEX_H
#define MVERTEX_H

#include "MVertexSkinData.h"

class MVertex
{
public:

	MVertex(int index_, glm::vec3 position_, MVertexSkinData weightsData_);
	~MVertex();

	MVertexSkinData getWeightsData();
	void addTangent(glm::vec3 tangent);
	void averageTangents();
	glm::vec3 getAverageTangent();
	int getIndex();
	float getLength();
	bool isSet();
	bool hasSameTextureAndNormal(int textureIndexOther_, int normalIndexOther_);
	void setTextureIndex(int textureIndex_);
	void setNormalIndex(int normalIndex_);
	glm::vec3 getPosition();
	int getTextureIndex();
	int getNormalIndex();
	MVertex getDuplicateVertex();
	void setDuplicateVertex(MVertex duplicateVertex_);
	MVertex* duplicateVertex = nullptr;
	

private:
	glm::vec3 position;
	int textureIndex = -1;
	int normalIndex = -1;

	int index;
	float length;
	std::vector<glm::vec3> tangents;
	glm::vec3 averagedTangent = glm::vec3(0.0f, 0.0f, 0.0f);
	MVertexSkinData weightsData;
};

#endif
