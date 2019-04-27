#include "MAnimationData.h"



MAnimationData::MAnimationData(float lengthSeconds_, std::vector<MKeyFrameData> keyFrames_)
{
	lengthSeconds = lengthSeconds_;
	keyFrames = keyFrames_;
}


MAnimationData::~MAnimationData()
{
}
