#ifndef __MODULE_SCENE2_H__
#define __MODULE_SCENE2_H__

#include "Module.h"
#include "Animation.h"

#include <stack>
#include <vector>
#include <iostream>

using namespace std;

struct SDL_Texture;

class ModuleScene_Level2 : public Module
{
public:
	//Constructor
	ModuleScene_Level2(bool startEnabled);

	//Destructor
	~ModuleScene_Level2();

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

	//Print Class
	
	void printSkillIcon();
	void printHostageIcon(int);
	void printLifeIcon(int);
	void printNum(std::vector<int> num, SDL_Texture* texture);
	void printTime(std::string time, SDL_Texture* texture);
	void printPlayer1();

	std::vector<int> getDigits(int number);

	int updateTimer(time_t start_time);
	std::string getTimeString(int elapsed_seconds);
	


public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* stageTexture2 = nullptr;
	SDL_Texture* stageBackgroundTexture2 = nullptr;


	// The sprite rectangle for the ground
	SDL_Rect ground;

	// The sprite section for the background
	SDL_Rect background;

	//Collider* secondFloor;
	// create a stack of integers
	stack<Collider*> colliders;
	Collider* finalLevel;


	/*
	
	*/
	SDL_Texture* SkillIcon = nullptr;
	SDL_Texture* HostageIcon = nullptr;
	SDL_Texture* LifeIcon = nullptr;
	SDL_Texture* LetraNum = nullptr;
	SDL_Texture* save = nullptr;
	SDL_Texture* Time = nullptr;
	SDL_Texture* dosPunt = nullptr;
	SDL_Texture* Player1 = nullptr;


	int hostage_num = 4;



	int life_num = 2;
	int texture_num = 0;

	int elapsed_time;
	time_t start_time;
	int total_time = 180;
	std::string time_string;

	//Canbiar Color SHINOBI
	float timer = 0.0f;
	const float switchTime = 250.0f; // Tiempo Cambiar Color
	bool NameColor = true;
};

#endif