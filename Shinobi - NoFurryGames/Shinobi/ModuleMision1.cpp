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
#include "SDL_mixer/include/SDL_mixer.h"
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


	Mission1FX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Mission/MISSION-1(intro).wav");
	App->audio->PlayFx(Mission1FX);

	SDL_SetRenderDrawColor(App->render->renderer, 128, 128, 128, 255);
	SDL_RenderClear(App->render->renderer);

	mis1Jumptimer = 0;
	dosComa = App->textures->Load("Assets/Interface/Color_use/White/Icon/DosComa.png");
	currentAnimation = &backgroundAnim;
	timerText = 0;
	str_cache = "";
	return ret;
}

update_status ModuleMision1::Update()
{

	GamePad& pad = App->input->pads[0];
	mis1Jumptimer += App->deltaTime;
	
	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || pad.a_down || pad.b_down || mis1Jumptimer >= 3000) {
		mis1Jumptimer = 999999;
		App->fade->FadeToBlack(this, (Module*)App->mapa1, 20);
	}

	currentAnimation->Update();


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

//void ModuleMision1::printext() {
//	
//	int IconPosition = 360;
//
//	Uint32 current_time = 0;
//	current_time = SDL_GetTicks();
//	
//	cout << SDL_GetTicks() << endl;
//	if (current_time - last_time > 50 && str_cache.length() < len) {
//	
//		
//		str_cache += str[str_cache.length()];
//
//
//		last_time = current_time;
//	}
//	
//	App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 110, App->scoreFontWhite16px, str_cache.c_str());
//	
//}
void ModuleMision1::printext() {
	int IconPosition = 360;
	timerText += App->deltaTime;
	if (timerText > 80 && str_cache.length() < len) {
		str_cache += str[str_cache.length()];
		timerText = 0;
	}
	App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 110, App->scoreFontWhite16px, str_cache.c_str());
}



void ModuleMision1::printMision() {
	int IconPosition = 260;
	App->interface_module->timer += App->deltaTime;
	
	if (App->interface_module->NameColor) {
		for (int i = 0; i < 2; i++)
		{
			App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 170, App->scoreFontRed16px, "mission 1");
		}
		if (App->interface_module->timer >= App->interface_module->switchTime) {
			App->interface_module->NameColor = false;
			App->interface_module->timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 170, App->scoreFontWhite16px, "mission 1");
		}
		if (App->interface_module->timer >= App->interface_module->switchTime) {
			App->interface_module->NameColor = true;
			App->interface_module->timer = 0.0f; // Reset Tiempo Contador
		}
	}

}


