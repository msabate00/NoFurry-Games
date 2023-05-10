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

#include "SDL/include/SDL.h"
#include <string> 
#include <vector>
#include <iostream>
#include <cmath>

ModuleMapa1::ModuleMapa1(bool startEnabled) : Module(startEnabled)
{

	backgroundAnim.loop = false;
	backgroundAnim.speed = 0.01f;
	background = { 200,200, SCREEN_WIDTH, SCREEN_HEIGHT };


}

ModuleMapa1::~ModuleMapa1()
{

}

// Load assets
bool ModuleMapa1::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	textureBackground = App->textures->Load("Assets/Interface/ZoneChange/AlNivel1_Blanco_0.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	currentAnimation = &backgroundAnim;

	return ret;
}

update_status ModuleMapa1::Update()
{



	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Level1, 20);
	}

	currentAnimation->Update();

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
update_status ModuleMapa1::PostUpdate()
{


	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	App->render->Blit(textureBackground, SCREEN_WIDTH - 360, SCREEN_HEIGHT - 170, SDL_FLIP_NONE, &currentAnimation->GetCurrentFrame(), 1);

	return update_status::UPDATE_CONTINUE;
}



