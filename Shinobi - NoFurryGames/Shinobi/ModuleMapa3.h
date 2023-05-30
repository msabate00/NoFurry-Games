#pragma once
#pragma once
#pragma once
#ifndef __MODULE_SCENE_MAPA3_H__
#define __MODULE_SCENE_MAPA3_H__

#include "Module.h"
#include "Animation.h"
#include <vector>
#include <iostream>
#include <string> 

struct SDL_Texture;

class ModuleMapa3 : public Module
{
public:
	//Constructor
	ModuleMapa3(bool startEnabled);

	//Destructor
	~ModuleMapa3();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate();


	void printMapa3();

public:

	// The scene sprite sheet loaded into an SDL_Texture



	SDL_Texture* dosComa = nullptr;
	SDL_Texture* mapaWhite = nullptr;
	SDL_Texture* mapaRed = nullptr;
	SDL_Rect background;


	Animation* currentAnimation = nullptr;
	Animation backgroundAnim;


	int MapaX = -15;
	int MapaY = -130;//-15
	float timerMapa3 = 0.0f;


};

#endif