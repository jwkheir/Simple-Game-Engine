#pragma once
#include "glew.h"
#include "glut.h"
#include "Object.h"
#include <string>
#include <iostream>
#include "LinkedList.h"
#include "Component.h"
#include "Transform.h"
#include "lua.hpp"
#include "luabridge.h"
#include "RigidBody.h"
#include "script.h"

using namespace std;

namespace Merlin{
	// Exercise 2.2
	class GameObject: public Object{
	private:
		string name;
		string tag;
		bool active;
		// Exercise 2.9
		Transform * transform;
		RigidBody * rigidBody;
		// Exercise 9.6
		Script * script;
	public:
		GameObject * next;
		GameObject(string name);
		// Exercise 2.9
		GameObject(string name, string tag, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3  scale = glm::vec3(1, 1, 1));
		~GameObject();
		// Exercise 2.5
		LinkedList<Component> * components;
		void Initialise();
		void Update();
		string GetName(){ return name; }
		string GetTag(){ return tag; }
		void SetTag(string tag){ this->tag = tag; }
		void Destroy(){ active = false; }
		bool IsActive(){ return active; }
		void AddComponent(Component * component);
		Transform * GetTransform(){ return transform; }
		RigidBody * GetRigidBody(){ return rigidBody; }
		// Exercise 9.6
		Script * GetScript(){ return script; }
		// Expose member functions to script
		static void Register(lua_State* L);
	};
}
