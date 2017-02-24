#include "stdafx.h"
#include "CharacterController.h"
#include "GameObject.h"

/*
* Author: Jack Kheir
* Updated: 18.05.16
*
* Adds to Player objects or in this case Knight Game Objects,
* A simple change in this class can be made so that it can be added
* to any gameobject.
*/
namespace Merlin
{
	Knight * CharacterController::knight = 0;
	CharacterController::CharacterController(GameObject * gameObject, Knight * knight, btDiscreteDynamicsWorld * pWorld) :Component(gameObject)
	{
		this->go = go;
		this->knight = knight;
		this->pw = pWorld;

		//BTKINEMATIC CONTROLLER SETUP
		shape = new btCapsuleShape(50, 50);
		ghost = new btPairCachingGhostObject();
		
		SetTransform();
		ghost->setCollisionShape(shape);

		controller = new btKinematicCharacterController(ghost, shape, 1);
		pw->addCharacter(controller);
		pw->addCollisionObject(ghost);
		
		pw->getPairCache()->setInternalGhostPairCallback(
			new btGhostPairCallback());
	}

	//SETS THE TRANSFORM AND DETECTS COLLISION CALLS
	void CharacterController::Update()
	{
		SetTransform();
		DetectCollision();
	}


	/*
	*code found at 
	*/
	void CharacterController::DetectCollision()
	{
		btManifoldArray manifoldArray;
		btBroadphasePairArray& pairArray =
			ghost->getOverlappingPairCache()->getOverlappingPairArray();
		int numPairs = pairArray.size();

		for (int i = 0; i < numPairs; ++i)
		{
			manifoldArray.clear();

			const btBroadphasePair& pair = pairArray[i];

			btBroadphasePair* collisionPair =
				pw->getPairCache()->findPair(
				pair.m_pProxy0, pair.m_pProxy1);

			if (!collisionPair) continue;

			if (collisionPair->m_algorithm)
				collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);

			for (int j = 0; j<manifoldArray.size(); j++)
			{
				btPersistentManifold* manifold = manifoldArray[j];

				bool isFirstBody = manifold->getBody0() == ghost;

				btScalar direction = isFirstBody ? btScalar(-1.0) : btScalar(1.0);

				for (int p = 0; p < manifold->getNumContacts(); ++p)
				{
					const btManifoldPoint&pt = manifold->getContactPoint(p);

					if (pt.getDistance() < 0.f)
					{
						const btVector3& ptA = pt.getPositionWorldOnA();
						const btVector3& ptB = pt.getPositionWorldOnB();
						const btVector3& normalOnB = pt.m_normalWorldOnB;

						// handle collisions here
					}
				}
			}
		}
	}

	//SETS THE GHOST OBJECT'S POSITION AND ROTATION TO THE GAMEOBJECT'S
	void CharacterController::SetTransform()
	{
		glm::quat quat = gameObject->GetTransform()->GetRotation();
		glm::vec3 pos = gameObject->GetTransform()->GetPosition();
		ghost->setWorldTransform(btTransform(btQuaternion(quat.x, quat.y, quat.z, 1), btVector3(pos.x, -50, pos.z)));
	}

	void CharacterController::Register(lua_State* L){
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("Merlin")
			.beginClass<CharacterController>("CharacterController")
			.addStaticFunction("GetKnight", &CharacterController::GetKnight)
			.endClass()
			.endNamespace();
	}
}
