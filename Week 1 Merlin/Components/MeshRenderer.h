#pragma once
#include "renderer.h"
#include "../Core/Mesh.h"
#include <matrix_transform.hpp>
#include <transform.hpp>
#include "RigidBody.h"


namespace Merlin{
	// Exercise 5.1
	class MeshRenderer : public Renderer{
	private:
		GLuint matMVPIdx;
		GLuint matNIdx;
		GLuint matMVIdx;

		GLuint lAmbientIdx;
		GLuint lDiffuseIdx;
		GLuint lSpecularIdx;
		GLuint lPositionIdx;

		GLuint mAmbientIdx;
		GLuint mDiffuseIdx;
		GLuint mSpecularIdx;
		GLuint mShininessIdx;

		GLuint cameraPositionIdx;
		Mesh * mesh;
	public:
		MeshRenderer(GameObject * gameObject, Mesh * mesh, Material * shader);
		~MeshRenderer();
		void Update();
		void Initialise();
	};
}