#ifndef MKEYFRAMEDATA_H
#define MKEYFRAMEDATA_H
#include "MJointTransformData.h"

class MKeyFrameData
{
public:

	float time;
	std::vector<MJointTransformData> jointTransforms;

	void addJointTransform(MJointTransformData transform_);


	MKeyFrameData(float time_);
	~MKeyFrameData();
};

#endif