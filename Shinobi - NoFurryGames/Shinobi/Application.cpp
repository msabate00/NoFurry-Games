#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Intro.h"
#include "ModuleScene_Intro2.h"
#include "ModuleScene_Level1_SecondFloor.h"
#include "ModuleScene_Level1_SecondFloor_Enemies.h"
#include "ModuleBoss.h"
#include "ModuleScene_MainMenu.h"
#include "ModuleScene_Boss1.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_timer.h"

#include <iostream>
using namespace std;

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] =	window =							new ModuleWindow(true);
	modules[1] =	input =								new ModuleInput(true);
	modules[2] =	textures =							new ModuleTextures(true);
	modules[3] =	scene_Intro =						new ModuleScene_Intro(true);
	modules[4] =	scene_Intro2 =						new ModuleScene_Intro2(false);
	modules[5] =	scene_MainMenu =					new ModuleScene_MainMenu(false);

	//Level1
	modules[6] =	scene_Level1 =						new ModuleScene_Level1(false);				//off
	modules[7] =	enemy =								new ModuleEnemies(false);					//off
	modules[8] =	scene_Level1_SecondFloor_Enemies =	new ModuleScene_Level1_SecondFloor_Enemies(false);	//off

	//Level 2

	//Level Boss
	modules[9]	=	scene_Boss1 =							new ModuleScene_Boss1(false);
	modules[10] =	boss =									new ModuleBoss(false);


	modules[11]	=	player =							new ModulePlayer(false);					//off
	modules[12] =	scene_Level1_SecondFloor =			new ModuleScene_Level1_SecondFloor(false);	//off
	modules[13] =	particles =							new ModuleParticles(true);
	modules[14] =	collisions =						new ModuleCollisions(true);
	modules[15] =	audio =								new ModuleAudio(true);
	modules[16] =	fade =								new ModuleFadeToBlack(true);
	modules[17] =	render =							new ModuleRender(true); // <----- SIEMPRE SE TIENE QUE CARGAR EL ULTIMO <----

}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;
	

	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());



	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;


	

	// Cap to 60 FPS
	SDL_Delay(16.666f);

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
