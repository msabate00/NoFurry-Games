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
#include "ModuleInputName.h"
#include "ModuleScene_MainMenu.h"


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
	leaderboard[0].score = 103010;
	leaderboard[1].score = 96050;
	leaderboard[2].score = 79060;
	leaderboard[3].score = 70400;
	leaderboard[4].score = 68020;
	leaderboard[5].score = 52039;
	leaderboard[6].score = 44560;
	leaderboard[7].score = 37050;
	leaderboard[8].score = 20190;
	leaderboard[9].score = 12340;

	//Coin
	leaderboard[0].coin = 3;
	leaderboard[1].coin = 2;
	leaderboard[2].coin = 4;
	leaderboard[3].coin = 1;
	leaderboard[4].coin = 9;
	leaderboard[5].coin = 1;
	leaderboard[6].coin = 7;
	leaderboard[7].coin = 5;
	leaderboard[8].coin = 5;
	leaderboard[9].coin = 4;

	//Name
	leaderboard[0].name = "lin";
	leaderboard[1].name = "kh2";
	leaderboard[2].name = "hdl";
	leaderboard[3].name = "tpm";
	leaderboard[4].name = "edu";
	leaderboard[5].name = "miku";
	leaderboard[6].name = "upc";
	leaderboard[7].name = "eli";
	leaderboard[8].name = "furry";
	leaderboard[9].name = "ram";

	insert_rank(App->interface_module->texture_num, App->interface_module->coinNum, App->inputname->myName);
	return ret;
}

update_status ModuleRanking::Update()
{
	GamePad& pad = App->input->pads[0];

	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || pad.a_down || pad.b_down) {
		App->interface_module->coinNum = 0;
		App->fade->FadeToBlack(this, (Module*)App->scene_MainMenu, 20);
		App->audio->PlayMusic("Assets/Audio/Music/SinMusica.ogg");
	}
	currentAnimation->Update();
	if (App->input->keys[SDL_SCANCODE_F9] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Level1, 20);
		App->audio->PlayMusic("Assets/Audio/Music/SinMusica.ogg");
	}

	if (App->input->keys[SDL_SCANCODE_F10] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Level2, 20);
		App->audio->PlayMusic("Assets/Audio/Music/SinMusica.ogg");
	}

	if (App->input->keys[SDL_SCANCODE_F11] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Boss1, 20);
		App->audio->PlayMusic("Assets/Audio/Music/SinMusica.ogg");
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
			
			App->fonts->BlitText(SCREEN_WIDTH - 318, SCREEN_HEIGHT - IconPositionY2, App->scoreFontRed16px, "greatest ranking");
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
			App->fonts->BlitText(SCREEN_WIDTH - 318, SCREEN_HEIGHT - IconPositionY2, App->scoreFontWhite16px, "greatest ranking");
			
		}
		if (App->interface_module->timer >= App->interface_module->switchTime) {
			App->interface_module->NameColor = true;
			App->interface_module->timer = 0.0f; // Reset Tiempo Contador
		}
	}

}


void ModuleRanking::printrRanking() {
	int IconPositionY;
	int IconPositionrank = 160;

	//cout << "ranking" << insert_index+1 << endl;
		App->render->Blit(ranking, SCREEN_WIDTH - 325, SCREEN_HEIGHT - 180, SDL_FLIP_NONE, nullptr, 0);

		for (int i = 0; i < 10; i++)
		{
			if (leaderboard[i].score >= 100000) {
				IconPositionY = 255;
			}
			else {
				IconPositionY = 239;
			}
			if (i == insert_index) {
				App->fonts->BlitText(SCREEN_WIDTH - 328, SCREEN_HEIGHT - IconPositionrank, App->scoreFontRed16px, leaderboard[i].rank.c_str());
				App->fonts->BlitText(SCREEN_WIDTH - IconPositionY, SCREEN_HEIGHT - IconPositionrank, App->scoreFontRed16px, std::to_string(leaderboard[i].score).c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 140, SCREEN_HEIGHT - IconPositionrank, App->scoreFontRed16px, std::to_string(leaderboard[i].coin).c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - IconPositionrank, App->scoreFontRed16px, leaderboard[i].name.c_str());
			}
			else {
				App->fonts->BlitText(SCREEN_WIDTH - 328, SCREEN_HEIGHT - IconPositionrank, App->scoreFontWhite16px, leaderboard[i].rank.c_str());
				App->fonts->BlitText(SCREEN_WIDTH - IconPositionY, SCREEN_HEIGHT - IconPositionrank, App->scoreFontWhite16px, std::to_string(leaderboard[i].score).c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 140, SCREEN_HEIGHT - IconPositionrank, App->scoreFontWhite16px, std::to_string(leaderboard[i].coin).c_str());
				App->fonts->BlitText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - IconPositionrank, App->scoreFontWhite16px, leaderboard[i].name.c_str());
			}

			IconPositionrank -= 20;
		}


}


std::string getRankSuffix(int rank) {
	if (rank >= 11 && rank <= 13)
		return "th";

	int lastDigit = rank % 10;
	switch (lastDigit) {
	case 1:
		return "st";
	case 2:
		return "nd";
	case 3:
		return "rd";
	default:
		return "th";
	}
}


void ModuleRanking::insert_rank(int new_score, int new_coin, const std::string& new_name) {


	for (int i = 0; i < 10; i++) {
		if (new_score > leaderboard[i].score) {
			insert_index = i;
			break;
		}
	}

	if (insert_index != -1) {

		for (int i = 9; i > insert_index; i--) {
			leaderboard[i] = leaderboard[i - 1];
			int rank = std::stoi(leaderboard[i].rank);
			leaderboard[i].rank = std::to_string(rank + 1) + getRankSuffix(rank + 1);
		}

		leaderboard[insert_index].score = new_score;
		leaderboard[insert_index].coin = new_coin;
		leaderboard[insert_index].name = new_name;
		leaderboard[insert_index].rank = std::to_string(std::stoi(leaderboard[insert_index + 1].rank) - 1) + getRankSuffix(std::stoi(leaderboard[insert_index + 1].rank) - 1);
	}

	
}