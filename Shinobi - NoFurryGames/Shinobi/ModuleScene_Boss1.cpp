#include "ModuleScene_Intro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleScene_Boss1.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBoss.h"
#include "ModuleInterface.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include <string> 
#include <vector>
#include <iostream>
#include <cmath>

ModuleScene_Boss1::ModuleScene_Boss1(bool startEnabled) : Module(startEnabled)
{
	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 506;
	ground.h = 300;

	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 726;
	background.h = 350;


}

ModuleScene_Boss1::~ModuleScene_Boss1()
{

}

// Load assets
bool ModuleScene_Boss1::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	stageTexture = App->textures->Load("Assets/Maps/Boss/NivelBoss_wide_suelo.png");
	stageBackgroundTexture = App->textures->Load("Assets/Maps/Boss/NivelBoss_wide_fondo.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->collisions->Enable();
	App->player->Enable();
	App->boss->Enable();

	//Suelo
	App->collisions->AddCollider({ 0, SCREEN_HEIGHT - 9, 506, 50 }, Collider::Type::WALL);

	//Paredes
	App->collisions->AddCollider({ 10, 0, 30, SCREEN_HEIGHT }, Collider::Type::WALL);
	App->collisions->AddCollider({ 476, 0, 30, SCREEN_HEIGHT }, Collider::Type::WALL);

	//Musica
	App->audio->PlayMusic("Assets/Audio/Music/Mission 1-3 (Boss).ogg");

	App->interface_module->resetTimer();

	return ret;
}

update_status ModuleScene_Boss1::Update()
{
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_MainMenu, 20);
		Mix_HaltMusic();
	}
	if (App->input->keys[SDL_SCANCODE_F9] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Level1, 20);
		Mix_HaltMusic();
	}

	if (App->input->keys[SDL_SCANCODE_F10] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Level2, 20);
		Mix_HaltMusic();
	}

	if (App->input->keys[SDL_SCANCODE_F11] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Boss1, 20);
		Mix_HaltMusic();
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene_Boss1::PostUpdate()
{


	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	App->render->Blit(stageBackgroundTexture, 0, -100, SDL_FLIP_NONE, &background, 0.35f); // Edificios del fondo
	App->render->Blit(stageTexture, 0, -56, SDL_FLIP_NONE, &ground, 1.0f); // Suelo y eso


	


	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene_Boss1::CleanUp()
{
	App->collisions->Disable();
	App->player->Disable();
	App->boss->Disable();
	//App->audio->ReleaseAudio();

	return true;
}



