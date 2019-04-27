#ifndef BoundaryBox_H
#define BoundaryBox_H

#include <OpenGL/glm/glm.hpp>


namespace ContinuumEngine3D {

	struct BoundaryBox {
		glm::vec3 minVert;
		glm::vec3 maxVert;
		glm::vec3 xyZ;
		glm::vec3 xYz;
		glm::vec3 Xyz;
		glm::vec3 xYZ;
		glm::vec3 XyZ;
		glm::vec3 XYz;
		glm::vec3 transform;
		std::vector<glm::vec3> vertexPos;
		float xSize;
		float ySize;
		float zSize;


		inline BoundaryBox() {
			minVert = glm::vec3(0.0f);
			maxVert = glm::vec3(0.0f);
			xyZ = glm::vec3(0.0f);
			xYz = glm::vec3(0.0f);
			Xyz = glm::vec3(0.0f);
			xYZ = glm::vec3(0.0f);
			XyZ = glm::vec3(0.0f);
			XYz = glm::vec3(0.0f);
			transform = glm::vec3(0.0f);
			xSize = 0.0f;
			ySize = 0.0f;
			zSize = 0.0f;
		}


		inline void CalculateBoundaryBox() {
			xyZ = glm::vec3(minVert.x, minVert.y, maxVert.z);
			xYz = glm::vec3(minVert.x, maxVert.y, minVert.z);
			Xyz = glm::vec3(maxVert.x, minVert.y, minVert.z);
			xYZ = glm::vec3(minVert.x, maxVert.y, maxVert.z);
			XyZ = glm::vec3(maxVert.x, minVert.y, maxVert.z);
			XYz = glm::vec3(maxVert.x, maxVert.y, minVert.z);
			xSize = maxVert.x - xYZ.x;
			ySize = maxVert.y - XyZ.y;
			zSize = maxVert.z - XYz.z;
		}

		inline BoundaryBox(glm::vec3 minVert_, glm::vec3 maxVert_, glm::vec3 transform_) {
			transform = transform_;
			minVert = minVert_;
			maxVert = maxVert_;
			xyZ = glm::vec3(minVert.x, minVert.y, maxVert.z);
			xYz = glm::vec3(minVert.x, maxVert.y, minVert.z);
			Xyz = glm::vec3(maxVert.x, minVert.y, minVert.z);
			xYZ = glm::vec3(minVert.x, maxVert.y, maxVert.z);
			XyZ = glm::vec3(maxVert.x, minVert.y, maxVert.z);
			XYz = glm::vec3(maxVert.x, maxVert.y, minVert.z);

			//top
			vertexPos.push_back(xYz);
			vertexPos.push_back(XYz);
			vertexPos.push_back(maxVert);
			vertexPos.push_back(xYZ);

			//front
			vertexPos.push_back(xYz);
			vertexPos.push_back(XYz);
			vertexPos.push_back(Xyz);
			vertexPos.push_back(minVert);

			//left
			vertexPos.push_back(xYz);
			vertexPos.push_back(minVert);
			vertexPos.push_back(xyZ);
			vertexPos.push_back(xYZ);

			//back
			vertexPos.push_back(xYZ);
			vertexPos.push_back(xyZ);
			vertexPos.push_back(XyZ);
			vertexPos.push_back(maxVert);

			//right
			vertexPos.push_back(maxVert);
			vertexPos.push_back(XyZ);
			vertexPos.push_back(Xyz);
			vertexPos.push_back(XYz);

			//bottom
			vertexPos.push_back(Xyz);
			vertexPos.push_back(minVert);
			vertexPos.push_back(xyZ);
			vertexPos.push_back(XyZ);



		}
	};

}
#endif