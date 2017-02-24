#pragma once
#include "Component.h"
#include "Transform.h"
#include "btBulletDynamicsCommon.h"


namespace Merlin{

	// Exercise 9.1
	class RigidBody : public Component {
	private:
		btScalar mass;
		btDiscreteDynamicsWorld * physicsWorld;
		btDefaultMotionState * motionState;
		btRigidBody* rb;
		bool isStatic;
	public:
		RigidBody(GameObject * gameObject, btCollisionShape* shape, btDiscreteDynamicsWorld * pWorld, btScalar mass, btVector3 * scale = NULL, btVector3 * offset = NULL);
		~RigidBody(void);
		void GetPhysicsObjectTransform(btScalar* transform);
		btRigidBody * GetPhysicsRigidBody(){
			return rb;
		}
		bool IsStatic(){
			return isStatic;
		}
		void Update(){}
		void Initialise(){}
	};
}