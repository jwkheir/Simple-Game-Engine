#include "stdafx.h"
#include "RigidBody.h"
#include "GameObject.h"

namespace Merlin{
	RigidBody::RigidBody(GameObject * gameObject, btCollisionShape* shape, btDiscreteDynamicsWorld * pWorld, btScalar mass, btVector3 * scale, btVector3 * offset) :Component(gameObject) {
		this->physicsWorld = pWorld;
		this->mass = mass;
		btTransform startTransform;
		startTransform.setIdentity();
		// Get the rendered object's transform
		Transform * transform = gameObject->GetTransform();
		if (offset == NULL){
			// Position the physics object based on the rendered object's location
			startTransform.setOrigin(btVector3(transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z));
		}
		else {
			//startTransform.setOrigin(*offset);
			startTransform.setOrigin(btVector3(transform->GetPosition().x + offset->x(), transform->GetPosition().y + offset->y(), transform->GetPosition().z + offset->z()));
		}
		// If no scale passed as a parameter, base scaling on GameObject's transform
		if (scale == NULL){
			// Scale the physics object collsion's shape based on the rendered object's scale
			shape->setLocalScaling(btVector3(transform->GetScale().x, transform->GetScale().y, transform->GetScale().z));
		}
		else {
			shape->setLocalScaling(*scale);
			//shape->setLocalScaling(btVector3(10, 10, 10));
		}
		//rigidbody is dynamic if mass is non zero, otherwise static
		isStatic = (mass == 0.f);
		btVector3 localInertia(0, 0, 0);
		if (!isStatic)
			shape->calculateLocalInertia(mass, localInertia);
		// The motion state can be used to access the physics object's transform to synchronise positioning with the rendered object
		motionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
		rb = new btRigidBody(rbInfo);
		rb->setRestitution(0.95f);
		rb->setFriction(1.2f);
		physicsWorld->addRigidBody(rb);
	}


	RigidBody::~RigidBody(void){
		physicsWorld->removeCollisionObject(rb);
		delete motionState;
		delete rb;
	}

	void RigidBody::GetPhysicsObjectTransform(btScalar* transform) {
		btTransform trans;
		motionState->getWorldTransform(trans);
		trans.getOpenGLMatrix(transform);
	}


}