#include "stdafx.h"
#include "GameObject.h"

namespace Merlin{
	GameObject::GameObject(string name) :name(name){
		cout << "Loading Game Object " << name << " into level." << endl;
		this->active = true;
		this->tag = "";
		// Exercise 2.5
		components = new LinkedList<Component>();
		rigidBody = 0;
		// Exercise 9.6
		script = 0;
	}

	// Exercise 2.9
	GameObject::GameObject(string name, string tag, glm::vec3 position, glm::vec3 rotation, glm::vec3  scale){
		cout << "Loading Game Object " << name << " into level." << endl;
		this->active = true;
		this->name = name;
		this->tag = tag;
		components = new LinkedList<Component>();
		// All GameObjects have a transform so assign it by default
		transform = new Transform(this, position, rotation, scale);
		transform->gameObject = this;
		components->Insert((Component*)transform);
	}

	GameObject::~GameObject(){
		//Exercise 2.7
		delete components;
	}


	// Exercise 2.6
	void GameObject::Initialise(){
		for (int n = 0; n < components->Count(); n++){
			components->Get(n)->Initialise();
		}
	}

	// Exercise 2.6
	void GameObject::Update(){
		for (int n = 0; n < components->Count(); n++){
			components->Get(n)->Update();
		}
	}

	void GameObject::AddComponent(Component * component){
		component->gameObject = this;
		if (typeid(RigidBody) == typeid(*component)) rigidBody = (RigidBody *)component;
		// Exercise 9.6
		if (typeid(Script) == typeid(*component)) script = (Script *)component;
		components->Insert(component);
	}

	void GameObject::Register(lua_State* L){
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("Merlin")
			.beginClass<Object>("Object")
			.addFunction("GetID", &Object::GetID)
			.endClass()
			.deriveClass<GameObject, Object>("GameObject")
			.addFunction("GetName", &GameObject::GetName)
			.addFunction("GetTag", &GameObject::GetTag)
			.addFunction("Destroy", &GameObject::Destroy)
			.addFunction("GetTransform", &GameObject::GetTransform)
			.endClass()
			.endNamespace();
	}
}