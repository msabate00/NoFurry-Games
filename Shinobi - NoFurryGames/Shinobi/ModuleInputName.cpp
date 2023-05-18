#include "ModuleInputName.h"

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


ModuleInputName::ModuleInputName(bool startEnabled) : Module(startEnabled)
{

}

ModuleInputName::~ModuleInputName()
{

}




// Load assets
bool ModuleInputName::Start()
{

	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	SDL_SetRenderDrawColor(App->render->renderer, 128, 128, 128, 255);
	SDL_RenderClear(App->render->renderer);

	iconType[0] = App->textures->Load("Assets/Interface/Color_use/SkillIcon/Rojo.png");
	iconType[1] = App->textures->Load("Assets/Interface/Color_use/SkillIcon/Verde.png");
	iconType[2] = App->textures->Load("Assets/Interface/Color_use/SkillIcon/Azul.png");

	ranking = App->textures->Load("Assets/Interface/Color_use/SkillIcon/rank.png");
	currentAnimation = &backgroundAnim;




	return ret;
}

update_status ModuleInputName::Update()
{


	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN) {

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
update_status ModuleInputName::PostUpdate()
{
	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	prinIcon();
	printTitle();
	//printrRanking();
	return update_status::UPDATE_CONTINUE;
}

void ModuleInputName::prinIcon() {

	int IconPosition1 = 20;
	int IconPosition2 = 20;
	timerIconChange += App->deltaTime;


	for (int i = 0; i < 9; i++) {
		for (int j = i - 1; j <= i + 1; j++) {
			int index = (j + i + 1) % 3;

			App->render->Blit(iconType[index], SCREEN_WIDTH - 370, SCREEN_HEIGHT - IconPosition1, SDL_FLIP_NONE, nullptr, 1);
		}
		IconPosition1 += 25;

		if (timerIconChange >= 1000) {
			SDL_Texture* temp = iconType[0];
			iconType[0] = iconType[1];
			iconType[1] = iconType[2];
			iconType[2] = temp;
			timerIconChange = 0;
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = i - 1; j <= i + 1; j++) {
			int index = (j + i + 1) % 3;

			App->render->Blit(iconType[index], SCREEN_WIDTH - 30, SCREEN_HEIGHT - IconPosition2, SDL_FLIP_NONE, nullptr, 1);
		}
		IconPosition2 += 25;

		if (timerIconChange >= 1000) {
			SDL_Texture* temp = iconType[0];
			iconType[0] = iconType[1];
			iconType[1] = iconType[2];
			iconType[2] = temp;
			timerIconChange = 0;
		}
	}

}

void ModuleInputName::printTitle() {
	int IconPositionY = 220;
	int IconPositionY2 = 200;
	App->interface_module->timer += App->deltaTime;

	if (App->interface_module->NameColor) {
		for (int i = 0; i < 2; i++)
		{
			//App->fonts->BlitText(SCREEN_WIDTH - 350, SCREEN_HEIGHT - IconPositionY, App->scoreFontRed, "greatest");
			App->render->Blit(App->interface_module->LetraNomRed, SCREEN_WIDTH - 245, SCREEN_HEIGHT - IconPositionY, SDL_FLIP_NONE, nullptr, 0);

			App->fonts->BlitText(SCREEN_WIDTH - 318, SCREEN_HEIGHT - IconPositionY2, App->scoreFontRed, "greatest ranking");
		}
		if (App->interface_module->timer >= App->interface_module->switchTime) {
			App->interface_module->NameColor = false;
			App->interface_module->timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			//App->fonts->BlitText(SCREEN_WIDTH - 350, SCREEN_HEIGHT - IconPositionY, App->scoreFontWhite, "greatest");
			App->render->Blit(App->interface_module->LetraNomWhite, SCREEN_WIDTH - 245, SCREEN_HEIGHT - IconPositionY, SDL_FLIP_NONE, nullptr, 0);
			App->fonts->BlitText(SCREEN_WIDTH - 318, SCREEN_HEIGHT - IconPositionY2, App->scoreFontWhite, "greatest ranking");

		}
		if (App->interface_module->timer >= App->interface_module->switchTime) {
			App->interface_module->NameColor = true;
			App->interface_module->timer = 0.0f; // Reset Tiempo Contador
		}
	}

}


