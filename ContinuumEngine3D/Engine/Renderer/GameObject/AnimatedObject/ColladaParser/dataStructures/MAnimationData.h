#ifndef  MANINMATION_H
#define MANINMATION_H

#include "MKeyFrameData.h"

class MAnimationData
{
public:

	float lengthSeconds;
	std::vector<MKeyFrameData> keyFrames;

	MAnimationData(float lengthSeconds_, std::vector<MKeyFrameData> keyFrames_);
	~MAnimationData();
};

#endif // ! MANINMATION_H
