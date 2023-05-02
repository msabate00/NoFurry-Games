#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"

#include "Enemy.h"
#include "Enemy_Basic.h"
#include "Hostage.h"
#include "EnemyBrownShield.h"


#include <iostream>


#define SPAWN_MARGIN 50

using namespace std;

ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	

	texture = App->textures->Load("Assets/Sprites/SpriteSheet_Enemies.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/EnemiesDie.wav");

	return true;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y, bool secondFloor)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].secondFloor = secondFloor;
			ret = true;
			break;
		}
	}

	return ret;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y, bool gun, int points, bool secondFloor)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].gun = gun;
			spawnQueue[i].points = points;
			spawnQueue[i].secondFloor = secondFloor;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
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

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case ENEMY_TYPE::BASIC:
				enemies[i] = new Enemy_Basic(info.x, info.y, info.secondFloor);
				break;

			case ENEMY_TYPE::BROWNSHIELD:
				enemies[i] = new EnemyBrownShield(info.x, info.y, info.secondFloor);
				break;

			case ENEMY_TYPE::HOSTAGE:
				enemies[i] = new Hostage(info.x, info.y, info.gun, info.points, info.secondFloor);
				break;

			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{


	//CUANDO COLISIONA CON EL JUGADOR
	if (c2 == App->player->collider && c1->type == Collider::Type::ENEMY)
	{
		return;
	}


	//IGNORAR LA COLISION SI EL JUGADOR ESTA EN OTRA ALTURA
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && enemies[i]->secondFloor != App->player->isSecondFloor)
		{
			
			return; //sale de las coisiones. ESTO DARA PROBLEMAS YA QUE SI SE TIENE QUE CHOCAR CON UNA PARED PERO UENO
		}
	}



	//PARA EL HOSTAGE
	if (c2 == App->player->collider && c1->type == Collider::Type::HOSTAGE)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && !((Hostage*)enemies[i])->saved)
			{
				//enemies[i]->OnCollision(c2); //Notify the enemy of a collision
				((Hostage*)enemies[i])->saved = true;
				if (((Hostage*)enemies[i])->gun) {
					//Mostrar particula bonus gun
					App->player->holdingGun = true;
				}



				return;
				break;
			}
		}
	}

	//RESTO DE COLISIONES
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			
			//delete enemies[i];
			//enemies[i] = nullptr;
			//destroyed = true;
			break;
		}
	}




	//	delete enemies[i];
	//	cout << "Eliminado" << endl;
	//	enemies[i] = nullptr;
	//	cout << "Hola" << endl;
	//	break;
	//	

	//	/*if (destroyedCountdown <= 0)
	//	{
	//		delete enemies[i];
	//		cout << "Eliminado" << endl;
	//		enemies[i] = nullptr;
	//		cout << "Hola" << endl;
	//		break;
	//	}*/
	//}

	///*delete enemies[i];
	//cout << "Eliminado" << endl;
	//enemies[i] = nullptr;
	//cout << "Hola" << endl;
	//break;*/

	///*if (App->enemy->destroyed == true)
	//{
	//	destroyedCountdown--;

	//	if (destroyedCountdown <= 0)
	//	{
	//		destroyed = false;
	//	}
	//}*/
	//
	//
	///*delete enemies[i];
	//enemies[i] = nullptr;
	//break;*/
}

Enemy* ModuleEnemies::getEnemy(int i) {
	return enemies[i];
}
		
	
