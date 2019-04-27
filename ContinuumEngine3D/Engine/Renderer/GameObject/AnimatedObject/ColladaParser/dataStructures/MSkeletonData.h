#ifndef MSKELETONDATA_H
#define MSKELETONDATA_H


#include "MJointData.h"

class MSkeletonData
{
public:

	int jointCount;
	MJointData headJoint;


	MSkeletonData();
	MSkeletonData(int jointCount_, MJointData headJoint_);
	~MSkeletonData();
};

#endif

