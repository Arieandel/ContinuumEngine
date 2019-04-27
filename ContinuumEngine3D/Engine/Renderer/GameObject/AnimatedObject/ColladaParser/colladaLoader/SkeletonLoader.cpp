#include "SkeletonLoader.h"



SkeletonLoader::SkeletonLoader(XmlNode* visualSceneNode_, std::vector<std::string> boneOrder_)
{
	jointCount = 0;
	glm::vec3 rotation = glm::vec3(1.0f, 0.0f, 0.0f);
	float angle = -90.0f;
	correction = glm::rotate(correction, angle, rotation);
	armatureData = visualSceneNode_->getChild("visual_scene")->getChildWithAttribute("node", "id", "Armature");
	boneOrder = boneOrder_;
}


SkeletonLoader::~SkeletonLoader()
{
}


MSkeletonData SkeletonLoader::extractBoneData() {
	XmlNode* headNode = armatureData->getChild("node");
	MJointData headJoint = loadJointData(headNode, true);
	return MSkeletonData(jointCount, headJoint);
}


MJointData SkeletonLoader::loadJointData(XmlNode* jointNode_, bool isRoot_) {

	MJointData joint = extractMainJointData(jointNode_, isRoot_);
	for (XmlNode* childNode : jointNode_->getChildren("node")) {
		joint.addChild(loadJointData(childNode, false));
	}
	return joint;
}


MJointData SkeletonLoader::extractMainJointData(XmlNode* jointNode_, bool isRoot_) {

	std::string nameId = jointNode_->getAttribute("id");

	std::vector<std::string>::iterator it = std::find(boneOrder.begin(), boneOrder.end(), nameId);
	int index;
	if (it != boneOrder.end())
	{
		// Get index of element from iterator
		index = std::distance(boneOrder.begin(), it);
	}

	std::string matrixData = jointNode_->getChild("matrix")->getData();

	std::istringstream iss(matrixData);
	std::vector<std::string> matrixDataResults((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	int Mindex = 0;
	glm::mat4 matrix = glm::mat4();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = std::stof(matrixDataResults[Mindex]);
			Mindex++;
		}
		
	}

	matrix = glm::transpose(matrix);

	if (isRoot_) {
		//because in Blender z is up, but in our game y is up.
		matrix = correction * matrix;
	}

	jointCount++;
	return MJointData(index, nameId, matrix);
}


