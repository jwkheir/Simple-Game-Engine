#include "stdafx.h"
#include <stdlib.h>
#include "glew.h"
#include "glfw3.h"
#include "Graphics.h"
#include "Physics.h"
#include "level.h"
#include "InputManager.h"
#include "lua.hpp"
#include "Camera.h"
#include "CharacterController.h"
#include "Knight.h"
#include "LightSystem.h"
using namespace Merlin;

#define  MERLIN_VERSION "1.0"

Merlin::Level *level;
lua_State * L;



// Exercise 1.2
void About(){
	printf("Merlin Engine Version %s \n", MERLIN_VERSION);
}

void InitialiseLUA(){
	L = luaL_newstate();
	if (L == NULL) {
		printf("FAILED... Unable to allocate memory for LUA Scripting. \n");
	}
	else {
		printf("PASS... LUA Scripting state created. \n");
	}
	luaL_openlibs(L);
	Graphics::Register(L);
	GameObject::Register(L);
	InputManager::Register(L);
	Camera::Register(L);
	// Exercise 8.8
	Transform::Register(L);
	CharacterController::Register(L);
	Knight::Register(L);
}

void InitialiseGLFW(){
	if (glfwInit() == GL_TRUE){
		// Exercise 1.5
		int major, minor, rev;
		glfwGetVersion(&major, &minor, &rev);
		printf("GLFW3 Version %i:%i:%i \n", major, minor, rev);
		printf("PASS... GLFW Initialised. \n");
	}
	else {
		printf("FAILED.. GLFW Initialisation failed. \n");
		exit(EXIT_FAILURE);
	}
}

void InitialiseGLEW(){
	if (glewInit() != GLEW_OK) {
		printf("FAILED... Unable to initialise GLEW. \n");
	}
	else {
		printf("PASS... GLEW Initialised. \n");
	}
}

void InitialsieFXLighting(){
	LightSystem::Initialise();
	//LightSystem::SetLight(0, 1, glm::vec3(255, 0, 0), 255);
}

void ShutDown()
{
	LightSystem::ShutDown();
	lua_close(L);
}

void DoRender(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	level->Update();
}

void DoPhysics(double deltaTime){
	level->physics->UpdatePhysics(deltaTime);
}


// Decouples physics and rendering timesteps
void GameLoop(GLFWwindow* window){
	// Physics step
	double dt = Physics::step;
	double previous = glfwGetTime();
	double lag = 0.0;
	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		double current = glfwGetTime();
		// Time elapsed since last frame
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;
		// Depending upon frame time 0 or more physics steps per frame.
		while (lag >= dt){
			DoPhysics(dt);
			lag -= dt;
		}
		DoRender();
		level->physics->UpdatePhysicsDebug();
		level->physics->debugDrawer->Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
		// Save the current cursor position in order to calculate cursor movement per frame.
		InputManager::RecordLastCursorPosition();
	}
}


void Initialise(GLFWwindow* window){
	InitialiseGLEW();
	// Exercise 8.3
	InputManager::Initialise(window);
	// Exercise 3
	InitialiseLUA();
	InitialsieFXLighting();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// Enable antialiasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Create the level
	level = new Merlin::Level("Demo Scene", L);
	// Load the assets
	level->Initialise();
	level->physics->debugDrawer->Initialise();
}


void OnError(int error, const char* description){
	fputs(description, stderr);
}

int main(){
	glfwSetErrorCallback(OnError);
	// Exercise 1.2
	About();
	// Exercise 1.1
	InitialiseGLFW();
	GLFWwindow* window = glfwCreateWindow(Graphics::DEFAULT_WINDOW_WIDTH, Graphics::DEFAULT_WINDOW_HEIGHT, "Merlin Engine", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// Exercise 1.6
	// Get the resolution of the primary monitor
	const GLFWvidmode * vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	// Center our window
	glfwSetWindowPos(
		window,
		(vidmode->width - Graphics::DEFAULT_WINDOW_WIDTH) / 2,
		(vidmode->height - Graphics::DEFAULT_WINDOW_HEIGHT) / 2
		);
	// Make the OpenGL context current
	glfwMakeContextCurrent(window);
	// Enable v-sync
	glfwSwapInterval(1);
	// Exercise 8.3
	Initialise(window);
	// Exercise 1.4
	GameLoop(window);
	ShutDown();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

