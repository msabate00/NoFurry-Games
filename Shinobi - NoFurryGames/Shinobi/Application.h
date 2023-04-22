#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "SDL/include/SDL_timer.h"

#define NUM_MODULES 12

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModuleScene_Level1;
class ModuleScene_MainMenu;
class ModuleParticles;
class ModuleCollisions;
class ModuleRender;
class ModuleEnemies;
class ModuleFadeToBlack;


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

	bool godMode = false;
	double deltaTime = 0;


	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;

	ModulePlayer* player = nullptr;
	ModuleScene_Level1* scene = nullptr;
	ModuleScene_MainMenu* scene_MainMenu = nullptr;

	ModuleParticles* particles = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleEnemies* enemy = nullptr;


	ModuleFadeToBlack* fade = nullptr;
	ModuleRender* render = nullptr;

	
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__