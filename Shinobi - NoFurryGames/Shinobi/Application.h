#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "SDL/include/SDL_timer.h"

#define NUM_MODULES 21


class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModuleScene_Intro;
class ModuleScene_Intro2;
class ModuleScene_Level1;
class ModuleScene_Level1_SecondFloor;
class ModuleScene_Level1_SecondFloor_Enemies;

class ModuleScene_Level2;

class ModuleScene_Boss1;

class ModuleScene_MainMenu;
class ModuleParticles;
class ModuleCollisions;
class ModuleRender;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleBoss;
class ModuleFonts;
class ModuleInterface;

class Application
{

private:
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];
	Module* activeModule = nullptr;

	bool debugMode = false;
	double deltaTime = 0;


	int life_num;


	//Fonts
	int scoreFontRed = -1;
	int scoreFontBlue = -1;
	int scoreFontWhite = -1;
	int scoreFontYellow = -1;
	int debugFontWhite = -1;
	char scoreText[10] = { "\0" };

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;

	ModulePlayer* player = nullptr;
	ModuleScene_Level1* scene_Level1 = nullptr;
	ModuleScene_Level1_SecondFloor* scene_Level1_SecondFloor = nullptr;
	ModuleScene_Level1_SecondFloor_Enemies* scene_Level1_SecondFloor_Enemies = nullptr;
	ModuleScene_MainMenu* scene_MainMenu = nullptr;
	ModuleScene_Intro* scene_Intro = nullptr;
	ModuleScene_Intro2* scene_Intro2 = nullptr;
	ModuleScene_Level2* scene_Level2 = nullptr;

	ModuleScene_Boss1* scene_Boss1 = nullptr;
	ModuleBoss* boss = nullptr;

	ModuleParticles* particles = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleEnemies* enemy = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleFadeToBlack* fade = nullptr;
	ModuleRender* render = nullptr;
	ModuleInterface* interface_module = nullptr;

	
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__