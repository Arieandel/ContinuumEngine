#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H

#include "../xmlParser/XmlNode.h"
#include "../dataStructures/MKeyFrameData.h"
#include "../dataStructures/MAnimationData.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <sstream>


class AnimationLoader
{
public:
	glm::mat4 correction;

	XmlNode* animationData;
	XmlNode* jointHierarchy;
	
	AnimationLoader(XmlNode* animationData_, XmlNode* jointHierarchy_);
	~AnimationLoader();

	MAnimationData extractAnimation();
	std::vector<float> getKeyTimes();
	std::vector<MKeyFrameData> initKeyFrames(std::vector<float> times_);
	void loadJointTransforms(std::vector<MKeyFrameData> frames_, XmlNode* jointData_, std::string rootNodeId_);
	std::string getDataId(XmlNode* jointData_);
	std::string getJointName(XmlNode* jointData_);
	void processTransforms(std::string jointName_, std::vector<std::string> rawData_, std::vector<MKeyFrameData> keyFrames_, bool root_);
	std::string findRootJointName();
	std::vector<std::string> Split(const std::string& s_, const char* delimiter_);

};

#endif