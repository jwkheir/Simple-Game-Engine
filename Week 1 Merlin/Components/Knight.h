#pragma once
#include "component.h"
#include "Graphics.h"
#include "lua.hpp"
#include "luabridge.h"


/*
* Author: Jack Kheir
* Updated: 18.05.16
*
* Essentially the player class, handles movement, rotation etc 
*/
using namespace std;

namespace Merlin
{
	class Knight : public Component
	{
	private:
		float speed;
	public:
		Knight(GameObject * gameObject, float speed);
		void Initialise(){};
		void Update();
		void Move(float value);
		void Strafe(float value);
		void Rotate(float value);
		void Reset();
		static void Register(lua_State* L);
		~Knight(void);
	};

}
