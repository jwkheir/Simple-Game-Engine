#include "stdafx.h"
#include "LightSystem.h"


namespace Merlin
{
	HINSTANCE LightSystem::hLibrary;
	LFX_RESULT LightSystem::result;
	LFX2INITIALIZE LightSystem::InitFunction;

	LFX2GETNUMDEVICES LightSystem::GetNumDevicesFunction;
	LFX2GETDEVDESC LightSystem::GetDeviceDescriptionFunction;
	LFX2GETNUMLIGHTS LightSystem::GetNumLightsFunction;
	LFX2GETLIGHTDESC LightSystem::GetLightDescriptionFunction;

	LFX2SETLIGHTCOL LightSystem::SetLightColorFunction;
	LFX2UPDATE LightSystem::UpdateFunction;
	LFX2RELEASE LightSystem::ReleaseFunction;

	LightSystem::LightSystem()
	{
	}

	void LightSystem::Initialise(){
		// Explicity dynamic link the library allows the engine to run even  though the DLL may not be present 
		hLibrary = LoadLibrary(_T(LFX_DLL_NAME));
		if (hLibrary){
			// Get the address from the exported functions in the DLL
			InitFunction = (LFX2INITIALIZE)GetProcAddress(hLibrary, LFX_DLL_INITIALIZE);
			GetNumDevicesFunction = (LFX2GETNUMDEVICES)GetProcAddress(hLibrary, LFX_DLL_GETNUMDEVICES);
			GetDeviceDescriptionFunction = (LFX2GETDEVDESC)GetProcAddress(hLibrary, LFX_DLL_GETDEVDESC);
			GetNumLightsFunction = (LFX2GETNUMLIGHTS)GetProcAddress(hLibrary, LFX_DLL_GETNUMLIGHTS);
			GetLightDescriptionFunction = (LFX2GETLIGHTDESC)GetProcAddress(hLibrary, LFX_DLL_GETLIGHTDESC);
			SetLightColorFunction = (LFX2SETLIGHTCOL)GetProcAddress(hLibrary, LFX_DLL_SETLIGHTCOL);
			UpdateFunction = (LFX2UPDATE)GetProcAddress(hLibrary, LFX_DLL_UPDATE);
			ReleaseFunction = (LFX2RELEASE)GetProcAddress(hLibrary, LFX_DLL_RELEASE);
			// AlienFX must be initialise before any of its functions are invoked.
			result = InitFunction();
			if (result == LFX_SUCCESS){
				cout << "PASS... AlienFX Initialised. \n" << endl;
				DisplaySystemDetails();
			}
			else{
				cout << "FAIL... AlienFX Initialisation error. \n " << result << endl;
			}
		}
		else{
			cout << "FAIL... AlienFX library load error. \n " << endl;
		}
	}

	void LightSystem::DisplaySystemDetails(){
		if (!hLibrary) return;
		unsigned int numDevs = 0;
		result = GetNumDevicesFunction(&numDevs);

		if (result == LFX_SUCCESS){
			cout << "AlienFX device count : " << numDevs << endl;
			//for (int i = 0; i < numDevs; i++)
			//{
			//	DisplayDeviceDetails(i);
			//}
		}
		else {
			cout << "AlienFX error getting the number of devices : " << endl;
		}
	}

	void LightSystem::DisplayDeviceDetails(unsigned int deviceId){
		if (!hLibrary) return;
		const unsigned int descSize = 255;
		unsigned char devType = 0;
		char description[descSize];
		result = GetDeviceDescriptionFunction(deviceId, description, descSize, &devType);
		if (result == LFX_SUCCESS){
			cout << "AlienFX device " << deviceId << " description : " << description << endl;
			//for (int i = 0; i < 2; i++)
			//{
			//	DisplayLightDetails(i, i);
			//}
		}
		else {
			cout << "AlienFX error getting device description : " << endl;
		}
	}

	void LightSystem::DisplayLightDetails(unsigned int deviceId, unsigned int lightId){
		if (!hLibrary) return;
		const unsigned int descSize = 255;
		unsigned char devType = 0;
		char description[descSize];
		result = GetLightDescriptionFunction(deviceId, lightId, description, descSize);
		if (result == LFX_SUCCESS){
			cout << "AlienFX light " << lightId << " description : " << description << endl;
		}
		else {
			cout << "AlienFX error getting light description : " << endl;
		}
	}
	
	void LightSystem::SetAllLights(glm::vec3 rgb)
	{
		LightSystem::SetLight(0, 1, rgb, 255);//side
		LightSystem::SetLight(0, 2, rgb, 255);//side
		LightSystem::SetLight(2, 0, rgb, 255);//keyboard
	}


	bool LightSystem::SetLight(unsigned int deviceId, unsigned int lightId, glm::vec3 col, int brightness){
		if (!hLibrary) return LFX_FAILURE;
		LFX_COLOR colour;
		colour.brightness = brightness;
		colour.red = col.x;
		colour.green = col.y;
		colour.blue = col.z;
		unsigned int result = SetLightColorFunction(deviceId, lightId, &colour);
		if (result != LFX_SUCCESS){
			cout << "AlienFX Set light error : " << result << endl;
		}
		result = UpdateFunction();
		if (result != LFX_SUCCESS){
			cout << "Update Error : " << result << endl;
		}
		return (result == LFX_SUCCESS);
	}

	void LightSystem::ResetLights(glm::vec3 rgb)
	{
		LightSystem::SetLight(0, 1, rgb, 0);//side
		LightSystem::SetLight(0, 2, rgb, 0);//side
		LightSystem::SetLight(2, 0, rgb, 0);//keyboard
	}

	void LightSystem::ShutDown()
	{
		ReleaseFunction();
		if (hLibrary != NULL)
		{
			FreeLibrary(hLibrary);
		}
	}

	LightSystem::~LightSystem()
	{
	}
}
