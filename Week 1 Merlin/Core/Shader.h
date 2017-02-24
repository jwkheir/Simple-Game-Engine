#pragma once
#include "glew.h"


namespace Merlin{

	class Shader{
	private:
		GLuint program, v, f;
		void PrintShaderInfoLog(GLuint obj, const char * fragmentShaderFileName);
		void PrintProgramInfoLog(GLuint obj);
		char *ReadTextFile(const char *fileName);
	public:
		// Required for XML Level loader
		Shader(){}
		Shader(const char * vertexShaderFileName, const char * fragmentShaderFileName);
		~Shader(void);
		GLuint GetProgram(){return program;}
	};

}