#include "MJointTransformData.h"



MJointTransformData::MJointTransformData(std::string jointNameId_, glm::mat4 jointLocalTransform_)
{
	jointNameId = jointNameId_;
	jointLocalTransform = jointLocalTransform_;
}


MJointTransformData::~MJointTransformData()
{
}
