/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include "PeggleApplicationPCH.h"
#include <Vision/Runtime/Framework/VisionApp/VAppImpl.hpp>

#include <Vision/Runtime/Framework/VisionApp/Modules/VHelp.hpp>

// Use the following line to initialize a plugin that is statically linked.
// Note that only Windows platform links plugins dynamically (on Windows you can comment out this line).
VIMPORT IVisPlugin_cl* GetEnginePlugin_PegglePlugin();

class PeggleApplicationClass : public VAppImpl
{
public:
	PeggleApplicationClass() {}
	virtual ~PeggleApplicationClass() {}

	virtual void SetupAppConfig(VisAppConfig_cl& config) HKV_OVERRIDE;
	virtual void PreloadPlugins() HKV_OVERRIDE;

	virtual void Init() HKV_OVERRIDE;
	virtual void AfterSceneLoaded(bool bLoadingSuccessful) HKV_OVERRIDE;
	virtual bool Run() HKV_OVERRIDE;
	virtual void DeInit() HKV_OVERRIDE;
};

VAPP_IMPLEMENT_SAMPLE(PeggleApplicationClass);

void PeggleApplicationClass::SetupAppConfig(VisAppConfig_cl& config)
{
	// Set custom file system root name ("havok_sdk" by default)
	config.m_sFileSystemRootName = "template_root";

	// Set the initial starting position of our game window and other properties
	// if not in fullscreen. This is only relevant on windows
	config.m_videoConfig.m_iXRes = 1024; // Set the Window size X if not in fullscreen.
	config.m_videoConfig.m_iYRes = 768;  // Set the Window size Y if not in fullscreen.
	config.m_videoConfig.m_iXPos = 50;   // Set the Window position X if not in fullscreen.
	config.m_videoConfig.m_iYPos = 50;   // Set the Window position Y if not in fullscreen.

	// Name to be displayed in the windows title bar.
	config.m_videoConfig.m_szWindowTitle = "Pe99le";

	config.m_videoConfig.m_bWaitVRetrace = true;

	// Fullscreen mode with current desktop resolution
  
	#if defined(WIN32)
	/*
	DEVMODEA deviceMode;
	deviceMode = Vision::Video.GetAdapterMode(config.m_videoConfig.m_iAdapter);
	config.m_videoConfig.m_iXRes = deviceMode.dmPelsWidth;
	config.m_videoConfig.m_iYRes = deviceMode.dmPelsHeight;
	config.m_videoConfig.m_bFullScreen = true;
	*/
	#endif  
}

void PeggleApplicationClass::PreloadPlugins()
{
	// Use the following line to load a plugin. Remember that, except on Windows platform, in addition
	// you still need to statically link your plugin library (e.g. on mobile platforms) through project
	// Properties, Linker, Additional Dependencies.
	VISION_PLUGIN_ENSURE_LOADED(PegglePlugin);
}

// Init function. Here we trigger loading our scene
void PeggleApplicationClass::Init()
{
  // Set filename and paths to our stand alone version.
  // Note: "/Data/Vision/Base" is always added by the sample framework
  VisAppLoadSettings settings("Scenes/Level_01.pcdx9.vscene");
  settings.m_customSearchPaths.Append(":template_root/Assets");
  LoadScene(settings);
}


void PeggleApplicationClass::AfterSceneLoaded(bool bLoadingSuccessful)
{
  // Define some help text
  VArray<const char*> help;
  help.Append("How to use this demo...");
  help.Append("");
  RegisterAppModule(new VHelp(help));

  // Create a mouse controlled camera (set above the ground so that we can see the ground)
  //Vision::Game.CreateEntity("VisMouseCamera_cl", hkvVec3(0.0f, 0.0f, 170.0f));
}

// Main Loop of the application
bool PeggleApplicationClass::Run()
{
  return true;
}

void PeggleApplicationClass::DeInit()
{
  // De-Initialization
  // [...]
}