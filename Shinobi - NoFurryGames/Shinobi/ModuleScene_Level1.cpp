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
#include "ModuleFonts.h"
#include "ModuleInterface.h"
#include "ModuleBossEndLevel.h"


#include <string> 
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Hostage.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL_mixer/include/SDL_mixer.h"

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

	App->collisions->Enable();
	App->scene_Level1_SecondFloor_Enemies->Enable();
	App->player->Enable();
	App->enemy->Enable();
	App->hostages->Enable();
	App->scene_Level1_SecondFloor->Enable();
	

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

	//Colliders con cajas para los saltos
	App->collisions->AddCollider({ 416, 186, 35, 15 }, Collider::Type::BOX_HELP); //CAJA 1 - IZQUIERDA
	App->collisions->AddCollider({ 411, 186, 35, 15 }, Collider::Type::BOX_HELP_RIGHT); //CAJA 1 - DERECHA

	App->collisions->AddCollider({ 544, 75, 35, 15 }, Collider::Type::BOX_HELP); //MURO 1 - IZQUIERDA
	App->collisions->AddCollider({ 539, 75, 35, 15 }, Collider::Type::BOX_HELP_RIGHT); //MURO 1 - DERECHA

	App->collisions->AddCollider({ 703, 186, 35, 15 }, Collider::Type::BOX_HELP); //CAJA 2 - IZQUIERDA
	App->collisions->AddCollider({ 698, 186, 35, 15 }, Collider::Type::BOX_HELP_RIGHT); //CAJA 2 - DERECHA

	App->collisions->AddCollider({ 863, 186, 35, 15 }, Collider::Type::BOX_HELP); //CAJA 3 - IZQUIERDA
	App->collisions->AddCollider({ 858, 186, 35, 15 }, Collider::Type::BOX_HELP_RIGHT); //CAJA 3 - DERECHA

	App->collisions->AddCollider({ 1408, 155, 32, 15 }, Collider::Type::BOX_HELP); //CAJA 4 - IZQUIERDA
	App->collisions->AddCollider({ 1469, 186, 35, 15 }, Collider::Type::BOX_HELP); //CAJA 5 - IZQUIERDA



	//Limites jugador
	App->collisions->AddCollider({ -16, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2046, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);

	//Cambio nivel
	finalLevel = App->collisions->AddCollider({ 2040, 0, 16, SCREEN_HEIGHT }, Collider::Type::CHANGE_LEVEL);
	finalLevel->active = false;

	//secondFloor->active = false;
	

	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 250, FLOOR_LEVEL - 64, false ,true); //Enemigo básico 1

	//Enemies ---
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 350, FLOOR_LEVEL - 64, false ,true); //Enemigo básico 1
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 380, FLOOR_LEVEL - 64, false, true); //Enemigo básico 2
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 744, FLOOR_LEVEL - 64); //Enemigo básico 3
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 790, FLOOR_LEVEL - 64); //Enemigo básico 4

	App->enemy->AddEnemy(ENEMY_TYPE::KNIFE, 820, FLOOR_LEVEL - 64); //Enemigo knife
	//App->enemy->AddEnemy(ENEMY_TYPE::KNIFE, 840, FLOOR_LEVEL - 64); //Enemigo knife 2
	//App->enemy->AddEnemy(ENEMY_TYPE::KNIFE, 860, FLOOR_LEVEL - 64); //Enemigo knife 3

	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 605, FLOOR_LEVEL - 64);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 815, FLOOR_LEVEL - 64);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 1020, FLOOR_LEVEL - 64);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 1522, FLOOR_LEVEL - 64);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 1694, FLOOR_LEVEL - 64);


	App->enemy->AddEnemy(ENEMY_TYPE::BROWNSHIELD, 300, FLOOR_LEVEL - 75, false, true); //Enemigo brownshield prueba


	if (App->player->position.x >= 1210) // <----- ESTO NO FUNCIONA, YA QUE ESTA EN EL START
	{
		App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 1059, FLOOR_LEVEL - 64); //Enemigo básico 5
		App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 1113, FLOOR_LEVEL - 64); //Enemigo básico 6
	}

	//Hostage
	if (App->interface_module->hostageTaken[0] == false) {
		
		App->hostages->AddHostage(HOSTAGE_TYPE::HOSTAGE, 530, FLOOR_LEVEL - 26, false, 200, false, 1, true);
	}

	//Musicadddd
	App->audio->PlayMusic("Assets/Audio/Music/Mission 1-1.ogg");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->interface_module->resetTimer();
	return ret;
}

update_status ModuleScene_Level1::Update()
{

	if (App->interface_module->hostage_num <= 0) {
		finalLevel->active = true;

		if (!App->boss_endLevel->IsEnabled()) {
			App->boss_endLevel->position.x = 1920;
			App->boss_endLevel->Enable();
		}
	}


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
update_status ModuleScene_Level1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(stageBackgroundTexture, 0, 0, SDL_FLIP_NONE,&background, 0.35f); // Edificios del fondo
	App->render->Blit(stageTexture, 0, -125, SDL_FLIP_NONE,&ground, 1.0f); // Suelo y eso



	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene_Level1::CleanUp()
{
	App->collisions->Disable();
	App->scene_Level1_SecondFloor->Disable();
	App->scene_Level1_SecondFloor_Enemies->Disable();
	App->player->Disable();
	App->enemy->Disable();
	App->hostages->Disable();

	if (App->boss_endLevel->IsEnabled()) {
		App->boss_endLevel->Disable();
	}

	
	return true;
}
