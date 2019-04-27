#include "ColladaLoader.h"



ColladaLoader::ColladaLoader()
{
}


ColladaLoader::~ColladaLoader()
{
}



MAnimatedModelData ColladaLoader::loadColladaModel(MyFile colladaFile_, int maxWeights_) {

	XmlNode* node = parser.loadXmlFile(colladaFile_);
	SkinLoader skinLoader(node->getChild("library_controllers"), maxWeights_);
	MSkinningData skinningData = skinLoader.extractSkinData();

	SkeletonLoader jointsLoader(node->getChild("library_visual_scenes"), skinningData.jointOder);
	MSkeletonData jointsData = jointsLoader.extractBoneData();

	GeometryLoader g(node->getChild("library_geometries"), skinningData.verticesSkinData);
	MMeshData meshData = g.extractModelData();

	MAnimatedModelData newAMD(meshData, jointsData);
	return newAMD;
}


MAnimationData ColladaLoader::loadColladaAnimation(MyFile colladaFile_) {

	XmlNode* node = parser.loadXmlFile(colladaFile_);
	XmlNode* animNode = node->getChild("library_animations");
	XmlNode* jointsNode = node->getChild("library_visual_scenes");
	AnimationLoader loader = AnimationLoader(animNode, jointsNode);
	MAnimationData animData = loader.extractAnimation();
	return animData;
}