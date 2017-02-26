#pragma once
#include "btBulletDynamicsCommon.h"
#include "GameObject.h"
#include <set>
#include <algorithm> 
#include "PhysicsDebug.h"

namespace Merlin{

	typedef std::pair<const btRigidBody*, const btRigidBody*> CollisionPair;
	typedef std::set<CollisionPair> CollisionPairs;

	class Physics{
	private:
		LinkedList<GameObject> * renderedObjects;
		btDiscreteDynamicsWorld * physicsWorld;
		btBroadphaseInterface * overlappingPairCache;
		btCollisionDispatcher * dispatcher;
		btSequentialImpulseConstraintSolver * solver;
		CollisionPairs pairsLastUpdate;
		GameObject* FindGameObject(btRigidBody* pBody);
		void CollisionEvent(btRigidBody * pBody0, btRigidBody * pBody1);
		void SeparationEvent(btRigidBody * pBody0, btRigidBody * pBody1);
		void CheckForCollisions();
	public:
		static float step;
		PhysicsDebug * debugDrawer;
		Physics(LinkedList<GameObject> * objects);
		~Physics();
		void UpdatePhysics(float deltaTime);
		btDiscreteDynamicsWorld * GetPhysicsWorld(){
			return physicsWorld;
		}
		void Physics::UpdatePhysicsDebug(){
			physicsWorld->debugDrawWorld();
		}
	};
}
