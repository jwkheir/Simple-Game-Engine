#include "stdafx.h"
#include "InputManager.h"

namespace Merlin{
	map < string, int > InputManager::keyMappings;
	GLFWwindow* InputManager::window = 0;
	Position InputManager::currentCursor = { 0.0, 0.0 };
	Position InputManager::previousCursor = { 0.0, 0.0 };

}
