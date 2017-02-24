#pragma once
#include "Shader.h"
#include "glut.h"
#include "glm.hpp"

using namespace std;


namespace Merlin{

	struct MaterialInfo {
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		GLfloat shininess;
	};

	// Materials are applied to the GameObject meshes during rendering.
	// They consist of a single shader and texture (only supports BMP textures).

	class Material {
	private:
		MaterialInfo properties;
		Shader * shader;
		bool textureEnabled; 
		GLuint textureId;
		unsigned char *LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
	public:
		Material(Shader * shader, const char * textureFileName, MaterialInfo  properties);
		~Material();
		// Predifined materials
		static MaterialInfo woodMaterial;
		static MaterialInfo whiteShineyMaterial;
		static MaterialInfo whiteMattMaterial;
		static MaterialInfo brassMaterial;
		static MaterialInfo redPlasticMaterial;
		void Apply();
		Shader * GetShader(){ return shader; }
		MaterialInfo GetProperties(){
			return properties;
		}
	};
}
