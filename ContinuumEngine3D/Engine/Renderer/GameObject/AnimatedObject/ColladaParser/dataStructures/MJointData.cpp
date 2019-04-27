#include "MJointData.h"


MJointData::MJointData() {
	index = 0;
	nameId = "";
	bindLocalTransform = glm::mat4();
}
MJointData::MJointData(int index_, std::string nameId_, glm::mat4 bindLocalTransform_)
{
	index = index_;
	nameId = nameId_;
	bindLocalTransform = bindLocalTransform_;
}


MJointData::~MJointData()
{
}


void MJointData::addChild(MJointData child) {
	children.push_back(child);
}