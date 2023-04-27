#ifndef __MODULE_SCENE_SECONDFLOOR_ENEMIES_H__
#define __MODULE_SCENE_SECONDFLOOR_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class ModuleScene_Level1_SecondFloor_Enemies : public Module
{
public:
	//Constructor
	ModuleScene_Level1_SecondFloor_Enemies(bool startEnabled);

	//Destructor
	~ModuleScene_Level1_SecondFloor_Enemies();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate();

	bool CleanUp();


public:

	SDL_Texture* up_level_fenceTexture = nullptr;
	SDL_Rect up_level_fence1Rect;
	SDL_Rect up_level_fence2Rect;
	SDL_Rect up_level_fence3Rect;


};

#endif