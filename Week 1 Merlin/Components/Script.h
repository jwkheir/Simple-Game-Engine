#pragma once
#include "Component.h"
#include "lua.hpp"
#include "luabridge.h"

using namespace std;
using namespace luabridge;

namespace Merlin{
	class Script :public Component{
	private:
		lua_State * L;
		LuaRef * componentScript;
		LuaRef * OnStartScript;
		LuaRef * OnUpdateScript;
		LuaRef * OnCollisionEnterScript;
		LuaRef * OnCollisionExitScript;
	public:
		Script(GameObject * gameObject, const char * scriptName, lua_State * L);
		~Script(void);
		void Initialise();
		void Update();
		void OnCollisionEnter(GameObject * collider);
		void OnCollisionExit(GameObject * collider);
		void Invoke(char *function);
	};
}