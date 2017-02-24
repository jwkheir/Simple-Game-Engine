#include "stdafx.h"
#include "Camera.h"
#include "GameObject.h"



namespace Merlin{

	Camera::Camera(GameObject * gameObject, float nearPlane, float farPlane) :Component(gameObject){
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;
		GLint viewport[4];
		// Get viewport dimensions
		glGetIntegerv(GL_VIEWPORT, viewport);
		int screenWidth = viewport[2];
		int screenHeight = viewport[3];
		float aspectRatio = screenWidth / (float)screenHeight;
		// Need to review this in future versions
		viewDirection = glm::vec3(0.0, 0.0, 0.0);
		// Up is also fixed
		up = glm::vec3(0, 1, 0);
	}

	Camera::~Camera(void){
	
	}

	void Camera::Update() {
		// Get camera's poition through the transform component
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		// Convert the position to a vector with 4 components for matrix multiplication
		glm::vec4 cameraPosition(position, 0.0);
		// Apply rotations to determine actual camera position
		cameraPosition = rotationMatrix * rollMatrix * cameraPosition;
	}

	void Camera::Yaw(float value) {
		cameraYaw -= value;
		if (cameraYaw < 0) cameraYaw += 360;
		if (cameraYaw >= 360) cameraYaw -= 360;
		float yaw = glm::radians(cameraYaw);
		rotationMatrix = glm::rotate(glm::mat4x4(), yaw, up);
	}

	void Camera::Pitch(float value) {
		cameraPitch -= value;
		if (cameraPitch < 0) cameraPitch += 360;
		if (cameraPitch >= 360) cameraPitch -= 360;
		float pitch = glm::radians(cameraPitch);
		// Get camera's position through the transform component
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		glm::vec3 forward = position;
		glm::vec3 right = glm::normalize(glm::cross(up, forward));
		rollMatrix = glm::rotate(glm::mat4x4(), -pitch, right);
	}

	void Camera::Zoom(float value) {
		// Get camera's poition through the transform component
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		position.z += value;
		// Update transform
		gameObject->GetTransform()->SetPosition(position);
	}

	glm::mat4x4 Camera::GetViewMatrix(){
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		// Convert the position to a vector with 4 components for matrix multiplication
		glm::vec4 cameraPosition(position, 0.0);
		// Apply rotations to determine actual camera position
		cameraPosition = rotationMatrix * rollMatrix * cameraPosition;
		return glm::lookAt(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z), viewDirection, up);
	}

	void Camera::Register(lua_State* L){
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("Merlin")
			.beginClass<Camera>("Camera")
			.addFunction("Yaw", &Camera::Yaw)
			.addFunction("Pitch", &Camera::Pitch)
			.addFunction("Zoom", &Camera::Zoom)
			.endClass()
			.endNamespace();
	}

}