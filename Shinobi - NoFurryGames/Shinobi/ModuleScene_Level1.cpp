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

#include <string> 
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Hostage.h"
#include "SDL/include/SDL_scancode.h"

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


	//Limites jugador
	App->collisions->AddCollider({ -16, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);
	App->collisions->AddCollider({ 2046, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL);

	//Cambio nivel
	finalLevel = App->collisions->AddCollider({ 2040, 0, 16, SCREEN_HEIGHT }, Collider::Type::CHANGE_LEVEL);
	finalLevel->active = false;

	//secondFloor->active = false;
	

	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 250, FLOOR_LEVEL - 64, false ,true); //Enemigo b�sico 1

	//Enemies ---
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 350, FLOOR_LEVEL - 64, false ,true); //Enemigo b�sico 1
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 380, FLOOR_LEVEL - 64, false, true); //Enemigo b�sico 2
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 744, FLOOR_LEVEL - 64); //Enemigo b�sico 3
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 790, FLOOR_LEVEL - 64); //Enemigo b�sico 4

	App->enemy->AddEnemy(ENEMY_TYPE::KNIFE, 820, FLOOR_LEVEL - 64); //Enemigo knife

	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 605, FLOOR_LEVEL - 64);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 815, FLOOR_LEVEL - 64);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 1020, FLOOR_LEVEL - 64);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 1522, FLOOR_LEVEL - 64);
	App->enemy->AddEnemy(ENEMY_TYPE::GUNSHOOTER, 1694, FLOOR_LEVEL - 64);


	if (App->player->position.x >= 1210) // <----- ESTO NO FUNCIONA, YA QUE ESTA EN EL START
	{
		App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 1059, FLOOR_LEVEL - 64); //Enemigo b�sico 5
		App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 1113, FLOOR_LEVEL - 64); //Enemigo b�sico 6
	}

	//Hostage
	if (App->interface_module->hostageTaken[0] == false) {
		App->enemy->AddEnemy(ENEMY_TYPE::HOSTAGE, 530, FLOOR_LEVEL - 26, false, 200, false, 1, true);
	}

	//Musicadddd
	App->audio->PlayMusic("Assets/Audio/Music/Mission 1-1.ogg", 2.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	
	return ret;
}

update_status ModuleScene_Level1::Update()
{

	if (App->interface_module->hostage_num <= 0) {
		finalLevel->active = true;
	}

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_MainMenu, 20);
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
	
	return true;
}
