#include "ModuleMapa3.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"
#include "ModuleInterface.h"

#include "SDL/include/SDL.h"
#include <string> 
#include <vector>
#include <iostream>
#include <cmath>

ModuleMapa3::ModuleMapa3(bool startEnabled) : Module(startEnabled) {}

ModuleMapa3::~ModuleMapa3() {}

// Load assets
bool ModuleMapa3::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	mapaWhite = App->textures->Load("Assets/Interface/ZoneChange/Nivel3/AlNivel3_Blanco_0.png");
	mapaRed = App->textures->Load("Assets/Interface/ZoneChange/Nivel3/AlNivel3_Rojo_0.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	currentAnimation = &backgroundAnim;

	MapaX = -15;
	MapaY = -130;
	
	timerMapa3 = 0.0f;

	return ret;
}

update_status ModuleMapa3::Update()
{
	GamePad& pad = App->input->pads[0];
	App->interface_module->timer += App->deltaTime;

	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || pad.a_down || pad.b_down || App->interface_module->timer >= 3000) {
		App->interface_module->resetTimer();
		App->interface_module->gameChange = true;
		App->interface_module->spacePoint = true;
		App->interface_module->timerPR = 0;
		App->fade->FadeToBlack(this, (Module*)App->scene_Boss1, 20);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleMapa3::PostUpdate()
{
	printMapa3();

	return update_status::UPDATE_CONTINUE;
}


void ModuleMapa3::printMapa3() {
	timerMapa3 += App->deltaTime;


	if (App->interface_module->NameColor && timerMapa3 >= 500) {

		App->render->Blit(mapaWhite, MapaX, MapaY, SDL_FLIP_NONE, nullptr, 1);
		App->interface_module->NameColor = false;
		if (MapaX < 122 && MapaX > 116 && MapaY < 12 && MapaY > 4) {
			MapaX = 119;
			MapaY = 9;
			if (timerMapa3 >= 2000) {

				MapaX += 16;
				MapaY += 16;
			}
		}
		else {

			MapaX += 15;
			MapaY += 15;
		}

	}
	else {
		App->render->Blit(mapaRed, MapaX, MapaY, SDL_FLIP_NONE, nullptr, 1);
		App->interface_module->NameColor = true;
		if (MapaX < 122 && MapaX > 116 && MapaY < 12 && MapaY > 4) {
			MapaX = 119;
			MapaY = 9;

			if (timerMapa3 >= 2000) {

				MapaX += 16;
				MapaY += 16;
			}
		}
		else {
			MapaX += 15;
			MapaY += 15;
		}
	}


}
