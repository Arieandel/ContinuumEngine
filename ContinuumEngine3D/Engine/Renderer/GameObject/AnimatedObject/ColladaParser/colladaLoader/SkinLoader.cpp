#include "SkinLoader.h"



SkinLoader::SkinLoader(XmlNode* controllersNode, int maxWeights_)
{
	skinningData = controllersNode->getChild("controller")->getChild("skin");
	maxWeights = maxWeights_;
}


SkinLoader::~SkinLoader()
{
}


MSkinningData SkinLoader::extractSkinData() {
	std::vector<std::string> jointList = loadJointsList();
	std::vector<float> weights = loadWeights();
	XmlNode* weightsDataNode = skinningData->getChild("vertex_weights");
	std::vector<int> effectorJointCounts = getEffectiveJointsCounts(weightsDataNode);
	std::vector<MVertexSkinData> vertexWeights = getSkinData(weightsDataNode, effectorJointCounts, weights);
	return MSkinningData(jointList, vertexWeights);

}

std::vector<std::string> SkinLoader::loadJointsList() {
	XmlNode* inputNode = skinningData->getChild("vertex_weights");
	std::string jointDataId = inputNode->getChildWithAttribute("input", "semantic", "JOINT")->getAttribute("source").substr(1);
	XmlNode* jointsNode = skinningData->getChildWithAttribute("source", "id", jointDataId)->getChild("Name_array");
	std::string names = jointsNode->getData();
	std::istringstream iss(names);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());
	return results;
}

std::vector<float> SkinLoader::loadWeights() {
	XmlNode* inputNode = skinningData->getChild("vertex_weights");
	std::string weightsDataId = inputNode->getChildWithAttribute("input", "semantic", "WEIGHT")->getAttribute("source").substr(1);
	XmlNode* weightNode = skinningData->getChildWithAttribute("source", "id", weightsDataId)->getChild("float_array");
	std::string names = weightNode->getData();
	std::istringstream iss(names);
	std::vector<std::string> temp((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());
	std::vector<float> results;
	for (int i = 0; i < temp.size(); i++) {
		results.push_back(std::stof(temp[i]));
	}
	return results;

}

std::vector<int> SkinLoader::getEffectiveJointsCounts(XmlNode* weightsDataNode_) {
	std::string rawData = weightsDataNode_->getChild("vcount")->getData();
	std::istringstream iss(rawData);
	std::vector<std::string> temp((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());
	std::vector<int> counts;
	for (int i = 0; i < temp.size(); i++) {
		counts.push_back(std::stoi(temp[i]));
	}
	return counts;
}


std::vector<MVertexSkinData>  SkinLoader::getSkinData(XmlNode* weightsDataNode_, std::vector<int> counts_, std::vector<float> weights_) {
	std::string rawData = weightsDataNode_->getChild("v")->getData();
	std::istringstream iss(rawData);
	std::vector<std::string> temp((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());
	std::vector<MVertexSkinData> skinningData;
	int pointer = 0;
	for (int count : counts_) {
		MVertexSkinData skinData;
		for (int i = 0; i < count; i++) {
			int jointId = std::stoi(temp[pointer++]);
			int weightId = std::stoi(temp[pointer++]);
			skinData.addJointEffect(jointId, weights_[weightId]);
		}
		skinData.limitJointNumber(maxWeights);
		skinningData.push_back(skinData);
	}
	return skinningData;

}