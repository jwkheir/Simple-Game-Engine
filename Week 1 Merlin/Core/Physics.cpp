#include "stdafx.h"
#include "Physics.h"

namespace Merlin{
	float Physics::step = 1.0 / 50.0;
	Physics::Physics(LinkedList<GameObject> * objects){
		renderedObjects = objects;
		btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		physicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, NULL, collisionConfiguration);
		physicsWorld->setGravity(btVector3(0, -100, 0));
		debugDrawer = new PhysicsDebug();
		debugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
		physicsWorld->setDebugDrawer(debugDrawer);
	}


	Physics::~Physics(){
		delete physicsWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
	}

	void Physics::UpdatePhysics(float deltaTime){
		physicsWorld->stepSimulation(deltaTime);
		CheckForCollisions();
	}

	GameObject* Physics::FindGameObject(btRigidBody* pBody) {
		for (int n = 0; n < renderedObjects->Count(); n++){
			GameObject * obj = renderedObjects->Get(n);
			// GameObject doesn't have a rigidbody
			if (obj == NULL || obj->GetRigidBody() == NULL) continue;
			if (obj->GetRigidBody()->GetPhysicsRigidBody() == pBody){
				return renderedObjects->Get(n);
			}
		}
		return NULL;
	}

	void Physics::CollisionEvent(btRigidBody * pBody0, btRigidBody * pBody1) {
		// find the two colliding objects
		GameObject* pObj0 = FindGameObject(pBody0);
		GameObject* pObj1 = FindGameObject(pBody1);
		// exit if we didn't find anything
		if (!pObj0 || !pObj1) return;
		if (pObj0->GetScript()) {
			pObj0->GetScript()->OnCollisionEnter(pObj1);
		}
		if (pObj1->GetScript()){
			pObj1->GetScript()->OnCollisionEnter(pObj0);
		}
	}

	void Physics::SeparationEvent(btRigidBody * pBody0, btRigidBody * pBody1) {
		// get the two separating objects
		GameObject* pObj0 = FindGameObject((btRigidBody*)pBody0);
		GameObject* pObj1 = FindGameObject((btRigidBody*)pBody1);
		// exit if we didn't find anything
		if (!pObj0 || !pObj1) return;
		if (pObj0->GetScript()) pObj0->GetScript()->OnCollisionExit(pObj1);
		if (pObj1->GetScript()) pObj1->GetScript()->OnCollisionExit(pObj0);
	}

	void Physics::CheckForCollisions() {
		// keep a list of the collision pairs we
		// found during the current update
		CollisionPairs pairsThisUpdate;
		// iterate through all of the manifolds in the dispatcher
		for (int i = 0; i < dispatcher->getNumManifolds(); ++i) {
			// get the manifold
			btPersistentManifold* pManifold = dispatcher->getManifoldByIndexInternal(i);
			// ignore manifolds that have no contact points.
			if (pManifold->getNumContacts() > 0) {
				// get the two rigid bodies involved in the collision
				const btRigidBody* pBody0 = static_cast<const btRigidBody*>(pManifold->getBody0());
				const btRigidBody* pBody1 = static_cast<const btRigidBody*>(pManifold->getBody1());
				GameObject* pObj0 = FindGameObject((btRigidBody*)pBody0);
				GameObject* pObj1 = FindGameObject((btRigidBody*)pBody1);
				// always create the pair in a predictable order (use the pointer value..)
				bool const swapped = pBody0 > pBody1;
				const btRigidBody* pSortedBodyA = swapped ? pBody1 : pBody0;
				const btRigidBody* pSortedBodyB = swapped ? pBody0 : pBody1;
				// create the pair
				CollisionPair thisPair = std::make_pair(pSortedBodyA, pSortedBodyB);
				// insert the pair into the current list
				pairsThisUpdate.insert(thisPair);
				// if this pair doesn't exist in the list from the previous update, it is a new
				// pair and we must send a collision event
				if (pairsLastUpdate.find(thisPair) == pairsLastUpdate.end()) {
					CollisionEvent((btRigidBody*)pBody0, (btRigidBody*)pBody1);
				}
			}
		}
		// create another list for pairs that were removed this update
		CollisionPairs removedPairs;
		// this handy function gets the difference beweentwo sets. It takes the difference between
		// collision pairs from the last update, and this 
		// update and pushes them into the removed pairs list
		std::set_difference(pairsLastUpdate.begin(), pairsLastUpdate.end(), pairsThisUpdate.begin(), pairsThisUpdate.end(), std::inserter(removedPairs, removedPairs.begin()));
		// iterate through all of the removed pairs
		// sending separation events for them
		for (CollisionPairs::const_iterator iter = removedPairs.begin(); iter != removedPairs.end(); ++iter) {
			SeparationEvent((btRigidBody*)iter->first, (btRigidBody*)iter->second);
		}
		// in the next iteration we'll want to compare against the pairs we found in this iteration
		pairsLastUpdate = pairsThisUpdate;
	}






























}
