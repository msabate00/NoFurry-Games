#ifndef __MODULE_SCENE_MAINMENU_H__
#define __MODULE_SCENE_MAINMENU_H__

#include "Module.h"
#include "Animation.h"
#include <vector>
#include <iostream>

struct SDL_Texture;

class ModuleScene_MainMenu : public Module
{
public:
	//Constructor
	ModuleScene_MainMenu(bool startEnabled);

	//Destructor
	~ModuleScene_MainMenu();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate();


	void printYear(std::vector<int> num, SDL_Texture* texture);
	void printIconC();
	void printNom();
	void printLetra();
	double letraGetX();
	double letraGetY();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	
	

	SDL_Texture* textureBackground = nullptr;
	SDL_Texture* textureBackground2 = nullptr;

	/*SDL_Texture* textureBackgroundResized;
	SDL_Texture* texture;
	SDL_Texture* GetResizedTexture(SDL_Texture* texture, int width, int height);*/

	Animation* currentAnimation = nullptr;
	Animation eyesAnimation;

	SDL_Texture* Letra = nullptr;
	SDL_Texture* LogoMedio = nullptr;
	SDL_Texture* LogoC = nullptr;

	// The sprite rectangle for the ground
	SDL_Rect ground;

	// The sprite section for the background
	SDL_Rect background;


	Collider* secondFloor;

	uint monedaFX = 0;


	SDL_Texture* LetraYear = nullptr;
	SDL_Texture* LetraIconC = nullptr;
	SDL_Texture* LetraNom = nullptr;
	int texture_Year = 1987;
	bool NameColor = true;

	//PrintaLetra ÈÌ
	double letraX = 0;//SCREEN_WIDTH - 400
	double letraY = 0;//SCREEN_HEIGHT - 200
	double CENTER_X = SCREEN_WIDTH - 240;
	double CENTER_Y = SCREEN_HEIGHT - 200;
	double A = 200;
	double B = 200;
	double angle = 0;
	double ROTATION_SPEED = 6;
	int sumapix = 0;

	//Canbiar Color SHINOBI
	float timer = 0.0f;
	const float switchTime = 100.0f; // Tiempo Cambiar Color
};

#endif