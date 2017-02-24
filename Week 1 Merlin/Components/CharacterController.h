#pragma once
#include "lua.hpp"
#include "luabridge.h"
#include "Knight.h"
#include "component.h"
#include "btBulletDynamicsCommon.h"
#include <btGhostObject.h>
#include <btKinematicCharacterController.h>

/*
* Author: Jack Kheir
* Updated: 18.05.16
*
* Adds to Player objects or in this case Knight Game Objects,
* A simple change in this class can be made so that it can be added
* to any gameobject.
*/

using namespace std;
namespace Merlin
{
	class Knight;
	class CharacterController : public Component
	{
	private :
		GameObject * go;
		static Knight * knight;
		btCapsuleShape * shape;
		btPairCachingGhostObject * ghost;
		btKinematicCharacterController * controller;
		btDiscreteDynamicsWorld * pw;
	private :
		void SetTransform();
		void DetectCollision();
	public:
		CharacterController(GameObject * gameObject, Knight * knight, btDiscreteDynamicsWorld * pWorld);
		static void SetKnight(Knight * go);
		static Knight * GetKnight()
		{
			return knight;
		}
		void Update();
		void Initialise(){}
		static void Register(lua_State* L);
	};

}
