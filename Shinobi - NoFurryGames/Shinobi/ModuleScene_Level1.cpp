#include "ModuleScene_Level1.h"

#include "ModuleScene_Level1_SecondFloor.h"
#include "ModuleScene_Level1_SecondFloor_Enemies.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include <string> 
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Hostage.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene_Level1::ModuleScene_Level1(bool startEnabled) : Module(startEnabled)
{
	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 2046;
	ground.h = 350;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;


}

ModuleScene_Level1::~ModuleScene_Level1()
{

}

// Load assets
bool ModuleScene_Level1::Start()
{
	LOG("Loading background assets");

	App->player->Enable();
	App->enemy->Enable();
	App->collisions->Enable();
	App->scene_Level1_SecondFloor_Enemies->Enable();

	bool ret = true;

	stageTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_solido.png");
	stageBackgroundTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_fondo.png");


	// Colliders ---
	App->collisions->AddCollider({ 0, SCREEN_HEIGHT - 9, 2046, 9 }, Collider::Type::WALL);

	//Cajas
	App->collisions->AddCollider({416, 183, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({703, 183, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({863, 183, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({1437, 183, 64, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({1405, 151, 32, 64}, Collider::Type::WALL);


	//Limites jugador
	App->collisions->AddCollider({ -16, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2046, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);

	//Cambio nivel
	finalLevel = App->collisions->AddCollider({ 2040, 0, 16, SCREEN_HEIGHT }, Collider::Type::CHANGE_LEVEL);
	finalLevel->active = false;

	//secondFloor->active = false;
	

	//Enemies ---
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 320, FLOOR_LEVEL - 64); //Enemigo básico 1
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 365, FLOOR_LEVEL - 64); //Enemigo básico 2


	//Hostage
	App->enemy->AddEnemy(ENEMY_TYPE::HOSTAGE, 530, FLOOR_LEVEL - 26, false, 200);

	
	
	//App->scene_Level1_SecondFloor->Enable();


	SkillIcon = App->textures->Load("Assets/Interface/Color_use/SkillIcon/Rojo.png");
	HostageIcon = App->textures->Load("Assets/Interface/Color_use/Normal_icon/rescate.png");
	LifeIcon = App->textures->Load("Assets/Interface/Color_use/Normal_icon/vida.png");
	save = App->textures->Load("Assets/Interface/Color_use/Yellow/SAVE.png");
	dosPunt = App->textures->Load("Assets/Interface/Color_use/Yellow/dospunto.png");

	start_time = time(nullptr);

	//Musicadddd
	App->audio->PlayMusic("Assets/Audio/Music/Mission 1-1.ogg", 0.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

update_status ModuleScene_Level1::Update()
{

	if (hostage_num <= 0) {
		finalLevel->active = true;
	}

	int elapsed_time = updateTimer(start_time);

	return update_status::UPDATE_CONTINUE;


}

// Update: draw background
update_status ModuleScene_Level1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(stageBackgroundTexture, 0, 0, SDL_FLIP_NONE,&background, 0.35f); // Edificios del fondo
	App->render->Blit(stageTexture, 0, -125, SDL_FLIP_NONE,&ground, 1.0f); // Suelo y eso

	printSkillIcon();
	printHostageIcon(hostage_num);
	printLifeIcon(life_num);



	printNum(getDigits(texture_num), LetraNum);

	printTime(getTimeString(elapsed_time).c_str(), Time);
	printPlayer1();
	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene_Level1::CleanUp()
{

	App->player->Disable();
	App->enemy->Disable();
	App->collisions->Disable();
	App->scene_Level1_SecondFloor_Enemies->Disable();
	return true;
}



void ModuleScene_Level1::printPlayer1() {

	int IconPosition = 360;
	timer += App->deltaTime;
	if (NameColor) {
		for (int i = 0; i < 2; i++)
		{
			std::string filename = "Assets/Interface/Color_use/Player/Azul_" + std::to_string(i) + ".png";
			Player1 = App->textures->Load(filename.c_str());
			App->render->Blit(Player1, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, SDL_FLIP_NONE, nullptr, 0);
			IconPosition -= 16;
		}
		if (timer >= switchTime) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			std::string filename = "Assets/Interface/Color_use/Player/Blanco_" + std::to_string(i) + ".png";
			Player1 = App->textures->Load(filename.c_str());
			App->render->Blit(Player1, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, SDL_FLIP_NONE, nullptr, 0);
			IconPosition -= 16;
		}
		if (timer >= switchTime) {
			NameColor = true;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}

}



void ModuleScene_Level1::printSkillIcon() {
	SDL_Rect rect = { 168,59,17,14 };

	bool sur = App->render->Blit(SkillIcon, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
	if (!sur) {
		//cout << "error" << endl;
	}


}

void ModuleScene_Level1::printHostageIcon(int hostage) {

	//App->render->Blit(SkillIcon, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
	int IconPosition = 340;

	for (int i = 0; i < hostage; i++)
	{
		App->render->Blit(HostageIcon, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 8;
	}

	App->render->Blit(save, SCREEN_WIDTH - 356, SCREEN_HEIGHT - 15, SDL_FLIP_NONE, nullptr, 0);

}
void ModuleScene_Level1::printLifeIcon(int life) {


	int IconPosition = 350;
	for (int i = 0; i < life; i++)
	{
		App->render->Blit(LifeIcon, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 8;
	}

}


void ModuleScene_Level1::printNum(std::vector<int> number, SDL_Texture* LetraNum) {

	int IconPosition = 250;
	for (int i = 0; i < number.size(); i++)
	{
		std::string filename = "Assets/Interface/Color_use/Red/Rojo_Numeros/Rojo_" + std::to_string(number[i]) + ".png";
		LetraNum = App->textures->Load(filename.c_str());

		App->render->Blit(LetraNum, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 16;
	}

}

void ModuleScene_Level1::printTime(std::string time_string, SDL_Texture* Time) {

	int IconPosition = 70;
	int elapsed_time = updateTimer(start_time);
	time_string = getTimeString(elapsed_time);
	std::vector<int> time_vector;
	for (char c : time_string) {
		if (isdigit(c)) {
			time_vector.push_back(c - '0');
		}
	}
	//App->render->Blit(dosPunt, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 150, SDL_FLIP_NONE, nullptr, 0);

	for (int i = 0; i < time_vector.size(); i++)
	{
		std::string filename = "Assets/Interface/Color_use/Yellow/Yellow_Numeros/Yellow_" + std::to_string(time_vector[i]) + ".png";
		SDL_Texture* Time = App->textures->Load(filename.c_str());
		App->render->Blit(Time, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 16;
		if (IconPosition == 54) {
			App->render->Blit(dosPunt, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
			IconPosition -= 16;
		}

		string time_string = getTimeString(elapsed_time);
		//cout << "Remaining time: " << time_string << endl;

		//cout << IconPosition << endl;
	}
	//App->render->Blit(Time, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 150, SDL_FLIP_NONE, nullptr, 0);

}

int ModuleScene_Level1::updateTimer(time_t start_time) {
	time_t current_time = time(nullptr);
	int elapsed_seconds = difftime(current_time, start_time);
	return elapsed_seconds;
}
//Suma tiempo
/*
std::string ModuleRender::getTimeString(int elapsed_time) {
	int minutes = elapsed_time / 60;
	int seconds = elapsed_time % 60;
	std::string time_string = std::to_string(minutes) + ":";

	if (seconds < 10) {
		time_string += "0";
	}
	time_string += std::to_string(seconds);

	return time_string;
}*/

//Resta tiempo , int total_time
std::string ModuleScene_Level1::getTimeString(int elapsed_time) {
	int remaining_seconds = total_time - elapsed_time;
	if (remaining_seconds < 0) {
		remaining_seconds = 0;
	}
	int minutes = remaining_seconds / 60;
	int seconds = remaining_seconds % 60;
	std::string time_string = std::to_string(minutes) + ":";

	if (seconds < 10) {
		time_string += "0";
	}
	time_string += std::to_string(seconds);

	return time_string;
}



std::vector<int> ModuleScene_Level1::getDigits(int number) {
	std::vector<int> digits;

	if (number == 0) {
		digits.push_back(0);
		return digits;
	}

	while (number != 0) {
		int digit = number % 10;
		digits.push_back(digit);
		number /= 10;
	}

	std::reverse(digits.begin(), digits.end());

	return digits;

}