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
	void printInput();
	void printdardos();
	void printNomSelect(int posX, int posY);
	void printNom();
	void deleteNom();

public:

	// The scene sprite sheet loaded into an SDL_Texture



	SDL_Texture* dosComa = nullptr;
	SDL_Texture* textureBackground = nullptr;


	SDL_Texture** iconType = new SDL_Texture * [2];
	SDL_Texture* ranking = nullptr;
	SDL_Texture* dardosWhite = nullptr;
	SDL_Texture* dardosRed = nullptr;
	SDL_Texture* ED = nullptr;

	SDL_Rect background;
	Animation* currentAnimation = nullptr;
	Animation backgroundAnim;

	char input_array[5][7] = {
	{'a', 'b', 'c', 'd', 'e', 'f', 'g'},
	{'h', 'i', 'j', 'k', 'l', 'm', 'n'},
	{'o', 'p', 'q', 'r', 's', 't', 'u'},
	{'v', 'w', 'x', 'y', 'z', '1', '2'},
	{'3', '4', '5', '6', '7', '8', '9'}
	};
	

	float timerIconChange = 0.0f;
	float timerColorChange = 0.0f;


	int dardosPositionX = 335;
	int dardosPositionY = 185;
	int letraposX;
	int letraposY;

	char myName[4];
	int myNamelist = 0;

	char namecharacter[2] = "";
};

#endif