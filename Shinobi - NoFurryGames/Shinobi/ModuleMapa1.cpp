#include "ModuleMapa1.h"

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

ModuleMapa1::ModuleMapa1(bool startEnabled) : Module(startEnabled){}

ModuleMapa1::~ModuleMapa1(){}

// Load assets
bool ModuleMapa1::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	mapaWhite= App->textures->Load("Assets/Interface/ZoneChange/Nivel1/AlNivel1_Blanco_0.png");
	mapaRed = App->textures->Load("Assets/Interface/ZoneChange/Nivel1/AlNivel1_Rojo_0.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	currentAnimation = &backgroundAnim;

	App->interface_module->hostage_num = 4;

	MapaX = -70;
	MapaY = SCREEN_HEIGHT - 15;

	return ret;
}

update_status ModuleMapa1::Update()
{

	App->interface_module->timer += App->deltaTime;

	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN ||  App->interface_module->timer >= 3000) {
		App->interface_module->resetTimer();
		App->interface_module->gameChange = true;
		App->interface_module->texture_num = 0;
		App->interface_module->hostage_num = 4;
		App->interface_module->resetTimeHostage = true;
		App->interface_module->timerPR = 0;
		App->interface_module->spacePoint = true;
		App->fade->FadeToBlack(this, (Module*)App->scene_Level1, 20);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleMapa1::PostUpdate()
{
	printMapa1();

	return update_status::UPDATE_CONTINUE;
}


void ModuleMapa1::printMapa1() {
	App->interface_module->timer += App->deltaTime;

	if (App->interface_module->NameColor && App->interface_module->timer >= 1000) {

		App->render->Blit(mapaWhite, MapaX, MapaY, SDL_FLIP_NONE, nullptr, 1);
		App->interface_module->NameColor = false;
		if (MapaX < 129 && MapaX > 123 && MapaY < 16 && MapaY > 10) {
			MapaX = 126;
			MapaY = 13;

			if (App->interface_module->timer >= 3000) {

				MapaX += 16;
				MapaY -= 16;
			}
		}
		else {
			MapaX += 15;
			MapaY -= 15;
		}

	}else {
		App->render->Blit(mapaRed, MapaX, MapaY, SDL_FLIP_NONE, nullptr, 1);
		App->interface_module->NameColor = true;
		if (MapaX < 129 && MapaX > 123 && MapaY < 16 && MapaY > 10) {
			MapaX = 126;
			MapaY = 13;

			if (App->interface_module->timer >= 3000) {

				MapaX += 16;
				MapaY -= 16;
			}
		}
		else {
			MapaX += 15;
			MapaY -= 15;
		}
	}

}
