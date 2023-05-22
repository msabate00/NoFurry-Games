#include "ModuleMapa2.h"

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

ModuleMapa2::ModuleMapa2(bool startEnabled) : Module(startEnabled) {}

ModuleMapa2::~ModuleMapa2() {}

// Load assets
bool ModuleMapa2::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	mapaWhite = App->textures->Load("Assets/Interface/ZoneChange/Nivel2/AlNivel2_Blanco_0.png");
	mapaRed = App->textures->Load("Assets/Interface/ZoneChange/Nivel2/AlNivel2_Rojo_0.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	currentAnimation = &backgroundAnim;


	MapaX = SCREEN_WIDTH - 25;
	MapaY = SCREEN_HEIGHT + 25;

	return ret;
}

update_status ModuleMapa2::Update()
{


	App->interface_module->timer += App->deltaTime;

	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->interface_module->timer >= 3000) {
		App->interface_module->resetTimer(); 
		App->interface_module->hostage_num = 3;
		App->interface_module->gameChange = true;
		App->interface_module->resetTimeHostage = true;
		App->interface_module->timerPR = 0;
		App->interface_module->spacePoint = true;
		App->fade->FadeToBlack(this, (Module*)App->scene_Level2, 20);
	}


	if (App->input->keys[SDL_SCANCODE_F9] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Level1, 20);
	}

	if (App->input->keys[SDL_SCANCODE_F10] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Level2, 20);
	}

	if (App->input->keys[SDL_SCANCODE_F11] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Boss1, 20);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleMapa2::PostUpdate()
{
	printMapa2();

	return update_status::UPDATE_CONTINUE;
}


void ModuleMapa2::printMapa2() {
	App->interface_module->timer += App->deltaTime;

	if (App->interface_module->NameColor && App->interface_module->timer >= 1000) {

		App->render->Blit(mapaWhite, MapaX, MapaY, SDL_FLIP_NONE, nullptr, 1);
		App->interface_module->NameColor = false;
		if (MapaX < 122 && MapaX > 116 && MapaY < 12 && MapaY > 6) {
			MapaX = 119;
			MapaY = 9;

			if (App->interface_module->timer >= 3000) {

				MapaX -= 16;
				MapaY -= 16;
			}
		}
		else {
			
			MapaX -= 15;
			MapaY -= 15;
		}

	}
	else {
		App->render->Blit(mapaRed, MapaX, MapaY, SDL_FLIP_NONE, nullptr, 1);
		App->interface_module->NameColor = true;
		if (MapaX < 122 && MapaX > 116 && MapaY < 12 && MapaY > 6) {
			MapaX = 119;
			MapaY = 9;

			if (App->interface_module->timer >= 3000) {

				MapaX -= 16;
				MapaY -= 16;
			}
		}
		else {
			MapaX -= 15;
			MapaY -= 15;
		}
	}
}
