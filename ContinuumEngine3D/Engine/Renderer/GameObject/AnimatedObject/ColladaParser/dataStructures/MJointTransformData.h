#ifndef MJOINTTRANSFORMDATA_H
#define MJOINTTRANSFORMDATA_H

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class MJointTransformData
{
public:
	std::string jointNameId;
	glm::mat4 jointLocalTransform;
	
	MJointTransformData(std::string jointNameId_, glm::mat4 jointLocalTransform_);
	~MJointTransformData();
};

#endif