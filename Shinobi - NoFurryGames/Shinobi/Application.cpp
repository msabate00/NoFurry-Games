#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Intro.h"
#include "ModuleScene_Intro2.h"
#include "ModuleMision1.h"
#include "ModuleMapa1.h"
#include "ModuleScene_Level1_SecondFloor.h"
#include "ModuleScene_Level1_SecondFloor_Enemies.h"

#include "ModuleMapa2.h"
#include "ModuleScene_Level2.h"

#include "ModuleMapa3.h"
#include "ModuleBoss.h"
#include "ModuleMapaV.h"
#include "ModuleRanking.h"


#include "ModuleScene_MainMenu.h"
#include "ModuleScene_Boss1.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleParticlesBoss.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleHostage.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"

#include <iostream>
#include "SDL/include/SDL_scancode.h"
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
	activeModule =	scene_Intro;
	modules[4] =	scene_Intro2 =						new ModuleScene_Intro2(false);
	modules[5] =	scene_MainMenu =					new ModuleScene_MainMenu(false);

	//Level1
	modules[6] =	mision1 =							new ModuleMision1(false);
	modules[7] =	mapa1 =								new ModuleMapa1(false);
	modules[8] = scene_Level1 =							new ModuleScene_Level1(false);


	//Level 2
	
	modules[9] =	mapa2 =								new ModuleMapa2(false);
	modules[10] =	scene_Level2 =						new ModuleScene_Level2(false);
	modules[11] =	enemy =								new ModuleEnemies(false);
	modules[12] =	hostages =							new ModuleHostage(false);
	modules[13] =	scene_Level1_SecondFloor_Enemies =	new ModuleScene_Level1_SecondFloor_Enemies(false);

	modules[14] =	mapa3 =								new ModuleMapa3(false);
	modules[15] =	scene_Boss1 =						new ModuleScene_Boss1(false);
	modules[16] =	boss =								new ModuleBoss(false);
	modules[17] =	mapaV=								new ModuleMapaV(false);
	modules[18] =	ranking =							new ModuleRanking(false);
	
	modules[19] = player =								new ModulePlayer(false);
	modules[20] = scene_Level1_SecondFloor =			new ModuleScene_Level1_SecondFloor(false);
	modules[21] = particles =							new ModuleParticles(true);
	modules[22] = particlesBoss =							new ModuleParticlesBoss(true);
	modules[23] = collisions =							new ModuleCollisions(true);
	modules[24] = audio =								new ModuleAudio(true);
	modules[25] = fonts =								new ModuleFonts(true);
	modules[26] = interface_module =					new ModuleInterface(true); // <------- SIEMPRE TIENE QUE CARGAR EL ANTEULTIMO
	modules[27] = fade =								new ModuleFadeToBlack(true); // <------- SIEMPRE TIENE QUE CARGAR EL PENULTIMO
	modules[28] = render =								new ModuleRender(true); // <----- SIEMPRE SE TIENE QUE CARGAR EL ULTI



	


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


	char lookupTable[] = { "0123456789       abcdefghijklmnopqrstuvwxyz_?,-  " };
	scoreFontRed = fonts->Load("Assets/Interface/Fonts/Red.png", lookupTable, 3);
	scoreFontBlue = fonts->Load("Assets/Interface/Fonts/Blue.png", lookupTable, 3);
	scoreFontWhite = fonts->Load("Assets/Interface/Fonts/White.png", lookupTable, 3);
	scoreFontYellow = fonts->Load("Assets/Interface/Fonts/Yellow.png", lookupTable, 3);
	debugFontWhite = fonts->Load("Assets/Interface/Fonts/DebugFont.png", lookupTable, 3);

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


	
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN) {
		godMode = !godMode;
	}
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN) {
		showRect = !showRect;
	}
	if (App->input->keys[SDL_SCANCODE_F6] == KEY_DOWN) {
		showDebug = !showDebug;
	}


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
