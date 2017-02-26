#pragma once
#include "Mesh.h"
#include "SceneContext.h"
#include "renderer.h"
#include "Shader.h"

namespace Merlin{
	class FBXMesh : public Mesh {
	private:
		void  GetFbxInfo(FbxNode*);
		const char * fileName;
	public:
		FBXMesh(const char * fileName);
		~FBXMesh();
		void Initialise();
		void Render();
	};
}
