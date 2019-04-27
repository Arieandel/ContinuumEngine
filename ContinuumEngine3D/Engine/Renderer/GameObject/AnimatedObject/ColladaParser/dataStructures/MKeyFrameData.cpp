#include "MKeyFrameData.h"



MKeyFrameData::MKeyFrameData(float time_)
{
	time = time_;
}


MKeyFrameData::~MKeyFrameData()
{
}


void MKeyFrameData::addJointTransform(MJointTransformData transform_) {
	jointTransforms.push_back(transform_);
}