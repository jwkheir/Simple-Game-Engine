#pragma once
#include "glfw3.h"
#include "lua.hpp"
#include "luabridge.h"
#include <string>
#include <map>
#include "glm.hpp"
using namespace std;

namespace Merlin{

	// Track cursor's screen coordinates
	struct Position{
		double x, y;
	};

	class InputManager{
	private:
		static GLFWwindow* window;
		static map < string, int > keyMappings;
		// There is no GLFW constant to represent mouse movement along x axis so define here
		static const int MERLIN_MOUSE_MOVE_X = 10001;

		static Position currentCursor;
		static Position previousCursor;

	public:
		static void Initialise(GLFWwindow* win){
				window = win;
				keyMappings["CameraZoomIn"] = GLFW_KEY_Z;
				keyMappings["CameraZoomOut"] = GLFW_KEY_X;
				keyMappings["CameraYawLeft"] = GLFW_KEY_LEFT;
				keyMappings["CameraYawRight"] = GLFW_KEY_RIGHT;
				keyMappings["CameraPitchUp"] = GLFW_KEY_UP;
				keyMappings["CameraPitchDown"] = GLFW_KEY_DOWN;
				keyMappings["Xaxis"] = MERLIN_MOUSE_MOVE_X;

				//Extra buttons added
				//-->movement
				keyMappings["W"] = GLFW_KEY_W;
				keyMappings["A"] = GLFW_KEY_A;
				keyMappings["S"] = GLFW_KEY_S;
				keyMappings["D"] = GLFW_KEY_D;
				//-->Rotation
				keyMappings["Q"] = GLFW_KEY_Q;
				keyMappings["E"] = GLFW_KEY_E;
			}

		static bool GetKey(string key){
			if (glfwGetKey(window, keyMappings[key]) == GLFW_PRESS){
				return true;
			}
			return false;
		}

		// Ivoked from within the game loop.
		static void RecordLastCursorPosition(){
			glfwGetCursorPos(window, &previousCursor.x, &previousCursor.y);
		}

		static float GetAxis(string key){
			if (keyMappings[key] == MERLIN_MOUSE_MOVE_X){
				glfwGetCursorPos(window, &currentCursor.x, &currentCursor.y);
				return glm::clamp(float(currentCursor.x - previousCursor.x), -1.0f, 1.0f);
			}
			else return 0.0f;
		}


		static void Register(lua_State* L){
			using namespace luabridge;
			getGlobalNamespace(L)
				.beginNamespace("Merlin")
				.beginClass<InputManager>("InputManager")
				.addStaticFunction("GetKey", &InputManager::GetKey)
				// Exercisr 8.7
				.addStaticFunction("GetAxis", &InputManager::GetAxis)
				.endClass()
				.endNamespace();
		}
	};

}