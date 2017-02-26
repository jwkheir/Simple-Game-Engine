#include "stdafx.h"
#include <iostream>
#include "Script.h"



namespace Merlin{

	Script::Script(GameObject * gameObject, const char * scriptName, lua_State * L) :Component(gameObject){
		OnStartScript = NULL;
		OnUpdateScript = NULL;
		OnCollisionEnterScript = NULL;
		OnCollisionExitScript = NULL;
		this->L = L;
		if (luaL_dofile(L, scriptName)){
			printf("%s\n", lua_tostring(L, -1));
		}
		else{
			componentScript = new LuaRef(getGlobal(L, "ScriptComponent"));
			if ((*componentScript).isTable()){
				OnStartScript = new LuaRef((*componentScript)["Start"]);
				OnUpdateScript = new LuaRef((*componentScript)["Update"]);
				OnCollisionEnterScript = new LuaRef((*componentScript)["OnCollisionEnter"]);
				OnCollisionExitScript = new LuaRef((*componentScript)["OnCollisionExit"]);
			}
		}
	}

	Script::~Script(void) {

	}

	void Script::OnCollisionEnter(GameObject * collider){
		if (OnCollisionEnterScript != NULL && (*OnCollisionEnterScript).isFunction()){
			(*OnCollisionEnterScript)((*componentScript), this->gameObject, collider);
		}
	}

	void Script::OnCollisionExit(GameObject * collider){
		if (OnCollisionExitScript != NULL && (*OnCollisionExitScript).isFunction()){
			(*OnCollisionExitScript)((*componentScript), this->gameObject, collider);
		}
	}

	void Script::Initialise(){
		if (OnStartScript != NULL && (*OnStartScript).isFunction()){
			(*OnStartScript)((*componentScript), this->gameObject);
		}
	}

	void Script::Update(){
		if (OnUpdateScript != NULL && (*OnUpdateScript).isFunction()){
			(*OnUpdateScript)((*componentScript), this->gameObject);
		}
	}
}