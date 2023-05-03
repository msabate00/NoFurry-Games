#include "ModuleScene_Intro.h"

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

ModuleScene_Intro::ModuleScene_Intro(bool startEnabled) : Module(startEnabled)
{
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

ModuleScene_Intro::~ModuleScene_Intro()
{

}

// Load assets
bool ModuleScene_Intro::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	textureBackground = App->textures->Load("Assets/Interface/Menu/intro.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	currentAnimation = &backgroundAnim;

	return ret;
}

update_status ModuleScene_Intro::Update()
{

	

	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Intro2, 20);
	}

	currentAnimation->Update();



	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene_Intro::PostUpdate()
{


	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	App->render->Blit(textureBackground, 0, 0, SDL_FLIP_NONE, &currentAnimation->GetCurrentFrame(), 1);

	return update_status::UPDATE_CONTINUE;
}



