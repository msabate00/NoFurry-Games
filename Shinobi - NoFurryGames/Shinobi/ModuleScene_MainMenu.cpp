#include "ModuleScene_MainMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Boss1.h"
#include "ModuleInterface.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"
#include "ModuleInterface.h"
#include "Module.h"

#include "SDL/include/SDL.h"
#include <string> 
#include <vector>
#include <iostream>
#include <cmath>

ModuleScene_MainMenu::ModuleScene_MainMenu(bool startEnabled) : Module(startEnabled)
{
	eyesAnimation.PushBack({ 0, 448, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	eyesAnimation.PushBack({ 0, 896, SCREEN_WIDTH, SCREEN_HEIGHT }); //izquierda
	eyesAnimation.PushBack({ 0, 448, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	eyesAnimation.PushBack({ 0, 672, SCREEN_WIDTH, SCREEN_HEIGHT }); //derecha
	eyesAnimation.PushBack({ 0, 448, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	eyesAnimation.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Brilli
	eyesAnimation.PushBack({ 0, 224, SCREEN_WIDTH, SCREEN_HEIGHT }); //Brilli2
	
	eyesAnimation.loop = true;
	eyesAnimation.speed = 0.04f;
	background = { 200,200, SCREEN_WIDTH, SCREEN_HEIGHT };


}

ModuleScene_MainMenu::~ModuleScene_MainMenu()
{

}

// Load assets
bool ModuleScene_MainMenu::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	textureBackground = App->textures->Load("Assets/Interface/Menu/background.png");

	
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	

	//Musicadddd
	//App->audio->PlayMusic("Assets/Audio/Music/Mission 1-1.ogg", 1.0f);


	currentAnimation = &eyesAnimation;


	for (int i = 0; i < 7; i++) {
		App->interface_module->hostageTaken[i] = false;
	}
	
	

	


	return ret;
}

update_status ModuleScene_MainMenu::Update()
{

	App->life_num = 3;


	
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && App->interface_module->coinNum > 0)
	{
		App->fade->FadeToBlack(this, (Module*)App->mision1, 2);

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
	
	currentAnimation->Update();
	


	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene_MainMenu::PostUpdate()
{


	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	App->render->Blit(textureBackground, 0, 0, SDL_FLIP_NONE, &currentAnimation->GetCurrentFrame(), 1);

	return update_status::UPDATE_CONTINUE;
}

