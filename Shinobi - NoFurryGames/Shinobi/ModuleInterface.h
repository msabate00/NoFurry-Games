#ifndef __MODULE_INTERFACE_H__
#define __MODULE_INTERFACE_H__

#include "Module.h"
#include "SDL/include/SDL_Rect.h"
#include "SDL/include/SDL_render.h"

#include <stack>
#include <vector>
#include <iostream>
struct SDL_Texture;
struct SDL_Renderer;

class ModuleInterface : public Module
{
public:
	//Constructor
	ModuleInterface(bool startEnabled);

	//Destructor
	~ModuleInterface();

	// Called on application start.
	// Creates the rendering context using the program's window.
	bool Start() override;

	// Called at the beginning of the application loop
	// Clears the rendering context to a background color
	update_status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles camera movement
	update_status Update() override;

	// Called at the end of the application loop.
	// Displays a rectangle in the rendering context
	// Updates the screen with the rendered content
	update_status PostUpdate() override;

	// Called on application exit.
	// Destroys the rendering context
	bool CleanUp() override;

	//MainMenu

	void printYear();
	void printIconC();
	void printNom();
	void printLetra();
	double letraGetX();
	double letraGetY();
	void InsertCoin();


	//LV1
	void printSkillIcon();
	void printHostageIcon(int);
	void printLifeIcon(int);
	void printNum(int point);
	void printTime(std::string time, SDL_Texture* texture);
	void printPlayer1();
	void printGoNext();
	void printGoIcon();
	int updateTimer(time_t start_time);
	std::vector<int> getDigits(int number);
	std::string getTimeString(int elapsed_seconds);


public:
	

	//MainMenu

	SDL_Texture* Letra = nullptr;
	SDL_Texture* LogoMedio = nullptr;
	//SDL_Texture* LogoC = nullptr;
	SDL_Texture* LetraYear = nullptr;
	SDL_Texture* LetraIconC = nullptr;
	SDL_Texture* LetraNomRed = nullptr;
	SDL_Texture* LetraNomWhite = nullptr;
	//int texture_Year = 1987;
	bool NameColor = true;

	//PrintaLetra ÈÌ
	double letraX = 0;//SCREEN_WIDTH - 400
	double letraY = 0;//SCREEN_HEIGHT - 200
	double CENTER_X = SCREEN_WIDTH - 240;
	double CENTER_Y = SCREEN_HEIGHT - 200;
	double A = 200;
	double B = 200;
	double angle = 0;
	const double ROTATION_SPEED = 6;
	int coinNum = 0;
	float timer = 0.0f;
	float timerGonext = 0.0f;
	float timerGoIcon = 0.0f;
	//Canbiar Color SHINOBI
	//const float switchTime = 100.0f; // Tiempo Cambiar Color



	//LV1

	SDL_Texture* SkillIcon = nullptr;
	SDL_Texture* HostageIcon = nullptr;
	SDL_Texture* LifeIcon = nullptr;
	SDL_Texture* LetraNum = nullptr;
	SDL_Texture* save = nullptr;
	SDL_Texture* Time = nullptr;
	SDL_Texture* dosPunt = nullptr;
	SDL_Texture* Player1 = nullptr;
	SDL_Texture* goIcon = nullptr;

	int hostage_num = 4;
	bool hostageTaken[4] = { false };
	int texture_num = 0;
	int elapsed_time;

	time_t start_time;
	int total_time = 180;
	std::string time_string;
	//Canbiar Color SHINOBI
	int rankingNum = 100000;
	
	const float switchTime = 250.0f; // Tiempo Cambiar Color
	const float switchTimeInsertCoin = 900.0f;

	int GoIconPosition = -1580;//-1580

};

#endif //__MODULE_RENDER_H__
