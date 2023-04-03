#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "SDL/include/SDL_timer.h"

#define NUM_MODULES 7

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModulePlayer;
class ModuleScene;
class ModuleRender;
class ModuleParticles;

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
	ModuleScene* scene = nullptr;

	ModuleRender* render = nullptr;

	ModuleParticles* particles = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__