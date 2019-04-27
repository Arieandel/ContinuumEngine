#include "GameObject.h"
#include "../../ContinuumEngine.h"


namespace ContinuumEngine3D {

	GameObject::GameObject(ContinuumEngine3D::Model* model_) : position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)) {
		model = model_;
		if (model) {
			modelInstance = model->CreateInstance(position, angle, rotation, scale);
			BoundaryBox = model->GetBoundaryBox();
			BoundaryBox.transform = glm::vec3(model->GetTransform(modelInstance)[3][0], model->GetTransform(modelInstance)[3][1], model->GetTransform(modelInstance)[3][2]);
			BoundaryBox.CalculateBoundaryBox();
			boxShape = new rp3d::BoxShape(rp3d::Vector3(BoundaryBox.xSize / 2.0f, BoundaryBox.ySize / 2.0f, BoundaryBox.zSize / 2.0f));
			mPreviousTransform = rp3d::Transform::identity();
			mBody = ContinuumEngine::GetInstance()->world->createCollisionBody(mPreviousTransform);
			mProxyShape = mBody->addCollisionShape(boxShape, rp3d::Transform::identity());
			updateBody();






		}
	}

	GameObject::GameObject(Model* model_, glm::vec3 position_) : position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)) {
		model = model_;
		position = position_;
		if (model) {
			modelInstance = model->CreateInstance(position, angle, rotation, scale);
			BoundaryBox = model->GetBoundaryBox();
			BoundaryBox.transform = glm::vec3(model->GetTransform(modelInstance)[3][0], model->GetTransform(modelInstance)[3][1], model->GetTransform(modelInstance)[3][2]);
			BoundaryBox.CalculateBoundaryBox();

			boxShape = new rp3d::BoxShape(rp3d::Vector3(BoundaryBox.xSize / 2.0f, BoundaryBox.ySize / 2.0f, BoundaryBox.zSize / 2.0f));

			mPreviousTransform = rp3d::Transform::identity();
			mPreviousTransform.setPosition(ContinuumEngine::GetInstance()->ConvertglmV3_to_rpV3(position_));

			mBody = ContinuumEngine::GetInstance()->world->createCollisionBody(mPreviousTransform);
			mProxyShape = mBody->addCollisionShape(boxShape, rp3d::Transform::identity());
			updateBody();
		}
	}


	GameObject::~GameObject() {
		if (model) {
		delete model;
		}
		model = nullptr;
		mBody = nullptr;
		model = nullptr;
		boxShape = nullptr;
		mProxyShape = nullptr;
		delete this;

	}

	void GameObject::deleteInstance() {
		auto it = model->modelInstances.begin();
		model->modelInstances.insert(it + modelInstance, glm::mat4());
		model->modelInstances.erase(model->modelInstances.begin() + modelInstance + 1);

	}

	void GameObject::SetPosition(glm::vec3 position_) {
		position = position_;
		if (model) {
			model->UpdateInstance(modelInstance, position, angle, rotation, scale);
			BoundaryBox.transform = glm::vec3(model->GetTransform(modelInstance)[3][0], model->GetTransform(modelInstance)[3][1], model->GetTransform(modelInstance)[3][2]);
			updateBody();


		}
	}
	void GameObject::SetAngle(float angle_) {
		angle = angle_;
		if (model) {
			model->UpdateInstance(modelInstance, position, angle, rotation, scale);

			BoundaryBox.transform = glm::vec3(model->GetTransform(modelInstance)[3][0], model->GetTransform(modelInstance)[3][1], model->GetTransform(modelInstance)[3][2]);
			updateBody();
		}
	}
	void GameObject::SetRotation(glm::vec3 rotation_) {
		rotation = rotation_;
		if (model) {
			model->UpdateInstance(modelInstance, position, angle, rotation, scale);

			BoundaryBox.transform = glm::vec3(model->GetTransform(modelInstance)[3][0], model->GetTransform(modelInstance)[3][1], model->GetTransform(modelInstance)[3][2]);
			updateBody();
		}
	}
	void GameObject::SetScale(glm::vec3 scale_) {
		scale = scale_;
		if (model) {
			model->UpdateInstance(modelInstance, position, angle, rotation, scale);

			BoundaryBox.transform = glm::vec3(model->GetTransform(modelInstance)[3][0], model->GetTransform(modelInstance)[3][1], model->GetTransform(modelInstance)[3][2]);
			updateBody();
		}
	}

	glm::vec3 GameObject::GetPosition() const {
		return position;
	}
	float GameObject::GetAngle() const {
		return angle;
	}
	glm::vec3 GameObject::GetRotation() const {
		return rotation;
	}
	glm::vec3 GameObject::GetScale() const {
		return scale;
	}

	Model* GameObject::GetModel() const
	{
		return model;
	}

	BoundaryBox GameObject::GetBoundaryBox() {
		return BoundaryBox;
	}

	rp3d::CollisionBody* GameObject::getBody() const {

		return mBody;
	}

	void GameObject::updateBody() {


		rp3d::Transform tempTransform = rp3d::Transform::identity();


		rp3d::Matrix3x3 matrix(model->GetTransform(modelInstance)[0][0], model->GetTransform(modelInstance)[1][0], model->GetTransform(modelInstance)[2][0],
			model->GetTransform(modelInstance)[0][1], model->GetTransform(modelInstance)[1][1], model->GetTransform(modelInstance)[2][1],
			model->GetTransform(modelInstance)[0][2], model->GetTransform(modelInstance)[1][2], model->GetTransform(modelInstance)[2][2]);

		rp3d::Vector3 tempPos = ContinuumEngine::GetInstance()->ConvertglmV3_to_rpV3(glm::vec3(model->GetTransform(modelInstance)[3][0], model->GetTransform(modelInstance)[3][1], model->GetTransform(modelInstance)[3][2]));

		rp3d::Quaternion tempQuat = rp3d::Quaternion(matrix);
		tempTransform.setPosition(tempPos);
		tempTransform.setOrientation(tempQuat);


		mBody->setTransform(tempTransform);

	}


	void GameObject::RenderBoundary() {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	}

}