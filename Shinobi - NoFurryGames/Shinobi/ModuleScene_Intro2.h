#ifndef __MODULE_SCENE_INTROTWO_H__
#define __MODULE_SCENE_INTROTWO_H__

#include "Module.h"
#include "Animation.h"
#include <vector>
#include <iostream>
#include <string> 

struct SDL_Texture;

class ModuleScene_Intro2 : public Module
{
public:
	//Constructor
	ModuleScene_Intro2(bool startEnabled);

	//Destructor
	~ModuleScene_Intro2();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate();





public:

	// The scene sprite sheet loaded into an SDL_Texture



	SDL_Texture* textureBackground = nullptr;
	SDL_Rect background;


	Animation* currentAnimation = nullptr;
	Animation backgroundAnim;

};

#endif