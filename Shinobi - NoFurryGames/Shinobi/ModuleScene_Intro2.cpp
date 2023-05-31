#include "ModuleScene_Intro2.h"

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
#include "SDL_mixer/include/SDL_mixer.h"
#include <string> 
#include <vector>
#include <iostream>
#include <cmath>

ModuleScene_Intro2::ModuleScene_Intro2(bool startEnabled) : Module(startEnabled)
{
	backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro


	backgroundAnim.loop = false;
	backgroundAnim.speed = 0.01f;
	background = { 200,200, SCREEN_WIDTH, SCREEN_HEIGHT };


}

ModuleScene_Intro2::~ModuleScene_Intro2()
{

}

// Load assets
bool ModuleScene_Intro2::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	textureBackground = App->textures->Load("Assets/Interface/Menu/intro2.png");
	Mix_HaltMusic();

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	currentAnimation = &backgroundAnim;

	return ret;
}

update_status ModuleScene_Intro2::Update()
{
	GamePad& pad = App->input->pads[0];
	
	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || pad.a_down || pad.b_down) {
		App->fade->FadeToBlack(this, (Module*)App->scene_MainMenu, 20);
		Mix_HaltMusic();
	}

	currentAnimation->Update();


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
update_status ModuleScene_Intro2::PostUpdate()
{


	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	App->render->Blit(textureBackground, 0, 0, SDL_FLIP_NONE, &currentAnimation->GetCurrentFrame(), 1);

	return update_status::UPDATE_CONTINUE;
}



