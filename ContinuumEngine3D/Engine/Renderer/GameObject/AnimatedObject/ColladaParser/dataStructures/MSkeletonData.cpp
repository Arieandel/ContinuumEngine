#include "MSkeletonData.h"


MSkeletonData::MSkeletonData() {
	jointCount = 0;
	headJoint = MJointData();
}


MSkeletonData::MSkeletonData(int jointCount_, MJointData headJoint_)
{
	jointCount = jointCount_;
	headJoint = headJoint_;
}


MSkeletonData::~MSkeletonData()
{
}
