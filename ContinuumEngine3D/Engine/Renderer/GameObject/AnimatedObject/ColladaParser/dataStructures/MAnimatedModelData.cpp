#include "MAnimatedModelData.h"



MAnimatedModelData::MAnimatedModelData(MMeshData mesh_, MSkeletonData joints_)
{
	joints = joints_;
	mesh = mesh_;
}


MAnimatedModelData::~MAnimatedModelData()
{
}



MSkeletonData MAnimatedModelData::getJointsData() {
	return joints;
}
MMeshData MAnimatedModelData::getMeshData() {
	return mesh;
}