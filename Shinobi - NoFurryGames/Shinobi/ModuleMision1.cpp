#include "ModuleMision1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleMapa1.h"
#include "ModuleScene_Level1.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"

#include "SDL/include/SDL.h"
#include <string> 
#include <vector>
#include <iostream>
#include <cmath>

ModuleMision1::ModuleMision1(bool startEnabled) : Module(startEnabled)
{

}

ModuleMision1::~ModuleMision1()
{

}

// Load assets
bool ModuleMision1::Start()
{

	bool ret = true;
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	Mision_FinishedFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Mission/Finished.wav");
	typewriterFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Mission/typewriter.wav");
	ONE_FX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Mission/1.wav");
	Mision_soundFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Mission/Mission.wav");

	SDL_SetRenderDrawColor(App->render->renderer, 128, 128, 128, 255);
	SDL_RenderClear(App->render->renderer);

	dosComa = App->textures->Load("Assets/Interface/Color_use/White/Icon/DosComa.png");
	currentAnimation = &backgroundAnim;
	return ret;
}

update_status ModuleMision1::Update()
{
	mis1Jumptimer += App->deltaTime;
	
	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || mis1Jumptimer >= 3000) {
		mis1Jumptimer = 999999;
		App->fade->FadeToBlack(this, (Module*)App->mapa1, 20);
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
update_status ModuleMision1::PostUpdate()
{
	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	printext();	
	printMision();
		return update_status::UPDATE_CONTINUE;
}

void ModuleMision1::printext() {
	
	int IconPosition = 360;
	App->interface_module->timer += App->deltaTime;

	Uint32 current_time = SDL_GetTicks();

	if (current_time - last_time > 50 && str_cache.length() < len) {
	
		
		str_cache += str[str_cache.length()];


		last_time = current_time;
	}
	//App->audio->PlayFx(typewriterFX);
	App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 110, App->scoreFontWhite, str_cache.c_str());
	
}


void ModuleMision1::printMision() {
	int IconPosition = 260;
	App->interface_module->timer += App->deltaTime;
	while (EfectoSonido == true)
	{
		App->audio->PlayFx(Mision_soundFX);
		
		EfectoSonido = false;
		App->audio->PlayFx(ONE_FX);
	}

	if (App->interface_module->NameColor) {
		for (int i = 0; i < 2; i++)
		{
			App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 170, App->scoreFontRed, "mission 1");
		}
		if (App->interface_module->timer >= App->interface_module->switchTime) {
			App->interface_module->NameColor = false;
			App->interface_module->timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 170, App->scoreFontWhite, "mission 1");
		}
		if (App->interface_module->timer >= App->interface_module->switchTime) {
			App->interface_module->NameColor = true;
			App->interface_module->timer = 0.0f; // Reset Tiempo Contador
		}
	}

}