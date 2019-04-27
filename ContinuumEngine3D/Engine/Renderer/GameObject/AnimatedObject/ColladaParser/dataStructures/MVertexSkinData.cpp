#include "MVertexSkinData.h"



MVertexSkinData::MVertexSkinData()
{
}


MVertexSkinData::~MVertexSkinData()
{
}


void MVertexSkinData::addJointEffect(int jointId, float weight) {
	for (int i = 0; i < weights.size(); i++) {
		if (weight > weights[i]) {
			jointIds[i] = jointId;
			weights[i] = weight;
			return;
		}
	}
	jointIds.push_back(jointId);
	weights.push_back(weight);
}

void  MVertexSkinData::fillEmptyWeights(int max) {
	while (jointIds.size() < max) {
		jointIds.push_back(0);
		weights.push_back(0.0f);
	}
}
float  MVertexSkinData::saveTopWeights(std::vector<float> topWeights) {
	float total = 0;
	for (int i = 0; i < topWeights.size(); i++) {
		topWeights[i] = weights[i];
		total += topWeights[i];
	}
	return total;

}
void MVertexSkinData::refillWeightList(std::vector<float> topWeights, float total) {
	weights.clear();
	weights.shrink_to_fit();
	for (int i = 0; i < topWeights.size(); i++) {
		
		weights.push_back(fminf(topWeights[i] / total, 1.0f));
	}
}

void MVertexSkinData::removeExcessJointIds(int max) {
	while (jointIds.size() > max) {
		jointIds.pop_back();
	}
}

void  MVertexSkinData::limitJointNumber(int max) {
	if (jointIds.size() > max) {
		std::vector<float> topWeights;
		for (int i = 0; i < max; i++) {
			topWeights.push_back(0.0f);
		}
		float total = saveTopWeights(topWeights);
		refillWeightList(topWeights, total);
		removeExcessJointIds(max);
	}
	else if (jointIds.size() < max) {
		fillEmptyWeights(max);
	}
}


