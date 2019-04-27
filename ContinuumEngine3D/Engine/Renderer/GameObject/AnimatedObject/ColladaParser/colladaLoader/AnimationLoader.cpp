#include "AnimationLoader.h"



AnimationLoader::AnimationLoader(XmlNode* animationData_, XmlNode* jointHierarchy_)
{
	glm::vec3 rotation = glm::vec3(1.0f, 0.0f, 0.0f);
	float angle = -90.0f;
	correction = glm::rotate(correction, angle, rotation);
	animationData = animationData_;
	jointHierarchy = jointHierarchy_;
}


AnimationLoader::~AnimationLoader()
{
}


MAnimationData AnimationLoader::extractAnimation() {
	std::string rootNode = findRootJointName();
	std::vector<float> times = getKeyTimes();
	float duration = times[times.size() - 1];
	std::vector<MKeyFrameData> keyFrames = initKeyFrames(times);
	std::vector<XmlNode*> animationNodes = animationData->getChildren("animation");
	for (XmlNode* jointNode : animationNodes) {
		loadJointTransforms(keyFrames, jointNode, rootNode);
	}
	return MAnimationData(duration, keyFrames);
}


std::vector<float> AnimationLoader::getKeyTimes() {
	XmlNode* timeData = animationData->getChild("animation")->getChild("source")->getChild("float_array");
	std::string rawTimes = timeData->getData();
	std::istringstream iss(rawTimes);
	std::vector<std::string> timesString((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());
	std::vector<float> times;
	for (int i = 0; i < timesString.size(); i++) {
		times[i] = std::stof(timesString[i]);
	}
	return times;
}


std::vector<MKeyFrameData> AnimationLoader::initKeyFrames(std::vector<float> times_) {

	std::vector<MKeyFrameData> frames;
	int count = times_.size();

	for (int i = 0; i < count; i++) {
		frames[i] = MKeyFrameData(times_[i]);
	}
	return frames;
}


void AnimationLoader::loadJointTransforms(std::vector<MKeyFrameData> frames_, XmlNode* jointData_, std::string rootNodeId_) {
	std::string jointNameId = getJointName(jointData_);
	std::string dataId = getDataId(jointData_);
	XmlNode* transformData = jointData_->getChildWithAttribute("source", "id", dataId);
	std::string tempRawData = transformData->getChild("float_array")->getData();

	std::istringstream iss(tempRawData);
	std::vector<std::string> rawData((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());
	processTransforms(jointNameId, rawData, frames_, jointNameId == rootNodeId_ ? true : false);
}

std::string AnimationLoader::getDataId(XmlNode* jointData_) {
	XmlNode* node = jointData_->getChild("sampler")->getChildWithAttribute("input", "semantic", "OUTPUT");
	return node->getAttribute("source").substr(1);
}

std::string AnimationLoader::getJointName(XmlNode* jointData_) {
	XmlNode* channelNode = jointData_->getChild("channel");
	std::string data = channelNode->getAttribute("target");
	const char* delim = "/";
	std::vector<std::string> targetTokens = Split(data, delim);
	return targetTokens[0];

}

void AnimationLoader::processTransforms(std::string jointName_, std::vector<std::string> rawData_, std::vector<MKeyFrameData> keyFrames_, bool root_) {
	
	glm::mat4 matrixData = glm::mat4();

	for (int i = 0; i < keyFrames_.size(); i++) {
		for (int n = 0; n < 4; n++) {
			for (int k = 0; k < 4; k++) {
				matrixData[n][k] = std::stof(rawData_[n * 4 + k]);
			}
		}
		matrixData = glm::transpose(matrixData);
		if (root_) {
			//because up axis in Blender is different to up axis in game
			matrixData = glm::rotate(matrixData, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		keyFrames_[i].addJointTransform(MJointTransformData(jointName_, matrixData));
		
	}
}

std::string AnimationLoader::findRootJointName() {
	XmlNode* skeleton = jointHierarchy->getChild("visual_scene")->getChildWithAttribute("node", "id", "Armature");
	return skeleton->getChild("node")->getAttribute("id");
}

std::vector<std::string> AnimationLoader::Split(const std::string& s_, const char* delimiter_) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s_);
	while (std::getline(tokenStream, token, *delimiter_))
	{
		tokens.push_back(token);
	}
	return tokens;
}