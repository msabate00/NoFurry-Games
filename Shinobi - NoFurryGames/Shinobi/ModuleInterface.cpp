#include "ModuleRender.h"
#include <string> 
#include <iostream>
#include <vector>
#include "Application.h"
#include <chrono>
#include <thread>

#include "ModuleWindow.h"
#include "ModuleInterface.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level2.h"
#include "ModuleScene_Boss1.h"
#include "ModuleFonts.h"


#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"



using namespace std;

ModuleInterface::ModuleInterface(bool startEnabled) : Module(startEnabled)
{

}

ModuleInterface::~ModuleInterface()
{

}

bool ModuleInterface::Init()
{
	bool ret = true;



	return ret;


}

// Called every draw update
update_status ModuleInterface::PreUpdate()
{
	

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleInterface::Update()
{

	

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleInterface::PostUpdate()
{

	//INTERFAZ COMUN PARA TODO EL JUEGO

	if (App->scene_Level1->IsEnabled() || App->scene_Level2->IsEnabled() || App->scene_Boss1->IsEnabled()) {
		//INTERFAZ PARA TODOS LOS NIVELES JUGABLES
	
	}
	



	if (App->scene_Level1->IsEnabled()) {
		//INTERFAZ PARA EL NIVEL 1



	}
	else if (App->scene_Level2->IsEnabled()) {
		//INTERFAZ PARA EL NIVEL 2


	}
	else if (App->scene_Boss1->IsEnabled()) {
		//INTERFAZ PARA EL JEFE
	
	
	
	}


	//INTERFAZ DEL GODMODE
	if (App->debugMode) {
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 240);
		SDL_Rect dstRect{
		(int)(-App->render->camera.x * 0) + 0 * SCREEN_SIZE,
		(int)(-App->render->camera.y * 0) + 0 * SCREEN_SIZE,
		160 * SCREEN_SIZE, 97 * SCREEN_SIZE };

		SDL_RenderFillRect(App->render->renderer, &dstRect);
		App->fonts->BlitText(0, 0, App->debugFontWhite, "f1 - t0ggle debugM0de");
		App->fonts->BlitText(0, 8, App->debugFontWhite, "f2 - weap0n switcher");
		App->fonts->BlitText(0, 16, App->debugFontWhite, "f3 - xxxxxxx");
		App->fonts->BlitText(0, 24, App->debugFontWhite, "f4 - xxxxxxx");
		App->fonts->BlitText(0, 32, App->debugFontWhite, "f5 - l0ad mainmenu");
		App->fonts->BlitText(0, 40, App->debugFontWhite, "f6 - xxxxxxx");
		App->fonts->BlitText(0, 48, App->debugFontWhite, "f7 - xxxxxxx");
		App->fonts->BlitText(0, 56, App->debugFontWhite, "f8 - xxxxxxx");
		App->fonts->BlitText(0, 64, App->debugFontWhite, "--- in main menu ---");
		App->fonts->BlitText(0, 72, App->debugFontWhite, "f9 - l0ad level1");
		App->fonts->BlitText(0, 80, App->debugFontWhite, "f10 - l0ad level2");
		App->fonts->BlitText(0, 88, App->debugFontWhite, "f11 - l0ad level_b0ss");



	}


	return update_status::UPDATE_CONTINUE;
}

bool ModuleInterface::CleanUp()
{


	return true;
}



