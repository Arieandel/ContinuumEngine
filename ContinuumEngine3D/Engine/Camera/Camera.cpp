#include "Camera.h"
#include "../ContinuumEngine.h"



namespace ContinuumEngine3D {

	std::unique_ptr<Camera> Camera::cameraInstance = nullptr;

	Camera::Camera() : position(glm::vec3()), perspective(glm::mat4()), orthographic(glm::mat4()), fieldOfView(0.0f), yaw(0.0f), pitch(0.0f), forwardVector(glm::vec3()), upVector(glm::vec3()), rightVector(glm::vec3()), worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f)
	{
		fieldOfView = 45.0f;
		forwardVector = glm::vec3(0.0f, 0.0f, -1.0f);
		upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		worldUp = upVector;
		nearPlane = 2.0f;
		farPlane = 50.0f;
		yaw = -90.0f;

		perspective = glm::perspective(fieldOfView, ContinuumEngine::GetInstance()->GetScreenSize().x / ContinuumEngine::GetInstance()->GetScreenSize().y, nearPlane, farPlane);
		orthographic = glm::ortho(0.0f, ContinuumEngine::GetInstance()->GetScreenSize().x, 0.0f, ContinuumEngine::GetInstance()->GetScreenSize().y, -1.0f, 1.0f);

		UpdateCameraVectors();
	}


	Camera::~Camera()
	{
		for (auto light : lights) {
			delete light;
			light = nullptr;
		}
	}


	Camera* Camera::GetInstance() {
		if (cameraInstance.get() == nullptr) {
			cameraInstance.reset(new Camera);
		}
		return cameraInstance.get();
	}

	void Camera::SetPosition(glm::vec3 position_) {
		position = position_;
		UpdateCameraVectors();
	}
	void Camera::SetRotation(GLfloat yaw_, GLfloat pitch_) {
		yaw = yaw_;
		pitch = pitch_;
		UpdateCameraVectors();
	}
	glm::mat4 Camera::GetView() const {
		return glm::lookAt(position, position + forwardVector, upVector);
	}

	glm::mat4 Camera::GetPerspective() const {
		return perspective;
	}

	glm::mat4 Camera::GetOrthographic() const {
		return orthographic;

	}

	void Camera::UpdateCameraVectors() {
		forwardVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		forwardVector.y = sin(glm::radians(pitch));
		forwardVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		forwardVector = glm::normalize(forwardVector);

		rightVector = glm::normalize(glm::cross(forwardVector, worldUp));
		upVector = glm::normalize(glm::cross(rightVector, forwardVector));
	}

	glm::vec3 Camera::GetPosition() const {
		return position;
	}
	void Camera::AddLightSource(LightSource* light_) {
		lights.push_back(light_);
	}
	std::vector<LightSource*> Camera::GetLightSources() const {
		return lights;
	}

	void Camera::ProcessMouseMovement(float xOffset_, float yOffset_) {
		xOffset_ *= 0.05f;
		yOffset_ *= 0.05f;

		yaw += xOffset_;
		pitch += yOffset_;
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}
		UpdateCameraVectors();
	}
	void Camera::ProcessMouseZoom(int y_) {
		if (y_ < 0 || y_ > 0) {
			position += (float)y_ * (forwardVector * 2.0f);
		}
		UpdateCameraVectors();
	}

}