#include "stdafx.h"
#include "Graphics.h"
#include "Camera.h"

namespace Merlin {
	// Exercise 1.3
	int Graphics::DEFAULT_WINDOW_WIDTH = 1200;
	int Graphics::DEFAULT_WINDOW_HEIGHT = 800;

	glm::mat4 Graphics::projectionMatrix;
	Camera * Graphics::mainCamera = 0;
	Light * Graphics::mainLight = 0;


	void Graphics::SetMainCamera(Camera * camera){
		mainCamera = camera;
		float aspectRatio = Graphics::DEFAULT_WINDOW_WIDTH / (float)Graphics::DEFAULT_WINDOW_HEIGHT;
		projectionMatrix = glm::frustum(-aspectRatio * camera->GetNearPlane(), aspectRatio * camera->GetNearPlane(), -camera->GetNearPlane(), camera->GetNearPlane(), camera->GetNearPlane(), camera->GetFarPlane());
		// OpenGL requires knowledge of the viewing volumume for clipping
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// left, right, bottom, top, near, far
		glFrustum(-aspectRatio * camera->GetNearPlane(), aspectRatio * camera->GetNearPlane(), -camera->GetNearPlane(), camera->GetNearPlane(), camera->GetNearPlane(), camera->GetFarPlane());
	}

	void Graphics::Register(lua_State* L){
		using namespace luabridge;
		getGlobalNamespace(L)
			.beginNamespace("Merlin")
			.beginClass<Graphics>("Graphics")
			.addStaticFunction("GetCamera", &Graphics::GetMainCamera)
			.endClass()
			.endNamespace();
	}

}
