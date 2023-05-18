#pragma once
#pragma once
#ifndef __MODULE_SCENE_InputName_H__
#define __MODULE_SCENE_InputName_H__

#include "Module.h"
#include "Animation.h"
#include <vector>
#include <iostream>
#include <string> 

struct SDL_Texture;

class ModuleInputName : public Module
{
public:
	//Constructor
	ModuleInputName(bool startEnabled);

	//Destructor
	~ModuleInputName();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate();


	void prinIcon();
	void printTitle();
	

public:

	// The scene sprite sheet loaded into an SDL_Texture



	SDL_Texture* dosComa = nullptr;
	SDL_Texture* textureBackground = nullptr;


	SDL_Texture** iconType = new SDL_Texture * [2];
	SDL_Texture* ranking = nullptr;

	SDL_Rect background;
	Animation* currentAnimation = nullptr;
	Animation backgroundAnim;


	char inputidle[36];


	float timerIconChange = 0.0f;
	float timerColorChange = 0.0f;



};

#endif