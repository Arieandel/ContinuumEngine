#ifndef MANIMATEDMODELDATA_H
#define MANIMATEDMODELDATA_H

#include "MSkeletonData.h"
#include "MMeshData.h"


class MAnimatedModelData
{
public:


	MSkeletonData joints;
	MMeshData mesh;

	MSkeletonData getJointsData();
	MMeshData getMeshData();

	MAnimatedModelData(MMeshData mesh_, MSkeletonData joints_);
	~MAnimatedModelData();


};

#endif