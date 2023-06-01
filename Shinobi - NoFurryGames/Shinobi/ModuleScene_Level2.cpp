#include "ModuleScene_Level2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleInterface.h"
#include "ModulePlayer.h"
#include "ModuleBossEndLevel.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL_mixer/include/SDL_mixer.h"

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
	App->hostages->Enable();

	Mix_HaltMusic();

	bool ret = true;

	stageTexture = App->textures->Load("Assets/Maps/Level2/Nivel2_wide.png");
	stageBackgroundTexture = App->textures->Load("Assets/Maps/Level2/Nivel2_wide_fondo.png");


	// Colliders ---
	App->collisions->AddCollider({ 0, SCREEN_HEIGHT - 9, 2046, 9 }, Collider::Type::WALL);

	//Cajas
	App->collisions->AddCollider({ 288, 183, 32, 32 }, Collider::Type::WALL); //1 caja
	App->collisions->AddCollider({ 290, 186, 35, 15 }, Collider::Type::BOX_HELP); //1 caja
	App->collisions->AddCollider({ 283, 186, 35, 15 }, Collider::Type::BOX_HELP_RIGHT); //1 caja

	App->collisions->AddCollider({ 573, 186, 35, 15 }, Collider::Type::BOX_HELP); //CAJA 2 - IZQUIERDA
	App->collisions->AddCollider({ 608, 186, 35, 15 }, Collider::Type::BOX_HELP_RIGHT); //CAJA 2 - DERECHA

	App->collisions->AddCollider({ 893, 186, 35, 15 }, Collider::Type::BOX_HELP); //MONTON 1 - IZQUIERDA
	App->collisions->AddCollider({ 957, 154, 35, 15 }, Collider::Type::BOX_HELP);
	App->collisions->AddCollider({ 1021, 122, 35, 15 }, Collider::Type::BOX_HELP);
	App->collisions->AddCollider({ 1117, 90 , 35, 15 }, Collider::Type::BOX_HELP);

	App->collisions->AddCollider({ 1376, 186, 35, 15 }, Collider::Type::BOX_HELP_RIGHT); //MONTON 1 - IZQUIERDA
	App->collisions->AddCollider({ 1280, 154, 35, 15 }, Collider::Type::BOX_HELP_RIGHT);
	App->collisions->AddCollider({ 1216, 122, 35, 15 }, Collider::Type::BOX_HELP_RIGHT);
	App->collisions->AddCollider({ 1120, 90 , 35, 15 }, Collider::Type::BOX_HELP_RIGHT);

	App->collisions->AddCollider({ 1565, 186, 35, 15 }, Collider::Type::BOX_HELP);
	App->collisions->AddCollider({ 1602, 122, 35, 15 }, Collider::Type::BOX_HELP_RIGHT);
	App->collisions->AddCollider({ 1664, 154, 35, 15 }, Collider::Type::BOX_HELP_RIGHT);
	App->collisions->AddCollider({ 1696, 186, 35, 15 }, Collider::Type::BOX_HELP_RIGHT);

	App->collisions->AddCollider({ 576, 184, 64, 32 }, Collider::Type::WALL); //2 + 3 cajas

	App->collisions->AddCollider({ 896, 183, 512, 32 }, Collider::Type::WALL); // Fila Cajas Abajo
	App->collisions->AddCollider({ 960, 151, 352, 32 }, Collider::Type::WALL); // Fila Cajas Medio
	App->collisions->AddCollider({ 1024, 119, 224, 32 }, Collider::Type::WALL); // fila cajas Arriba
	App->collisions->AddCollider({ 1120, 87, 32, 32 }, Collider::Type::WALL); // caja 13

	App->collisions->AddCollider({ 1568, 183, 32, 32 }, Collider::Type::WALL); // Columna 17 caja
	App->collisions->AddCollider({ 1600, 119, 32, 96 }, Collider::Type::WALL); // Columna 18 caja + bloque
	App->collisions->AddCollider({ 1632, 151, 32, 64 }, Collider::Type::WALL); // Columna 2 19 caja grande
	App->collisions->AddCollider({ 1664, 151, 32, 64 }, Collider::Type::WALL); // Columna 3 19 caja grande
	App->collisions->AddCollider({ 1696, 183, 32, 32 }, Collider::Type::WALL); // 20 caja
	
	//Limites jugador
	App->collisions->AddCollider({ -16, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2048, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);


	//Cambio nivel
	finalLevel = App->collisions->AddCollider({ 2040, 0, 16, SCREEN_HEIGHT }, Collider::Type::CHANGE_LEVEL);
	finalLevel->active = false;


	//Hostage
	if (App->interface_module->hostageTaken[4] == false) 
		App->hostages->AddHostage(HOSTAGE_TYPE::HOSTAGE, 290, FLOOR_LEVEL - 60, true, 0, false, 5, true);
	if (App->interface_module->hostageTaken[5] == false) 
		App->hostages->AddHostage(HOSTAGE_TYPE::HOSTAGE, 870, FLOOR_LEVEL - 28 , false, 500, false, 6, true);
	if (App->interface_module->hostageTaken[6] == false) 
		App->hostages->AddHostage(HOSTAGE_TYPE::HOSTAGE, 1650, FLOOR_LEVEL - 93, false, 1000, false, 7, true);

	//Enemies
	
	
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 330, FLOOR_LEVEL - 64, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 365, FLOOR_LEVEL - 64, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 390, FLOOR_LEVEL - 64, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 480, FLOOR_LEVEL - 64, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 650, FLOOR_LEVEL - 64, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 1054, FLOOR_LEVEL - 180, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 1090, FLOOR_LEVEL - 180, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 1122, FLOOR_LEVEL - 180, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 1530, FLOOR_LEVEL - 64, false, true);

	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 650, FLOOR_LEVEL - 64, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 690, FLOOR_LEVEL - 64, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 860, FLOOR_LEVEL - 64, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 1215, FLOOR_LEVEL - 180, false, true);

	App->enemy->AddEnemy(ENEMY_TYPE::PURPLESHIELD, 850, FLOOR_LEVEL - 64);

	App->enemy->AddEnemy(ENEMY_TYPE::KNIFE, 1215, FLOOR_LEVEL - 180, false, true);


	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 420, FLOOR_LEVEL - 64, false, true);

	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 500, FLOOR_LEVEL - 64, false, true);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 520, FLOOR_LEVEL - 64, false, true);


	//Musica
	App->audio->PlayMusic("Assets/Audio/Music/Mission 1-2.ogg");

	App->player->isSecondFloor = false;


	App->render->camera.x = 0;
	App->render->camera.y = 0;


	App->interface_module->resetTimer();
	return ret;
}

update_status ModuleScene_Level2::Update()
{
	


	if (App->interface_module->hostage_num <= 0) {
		finalLevel->active = true;

		if (!App->boss_endLevel->IsEnabled()) {
			App->boss_endLevel->position.x = 1920;
			App->boss_endLevel->Enable();
		}

	}

	int elapsed_time = updateTimer(start_time);

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_MainMenu, 20);
		Mix_HaltMusic();
	}

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
	App->hostages->Disable();

	if (App->boss_endLevel->IsEnabled()) {
		App->boss_endLevel->Disable();
	}

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



