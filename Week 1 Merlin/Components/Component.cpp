#include "stdafx.h"
#include "Component.h"

namespace Merlin{


	Component::Component(GameObject * gameObject){
		this->gameObject = gameObject;
		next = 0;
	}

	Component::~Component(){
	}
}