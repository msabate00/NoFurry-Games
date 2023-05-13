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

	return ret;
}

update_status ModuleMapa3::Update()
{

	App->interface_module->timer += App->deltaTime;

	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->interface_module->timer >= 3000) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Boss1, 20);
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
update_status ModuleMapa3::PostUpdate()
{
	printMapa3();

	return update_status::UPDATE_CONTINUE;
}


void ModuleMapa3::printMapa3() {
	App->interface_module->timer += App->deltaTime;


	if (App->interface_module->NameColor && App->interface_module->timer >= 1000) {

		App->render->Blit(mapaWhite, MapaX, MapaY, SDL_FLIP_NONE, nullptr, 1);
		App->interface_module->NameColor = false;
		if (MapaX < 122 && MapaX > 116 && MapaY < 12 && MapaY > 6) {
			MapaX = 119;
			MapaY = 9;

			if (App->interface_module->timer >= 2000) {

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
		if (MapaX < 122 && MapaX > 116 && MapaY < 12 && MapaY > 6) {
			MapaX = 119;
			MapaY = 9;

			if (App->interface_module->timer >= 2000) {

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
