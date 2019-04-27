#ifndef SKELETONLOADER_H
#define SKELETONLOADER_H

#include "../xmlParser/XmlNode.h"
#include "../dataStructures/MSkeletonData.h"
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <sstream>


class SkeletonLoader
{
public:

	XmlNode* armatureData;
	std::vector<std::string> boneOrder;
	int jointCount;
	glm::mat4 correction;

	MSkeletonData extractBoneData();
	MJointData loadJointData(XmlNode* jointNode_, bool isRoot_);
	MJointData extractMainJointData(XmlNode* jointNode_, bool isRoot_);

	SkeletonLoader(XmlNode* visualSceneNode_, std::vector<std::string> boneOrder_);
	~SkeletonLoader();
};

#endif