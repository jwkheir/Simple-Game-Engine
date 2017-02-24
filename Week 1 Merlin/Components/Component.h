#pragma once
#include "Object.h"
#include "glm.hpp"
#include "matrix_transform.hpp"


namespace Merlin{
	class GameObject;

	// Exercise 2.4
	class Component:public Object {
	public:
		Component *next;
		GameObject * gameObject;
		Component(){}
		Component(GameObject * gameObject);
		~Component();
		virtual void Initialise() = 0;
		virtual void Update() = 0;
	};

}