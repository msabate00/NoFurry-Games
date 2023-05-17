#include "ModuleRanking.h"

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


ModuleRanking::ModuleRanking(bool startEnabled) : Module(startEnabled)
{

}

ModuleRanking::~ModuleRanking()
{

}




// Load assets
bool ModuleRanking::Start()
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


	//Rank
	leaderboard[0].rank = "1st";
	leaderboard[1].rank = "2nd";
	leaderboard[2].rank = "3rd";
	leaderboard[3].rank = "4th";
	leaderboard[4].rank = "5th";
	leaderboard[5].rank = "6th";
	leaderboard[6].rank = "7th";
	leaderboard[7].rank = "8th";
	leaderboard[8].rank = "9th";
	leaderboard[9].rank = "10th";

	//Score
	leaderboard[0].score = 100000;
	leaderboard[1].score = 90000;
	leaderboard[2].score = 80000;
	leaderboard[3].score = 70000;
	leaderboard[4].score = 60000;
	leaderboard[5].score = 50000;
	leaderboard[6].score = 40000;
	leaderboard[7].score = 30000;
	leaderboard[8].score = 20000;
	leaderboard[9].score = 10000;

	//Coin
	leaderboard[0].coin = 05;
	leaderboard[1].coin = 05;
	leaderboard[2].coin = 05;
	leaderboard[3].coin = 05;
	leaderboard[4].coin = 05;
	leaderboard[5].coin = 05;
	leaderboard[6].coin = 05;
	leaderboard[7].coin = 05;
	leaderboard[8].coin = 05;
	leaderboard[9].coin = 05;

	//Name
	leaderboard[0].name = "aaa";
	leaderboard[1].name = "bbb";
	leaderboard[2].name = "ccc";
	leaderboard[3].name = "ddd";
	leaderboard[4].name = "eee";
	leaderboard[5].name = "fff";
	leaderboard[6].name = "ggg";
	leaderboard[7].name = "hhh";
	leaderboard[8].name = "iii";
	leaderboard[9].name = "jjj";

	return ret;
}

update_status ModuleRanking::Update()
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
update_status ModuleRanking::PostUpdate()
{
	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	prinIcon();
	printTitle();
	printrRanking();
	return update_status::UPDATE_CONTINUE;
}

void ModuleRanking::prinIcon() {

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

void ModuleRanking::printTitle() {
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


void ModuleRanking::printrRanking() {
	int IconPositionY = 180;
	int IconPositionrank = 160;
		App->render->Blit(ranking, SCREEN_WIDTH - 325, SCREEN_HEIGHT - IconPositionY, SDL_FLIP_NONE, nullptr, 0);

		for (int i = 0; i < 10; i++)
		{
			if (i == 0) {
				App->fonts->BlitText(SCREEN_WIDTH - 328, SCREEN_HEIGHT - IconPositionrank, App->scoreFontRed, leaderboard[i].rank.c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 255, SCREEN_HEIGHT - IconPositionrank, App->scoreFontRed, std::to_string(leaderboard[i].score).c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 140, SCREEN_HEIGHT - IconPositionrank, App->scoreFontRed, std::to_string(leaderboard[i].coin).c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - IconPositionrank, App->scoreFontRed, leaderboard[i].name.c_str());
			}
			else {
				App->fonts->BlitText(SCREEN_WIDTH - 328, SCREEN_HEIGHT - IconPositionrank, App->scoreFontWhite, leaderboard[i].rank.c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 239, SCREEN_HEIGHT - IconPositionrank, App->scoreFontWhite, std::to_string(leaderboard[i].score).c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 140, SCREEN_HEIGHT - IconPositionrank, App->scoreFontWhite, std::to_string(leaderboard[i].coin).c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - IconPositionrank, App->scoreFontWhite, leaderboard[i].name.c_str());
			}

			IconPositionrank -= 20;
		}


}

