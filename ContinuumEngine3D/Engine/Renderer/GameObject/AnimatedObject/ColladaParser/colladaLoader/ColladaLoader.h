#ifndef COLLADALOADER_H
#define COLLADALOADER_H

#include "../dataStructures/MAnimatedModelData.h"
#include "../xmlParser/XmlParser.h"
#include "SkinLoader.h"
#include "SkeletonLoader.h"
#include "GeometryLoader.h"
#include "AnimationLoader.h"

class ColladaLoader
{
public:
	XmlParser parser;
	MAnimatedModelData loadColladaModel(MyFile colladaFile_, int maxWeights_);
	MAnimationData loadColladaAnimation(MyFile colladaFile_);
	ColladaLoader();
	~ColladaLoader();

};

#endif