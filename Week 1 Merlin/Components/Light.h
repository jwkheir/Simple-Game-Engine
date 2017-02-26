#pragma once
#include "Component.h"
#include "glew.h"



namespace Merlin{

	struct LightInfo{
		glm::vec3 position;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};

	// Exercise 3.2
	class Light : public Component {
	private:
		GLenum index;
		static int lightIndex;
		LightInfo properties;
	public:
		Light(GameObject * gameObject, LightInfo info);
		~Light(void);
		void Initialise();
		void Update();
		static LightInfo noonLight;
		static LightInfo duskLight;
		LightInfo GetProperties();
	};



}