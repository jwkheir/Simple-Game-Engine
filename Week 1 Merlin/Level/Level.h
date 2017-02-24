#pragma once
#include "LinkedList.h"
#include "GameObject.h"
#include "Graphics.h"
#include "lua.hpp"
#include "physics.h"


namespace Merlin{
	// Exercise 3.3
	class Level{
	private:
		string name;
		LinkedList<GameObject> * gameObjects;
	public:
		Physics * physics;
		Level(){};
		Level(string name, lua_State * L);
		~Level(void);
		void Initialise();
		void Update();
		string GetName(){
			return name;
		}
	};
}