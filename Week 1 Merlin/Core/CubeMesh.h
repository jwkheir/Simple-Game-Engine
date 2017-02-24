#pragma once
#include "Mesh.h"

namespace Merlin{

	class CubeMesh : public Mesh {
	private:
		static GLfloat cubeTriangles[];
		static GLfloat cubeTexture[];
		static GLfloat cubeNormals[];
	public:
		CubeMesh();
		~CubeMesh();
		void Initialise();
		void Render();
	};

}
