#ifndef MJOINTDATA_H
#define MJOINTDATA_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

class MJointData
{
public:

	int index;
	std::string nameId;
	glm::mat4 bindLocalTransform;
	std::vector<MJointData> children;
	void addChild(MJointData child);
	MJointData(int index_, std::string nameId_, glm::mat4 bindLocalTransform_);
	MJointData();
	~MJointData();
};

#endif
