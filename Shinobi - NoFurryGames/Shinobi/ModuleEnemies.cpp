#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level1_SecondFloor_Enemies.h"
#include "ModuleInterface.h"

#include "Enemy.h"
#include "Enemy_Basic.h"
#include "Hostage.h"
#include "EnemyBrownShield.h"
#include "EnemyPurpleShield.h"

#include "EnemyKnife.h"
#include "EnemyGun.h"


#include <iostream>


#define SPAWN_MARGIN 1000
#define SPAWN_MARGIN_LEFT 1000

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

	HandleEnemiesDespawn(false);

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

		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE) {
			spawnQueue[i].type = ENEMY_TYPE::NO_TYPE;
		}

	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y, bool secondFloor, bool spawnStart)
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
			spawnQueue[i].spawnStart = spawnStart;
			ret = true;
			break;
		}
	}

	return ret;
}



bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y, bool gun, int points, bool secondFloor, int id, bool spawnStart)
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
			spawnQueue[i].id = id;
			spawnQueue[i].spawnStart = spawnStart;
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
			//// Spawn a new enemy if the screen has reached a spawn position
			//if ((spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN+50 &&
			//	spawnQueue[i].x * SCREEN_SIZE > App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) ||
			//	(spawnQueue[i].x * SCREEN_SIZE <  App->render->camera.x - SPAWN_MARGIN_LEFT &&
			//	spawnQueue[i].x * SCREEN_SIZE > App->render->camera.x - SPAWN_MARGIN_LEFT - 50
			//	) || spawnQueue->spawnStart){

			if ((spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN + 50 &&
				spawnQueue[i].x * SCREEN_SIZE > App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) || spawnQueue[i].spawnStart) {
				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn(bool all)
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{

			if (all) {
				delete enemies[i];
				enemies[i] = nullptr;
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

void ModuleEnemies::HandleEnemiesDespawnEnemy(Enemy* enemy)
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{

			if (enemies[i]->GetCollider() == enemy->GetCollider()) {

				delete enemies[i];
				enemies[i] = nullptr;
				return;
			}
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
			case ENEMY_TYPE::KNIFE:
				enemies[i] = new Enemy_Knife(info.x, info.y, info.secondFloor);
				break;

			case ENEMY_TYPE::BROWNSHIELD:
				enemies[i] = new EnemyBrownShield(info.x, info.y, info.secondFloor);
				break;

			case ENEMY_TYPE::PURPLESHIELD:
				enemies[i] = new EnemyPurpleShield(info.x, info.y, info.secondFloor);
				break;

			case ENEMY_TYPE::GUNSHOOTER:
				enemies[i] = new EnemyGun(info.x, info.y, info.secondFloor);
				break;

				/*case ENEMY_TYPE::HOSTAGE:
					enemies[i] = new Hostage(info.x, info.y, info.gun, info.points, info.secondFloor, info.id);
					break;*/


			}

			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = App->audio->enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::KillAll() {

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{

			enemies[i]->setHasReceivedDamage = true;
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

	//PARA LAS PAREDES
	if (c2->type == Collider::Type::WALL && c1->type == Collider::Type::ENEMY)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
			{
				enemies[i]->OnCollision(c1, c2); //Notify the enemy of a collision

				/*if (c2->GetRect().y < c1->GetRect().y + c1->GetRect().h && ((!enemies[i]->secondFloor && c2->active) || enemies[i]->secondFloor)) {
					cout << "Caja: " << c2->GetRect().y << " PJ Y: " << c1->GetRect().y << " H: " << c1->GetRect().h << endl;
					enemies[i]->boxCollision = true;
				}*/
				break;
			}
		}
	}


	//IGNORAR LA COLISION SI EL JUGADOR ESTA EN OTRA ALTURA
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && enemies[i]->secondFloor != App->player->isSecondFloor)
		{

			return; //sale de las coisiones. ESTO DARA PROBLEMAS YA QUE SI SE TIENE QUE CHOCAR CON UNA PARED PERO UENO
		}
	}


	//RESTO DE COLISIONES
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && (enemies[i]->GetCollider() == c1 || enemies[i]->GetColliderRange() == c1))
		{
			enemies[i]->OnCollision(c1, c2); //Notify the enemy of a collision
			enemies[i]->killed = true;

			//delete enemies[i];
			//enemies[i] = nullptr;
			//destroyed = true;
			break;
		}
	}
}

Enemy* ModuleEnemies::getEnemy(int i) {
	return enemies[i];
}


