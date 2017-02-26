#pragma once
#include "Component.h"
#include "glm.hpp"
#include "quaternion.hpp"
#include "lua.hpp"
#include "luabridge.h"


namespace Merlin{
	class GameObject;

	class Transform :public  Component{
	private:
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3  scale;
	public:
		static glm::vec3 const FORWARD;
		static glm::vec3 const UP;
		static glm::vec3 const RIGHT;
		Transform();
		Transform(GameObject * gameObject, glm::vec3  position, glm::vec3 rotation, glm::vec3   scale);
		~Transform();
		glm::vec3   GetPosition(){ return position; }
		glm::quat   GetRotation(){ return rotation; }
		glm::vec3   GetScale(){ return scale; }
		void SetPosition(glm::vec3   position) {
			this->position = position;
		}
		void SetRotation(glm::quat  rotation) {
			this->rotation = rotation;
		}
		void SetScale(glm::vec3   scale) {
			this->scale = scale;
		}
		void Update(){}
		void Initialise(){}

		glm::mat4x4  GetTransformation();

		void RotateAboutY(float angle);
		// Exercise 8.8
		static void Register(lua_State* L);
	};
}
