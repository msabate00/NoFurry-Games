#include "ModuleScene_Level2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"

#include <string> 
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Hostage.h"


ModuleScene_Level2::ModuleScene_Level2(bool startEnabled) : Module(startEnabled)
{

	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 2048;
	ground.h = 372;

	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 2046;
	background.h = 350;


}

ModuleScene_Level2::~ModuleScene_Level2()
{

}

// Load assets
bool ModuleScene_Level2::Start()
{
	LOG("Loading background assets");

	App->collisions->Enable();
	
	App->player->Enable();
	App->enemy->Enable();
	
	bool ret = true;

	stageTexture = App->textures->Load("Assets/Maps/Level2/Nivel2_wide.png");
	stageBackgroundTexture = App->textures->Load("Assets/Maps/Level2/Nivel2_wide_fondo.png");


	// Colliders ---
	App->collisions->AddCollider({ 0, SCREEN_HEIGHT - 9, 2046, 9 }, Collider::Type::WALL);

	//Cajas
	App->collisions->AddCollider({ 288, 183, 32, 32 }, Collider::Type::WALL); //1 caja
	App->collisions->AddCollider({ 576, 183, 64, 32 }, Collider::Type::WALL); //2 + 3 cajas
	App->collisions->AddCollider({ 896, 183, 64, 32 }, Collider::Type::WALL); // 4 + 5 cajas
	App->collisions->AddCollider({ 960, 151, 353, 64 }, Collider::Type::WALL); // Bloque grande
	App->collisions->AddCollider({ 1024, 119, 224, 32 }, Collider::Type::WALL); // fila cajas 6 - 12
	App->collisions->AddCollider({ 1120, 87, 32, 32 }, Collider::Type::WALL); // caja 13
	App->collisions->AddCollider({ 1313, 183, 96, 32 }, Collider::Type::WALL); // 14 + 15 + 16 cajas
	App->collisions->AddCollider({ 1568, 183, 32, 32 }, Collider::Type::WALL); // 17 caja
	App->collisions->AddCollider({ 1600, 119, 32, 32 }, Collider::Type::WALL); // 18 caja
	App->collisions->AddCollider({ 1600, 151, 96, 64 }, Collider::Type::WALL); // 19 caja grande
	App->collisions->AddCollider({ 1696, 183, 32, 32 }, Collider::Type::WALL); // 20 caja
	
	//Limites jugador
	App->collisions->AddCollider({ -16, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2048, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);

	//Hostage
	App->enemy->AddEnemy(ENEMY_TYPE::HOSTAGE, 290, FLOOR_LEVEL - 60, false, 200, false, 5, true);
	App->enemy->AddEnemy(ENEMY_TYPE::HOSTAGE, 870, FLOOR_LEVEL - 28, false, 200, false, 6, true);
	App->enemy->AddEnemy(ENEMY_TYPE::HOSTAGE, 1650, FLOOR_LEVEL - 93, false, 200, false, 7, true);


	//Musica
	App->audio->PlayMusic("Assets/Audio/Music/Mission 1-2.ogg", 2.0f);


	App->render->camera.x = 0;
	App->render->camera.y = 0;
	return ret;
}

update_status ModuleScene_Level2::Update()
{

	if (hostage_num <= 0) {
		finalLevel->active = true;
	}

	int elapsed_time = updateTimer(start_time);

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_MainMenu, 20);
	}



	return update_status::UPDATE_CONTINUE;


}

// Update: draw background
update_status ModuleScene_Level2::PostUpdate()
{

	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	App->render->Blit(stageBackgroundTexture, 0, -100, SDL_FLIP_NONE, &background, 0.35f); // Edificios del fondo
	App->render->Blit(stageTexture, 0, -141, SDL_FLIP_NONE, &ground, 1.0f); // Suelo y eso

	
	printSkillIcon();
	printHostageIcon(hostage_num);
	printLifeIcon(life_num);



	printNum(getDigits(texture_num), LetraNum);

	printTime(getTimeString(elapsed_time).c_str(), Time);
	printPlayer1();
	return update_status::UPDATE_CONTINUE;


}


bool ModuleScene_Level2::CleanUp()
{
	App->collisions->Disable();
	App->player->Disable();
	App->enemy->Disable();
	return true;
}

void ModuleScene_Level2::printSkillIcon()
{
}

void ModuleScene_Level2::printHostageIcon(int)
{
}

void ModuleScene_Level2::printLifeIcon(int)
{
}

void ModuleScene_Level2::printNum(std::vector<int> num, SDL_Texture* texture)
{
}

void ModuleScene_Level2::printTime(std::string time, SDL_Texture* texture)
{
}

void ModuleScene_Level2::printPlayer1()
{
}

std::vector<int> ModuleScene_Level2::getDigits(int number)
{
	return std::vector<int>();
}

int ModuleScene_Level2::updateTimer(time_t start_time)
{
	return 0;
}

std::string ModuleScene_Level2::getTimeString(int elapsed_seconds)
{
	return std::string();
}



