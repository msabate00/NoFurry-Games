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
#include "ModuleScene_Level1.h"

#include <iostream>
using namespace std;


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene_Level1_SecondFloor_Enemies::ModuleScene_Level1_SecondFloor_Enemies(bool startEnabled) : Module(startEnabled)
{
	// ground
	up_level_fence1Rect.x = 96;
	up_level_fence1Rect.y = 204;
	up_level_fence1Rect.w = 447;
	up_level_fence1Rect.h = 28;

	up_level_fence2Rect.x = 576;
	up_level_fence2Rect.y = 204;
	up_level_fence2Rect.w = 509;
	up_level_fence2Rect.h = 28;

	up_level_fence3Rect.x = 1293;
	up_level_fence3Rect.y = 204;
	up_level_fence3Rect.w = 655;
	up_level_fence3Rect.h = 28;

}

ModuleScene_Level1_SecondFloor_Enemies::~ModuleScene_Level1_SecondFloor_Enemies()
{

}

// Load assets
bool ModuleScene_Level1_SecondFloor_Enemies::Start()
{
	LOG("Loading background assets");
	up_level_fenceTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_solido.png");


	//Hostage
	if (App->scene_Level1->hostageTaken[1] == false)
		App->enemy->AddEnemy(ENEMY_TYPE::HOSTAGE, 700, FLOOR_LEVEL - 141, true, 0, true, 2);

	if (App->scene_Level1->hostageTaken[2] == false)
		App->enemy->AddEnemy(ENEMY_TYPE::HOSTAGE, 1000, FLOOR_LEVEL - 141, false, 500, true, 3);

	if (App->scene_Level1->hostageTaken[3] == false)
		App->enemy->AddEnemy(ENEMY_TYPE::HOSTAGE, 1550, FLOOR_LEVEL - 141, false, 1000, true, 4);

	//Enemies
	App->enemy->AddEnemy(ENEMY_TYPE::PURPLESHIELD, 950, FLOOR_LEVEL - 177, true);
	App->enemy->AddEnemy(ENEMY_TYPE::PURPLESHIELD, 1500, FLOOR_LEVEL - 177, true);

	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 850, FLOOR_LEVEL - 177, true); //Enemigo básico 1


	bool ret = true;


	return ret;
}

update_status ModuleScene_Level1_SecondFloor_Enemies::Update()
{
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene_Level1_SecondFloor_Enemies::PostUpdate()
{
	App->render->Blit(up_level_fenceTexture, 96, 79, SDL_FLIP_NONE, &up_level_fence1Rect, 1.0f); // Suelo y eso
	App->render->Blit(up_level_fenceTexture, 576, 79, SDL_FLIP_NONE, &up_level_fence2Rect, 1.0f); // Suelo y eso
	App->render->Blit(up_level_fenceTexture, 1293, 79, SDL_FLIP_NONE, &up_level_fence3Rect, 1.0f); // Suelo y eso

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene_Level1_SecondFloor_Enemies::CleanUp()
{
	return true;
}
