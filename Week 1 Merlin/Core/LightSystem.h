#pragma once
#include <iostream>
#include "LFX2.h"
#include <Windows.h>
#include "glm.hpp"

using namespace std;

namespace Merlin
{
	class LightSystem
	{
	private:
		static HINSTANCE hLibrary;
		static LFX2INITIALIZE InitFunction;
		static LFX_RESULT result;
		static LFX2GETNUMDEVICES GetNumDevicesFunction;
		static LFX2GETDEVDESC GetDeviceDescriptionFunction;
		static LFX2GETNUMLIGHTS GetNumLightsFunction;
		static LFX2GETLIGHTDESC GetLightDescriptionFunction;
		static LFX2SETLIGHTCOL SetLightColorFunction;
		static LFX2UPDATE UpdateFunction;
		static LFX2RELEASE ReleaseFunction;
	public:
		LightSystem();
		static void Initialise();
		static void DisplaySystemDetails();
		static void DisplayDeviceDetails(unsigned int deviceId);
		static void DisplayLightDetails(unsigned int deviceId, unsigned int lightId);
		static bool SetLight(unsigned int deviceId, unsigned int lightId, glm::vec3 col, int brightness);
		static void ShutDown();
		//Custom Functions 
		static void SetAllLights(glm::vec3 rgb);
		static void ResetLights(glm::vec3 rgb);
		~LightSystem();
	};
}
