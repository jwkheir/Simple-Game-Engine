#include "stdafx.h"
#include "Knight.h"
#include "GameObject.h"
#include "LightSystem.h"


/*
* Author: Jack Kheir
* Updated: 18.05.16
*
* Essentially the player class, handles movement, rotation etc
*/
namespace Merlin
{
	Knight::Knight(GameObject * gameObject, float speed) :Component(gameObject)
	{
		this->speed = speed;
	}

	Knight::~Knight(void){}

	void Knight::Update(){}
	

	/*
	*Called when W or S key is pressed
	*/
	void Knight::Move(float value)
	{
		glm::vec3 position = gameObject->GetTransform()->GetPosition();
		glm::vec3 forward = gameObject->GetTransform()->FORWARD * gameObject->GetTransform()->GetRotation();
		if (!forward.y > 0 && !forward.y < 180)
		{
			forward.x = -forward.x * speed;
		}

		if (value > 0)
		{
			LightSystem::SetAllLights(glm::vec3(255, 255, 0));
		}
		else if (value < 0)
		{
			LightSystem::SetAllLights(glm::vec3(128, 255, 0));
		}
		position += forward * value * speed;
		gameObject->GetTransform()->SetPosition(position);
	}

	/*
	*Called when A or D key is pressed
	*/
	void Knight::Strafe(float value)
	{
		glm::vec3 position = gameObject->GetTransform()->GetPosition();

		if (value > 0)
		{
			LightSystem::SetAllLights(glm::vec3(255, 255, 0));
		}
		else
		{
			LightSystem::SetAllLights(glm::vec3(51, 51, 255));
		}
		position.x += value * speed;
		gameObject->GetTransform()->SetPosition(position);	
	}

	/*
	*Called when Q or E key is pressed
	*/
	void Knight::Rotate(float value)
	{
		float rotate = glm::radians(value * speed);
		glm::quat temp = glm::angleAxis(rotate, glm::vec3(0.0, 1.0, 0.0));
		glm::quat rotation = temp * gameObject->GetTransform()->GetRotation();

		if (value > 0)
		{
			LightSystem::SetAllLights(glm::vec3(51, 0, 102));
		}
		else
		{
			LightSystem::SetAllLights(glm::vec3(255, 153, 51));
		}
		gameObject->GetTransform()->SetRotation(rotation);
	}

	void Knight::Reset()
	{
		LightSystem::ResetLights(glm::vec3(0, 0, 0));
	}

	void Knight::Register(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("Merlin")
			.beginClass<Knight>("Knight")
			.addFunction("Move", &Knight::Move)
			.addFunction("Strafe", &Knight::Strafe)
			.addFunction("Rotate", &Knight::Rotate)
			.addFunction("Reset", &Knight::Reset)
			.endClass()
			.endNamespace();
	}
}
