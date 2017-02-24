#pragma once
#include "component.h"
#include "Graphics.h"
#include "lua.hpp"
#include "luabridge.h"

using namespace std;


namespace Merlin{
	// Responsible for setting up clipping planes and positioning and rotation of camera.
	// Note: camera always points towards origin.
	class Camera : public Component {
	private:
		glm::vec3 viewDirection;
		float cameraPitch;
		float cameraYaw;
		glm::vec3 up;
		glm::mat4x4 viewMatrix;
		glm::mat4x4 rotationMatrix;
		glm::mat4x4 rollMatrix;

		float nearPlane;
		float farPlane;
		int cameraSpeed;

		
	public:
		Camera(GameObject * gameObject, float nearPlane, float farPlane);
		~Camera(void);
		void Initialise(){}
		void Update();
		// Invoked by LUA scripts
		void Yaw(float value);
		void Pitch(float value);
		void Zoom(float value);
		float GetNearPlane(){
			return nearPlane;
		}
		float GetFarPlane(){
			return farPlane;
		}
		// Used by shaders that draw the verticies
		glm::mat4x4 GetViewMatrix();
		// Make accessible to LUA scripts
		static void Register(lua_State* L);
	};
}

