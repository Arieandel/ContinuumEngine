#ifndef MVERTEXSKINDATA_H
#define MVERTEXSKINDATA_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

class MVertexSkinData
{
public:

	std::vector<int> jointIds;
	std::vector<float> weights;

	void addJointEffect(int jointId, float weight);
	void limitJointNumber(int max);
	float saveTopWeights(std::vector<float> topWeights);
	void refillWeightList(std::vector<float> topWeights, float total);
	void removeExcessJointIds(int max);
	void fillEmptyWeights(int max);


	MVertexSkinData();
	~MVertexSkinData();
};

#endif
