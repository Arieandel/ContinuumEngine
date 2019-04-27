#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"



namespace ContinuumEngine3D {

	class GameObject
	{
	public:
		GameObject(ContinuumEngine3D::Model* model_);
		GameObject(Model* model_, glm::vec3 position_);
		~GameObject();

		void SetPosition(glm::vec3 position_);
		void SetAngle(float angle_);
		void SetRotation(glm::vec3 rotation_);
		void SetScale(glm::vec3 scale_);
		void RenderBoundary();

		Model* GetModel() const;
		glm::vec3 GetPosition() const;
		float GetAngle() const;
		glm::vec3 GetRotation() const;
		glm::vec3 GetScale() const;
		rp3d::CollisionBody* getBody() const;
		GLuint modelInstance;
		rp3d::CollisionBody* mBody;
		Model* model;
		void updateBody();

		BoundaryBox GetBoundaryBox();

		rp3d::BoxShape* boxShape;

		rp3d::Transform mPreviousTransform;
		rp3d::ProxyShape* mProxyShape;

		GLuint boundaryVAO, boundaryVBO;
		void deleteInstance();
	private:
		glm::vec3 position;
		float angle;
		glm::vec3 rotation;
		glm::vec3 scale;


		BoundaryBox BoundaryBox;

		glm::mat4 scaleMatrix;
	};
}
#endif