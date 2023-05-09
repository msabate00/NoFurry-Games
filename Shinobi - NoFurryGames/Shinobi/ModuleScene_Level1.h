#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

#include <stack>
#include <vector>
#include <iostream>

using namespace std;

struct SDL_Texture;

class ModuleScene_Level1 : public Module
{
public:
	//Constructor
	ModuleScene_Level1(bool startEnabled);

	//Destructor
	~ModuleScene_Level1();

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
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* stageTexture = nullptr;
	SDL_Texture* stageBackgroundTexture = nullptr;
	
	
	// The sprite rectangle for the ground
	SDL_Rect ground;

	// The sprite section for the background
	SDL_Rect background;

	//Collider* secondFloor;
	// create a stack of integers
	stack<Collider*> colliders;
	Collider* finalLevel;
	
};

#endif