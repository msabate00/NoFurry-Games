#include "ModuleHostage.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level1_SecondFloor_Enemies.h"
#include "ModuleInterface.h"

#include "HostageEntity.h"
#include "Hostage.h"




#include <iostream>


#define SPAWN_MARGIN 1000
#define SPAWN_MARGIN_LEFT 1000

using namespace std;

ModuleHostage::ModuleHostage(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_HOSTAGE; ++i)
		hostages[i] = nullptr;
}

ModuleHostage::~ModuleHostage()
{

}

bool ModuleHostage::Start()
{


	texture = App->textures->Load("Assets/Sprites/SpriteSheet_Enemies.png");
	hostageDestroyedFx = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/EnemiesDie.wav");

	return true;
}

update_status ModuleHostage::Update()
{
	HandleHostageSpawn();

	for (uint i = 0; i < MAX_HOSTAGE; ++i)
	{
		if (hostages[i] != nullptr)
			hostages[i]->Update();
	}

	HandleHostageDespawn(false);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleHostage::PostUpdate()
{
	for (uint i = 0; i < MAX_HOSTAGE; ++i)
	{
		if (hostages[i] != nullptr)
			hostages[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleHostage::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_HOSTAGE; ++i)
	{
		if (hostages[i] != nullptr)
		{
			delete hostages[i];
			hostages[i] = nullptr;
		}

		if (spawnQueue[i].type != HOSTAGE_TYPE::NO_TYPE) {
			spawnQueue[i].type = HOSTAGE_TYPE::NO_TYPE;
		}

	}

	return true;
}


bool ModuleHostage::AddHostage(HOSTAGE_TYPE type, int x, int y, bool gun, int points, bool secondFloor, int id, bool spawnStart)
{
	bool ret = false;

	for (uint i = 0; i < MAX_HOSTAGE; ++i)
	{
		if (spawnQueue[i].type == HOSTAGE_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].gun = gun;
			spawnQueue[i].points = points;
			spawnQueue[i].secondFloor = secondFloor;
			spawnQueue[i].id = id;
			spawnQueue[i].spawnStart = spawnStart;
			spawnQueue[i].spawned = false;
			ret = true;
			break;
		}
	}

	return ret;
}


void ModuleHostage::HandleHostageSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_HOSTAGE; ++i)
	{
		if (spawnQueue[i].type != HOSTAGE_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if(!spawnQueue[i].spawned){
				SpawnHostage(spawnQueue[i]);
				spawnQueue[i].type = HOSTAGE_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
				spawnQueue[i].spawned = true;
			}
			
		}
	}
}

void ModuleHostage::HandleHostageDespawn(bool all)
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_HOSTAGE; ++i)
	{
		if (hostages[i] != nullptr)
		{

			if (all) {
				delete hostages[i];
				hostages[i] = nullptr;
			}

			// Delete the enemy when it has reached the end of the screen
			/*if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}*/
		}
	}
}

void ModuleHostage::HandleHostageDespawnEnemy(HostageEntity* enemy)
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_HOSTAGE; ++i)
	{
		if (hostages[i] != nullptr)
		{

			if (hostages[i]->GetCollider() == enemy->GetCollider()) {

				delete hostages[i];
				hostages[i] = nullptr;
				return;
			}
		}
	}
}



void ModuleHostage::SpawnHostage(const HostageSpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_HOSTAGE; ++i)
	{
		if (hostages[i] == nullptr)
		{
			switch (info.type)
			{			

			case HOSTAGE_TYPE::HOSTAGE:
				hostages[i] = new Hostage(info.x, info.y, info.gun, info.points, info.secondFloor, info.id);
				break;


			}

			hostages[i]->texture = texture;
			hostages[i]->destroyedFx = hostageDestroyedFx;
			break;
		}
	}
}

void ModuleHostage::OnCollision(Collider* c1, Collider* c2)
{
	
	//IGNORAR LA COLISION SI EL JUGADOR ESTA EN OTRA ALTURA
	for (uint i = 0; i < MAX_HOSTAGE; ++i)
	{
		if (hostages[i] != nullptr && hostages[i]->GetCollider() == c1 && hostages[i]->secondFloor != App->player->isSecondFloor)
		{

			return; //sale de las coisiones. ESTO DARA PROBLEMAS YA QUE SI SE TIENE QUE CHOCAR CON UNA PARED PERO UENO
		}
	}



	//PARA EL HOSTAGE
	if (c2 == App->player->collider && c1->type == Collider::Type::HOSTAGE)
	{
		for (uint i = 0; i < MAX_HOSTAGE; ++i)
		{
			if (hostages[i] != nullptr && hostages[i]->GetCollider() == c1 && !((Hostage*)hostages[i])->saved)
			{

				switch (((Hostage*)hostages[i])->id) {
				case 1:
					App->interface_module->hostageTaken[0] = true;
					break;
				case 2:
					App->interface_module->hostageTaken[1] = true;
					break;
				case 3:
					App->interface_module->hostageTaken[2] = true;
					break;
				case 4:
					App->interface_module->hostageTaken[3] = true;
					break;



				}

				((Hostage*)hostages[i])->saved = true;
				if (((Hostage*)hostages[i])->gun) {
					//Mostrar particula bonus gun
					App->player->holdingGun = true;
				}


				return;
				break;
			}
		}
	}
}

HostageEntity* ModuleHostage::getHostage(int i) {
	return hostages[i];
}


