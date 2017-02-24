#include "stdafx.h"
#include "Object.h"

namespace Merlin{
	int Object::instances = 0;

	Object::Object(){
		instances++;
		this->id = instances;
	}


	Object::~Object(){
	}
}