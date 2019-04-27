#ifndef SKINLOADER_H
#define SKINLOADER_H


#include "../xmlParser/XmlNode.h"
#include "../dataStructures/MSkinningData.h"
#include "../dataStructures/MVertexSkinData.h"
#include <iostream>
#include <sstream>
#include <iterator>

class SkinLoader
{
public:

	XmlNode* skinningData;
	int maxWeights;

	MSkinningData extractSkinData();
	std::vector<std::string> loadJointsList();
	std::vector<float> loadWeights();
	std::vector<int> getEffectiveJointsCounts(XmlNode* weightsDataNode_);

	std::vector<MVertexSkinData> getSkinData(XmlNode* weightsDataNode_, std::vector<int> counts_, std::vector<float> weights_);

	SkinLoader(XmlNode* controllersNode, int maxWeights_);
	~SkinLoader();
};

#endif
