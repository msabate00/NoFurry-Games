#include "EnemyBrownShield.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleScene_Level1.h"
#include <iostream>

using namespace std;

EnemyBrownShield::EnemyBrownShield(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor)
{
	
	
	idleBrown.PushBack({ 314, 108,44,65 });
	idleBrown.PushBack({ 364, 108,44,65 });

	idleBrown.speed = 0.01f;

	attackBrown.PushBack({ 314, 18,48,73 });
	attackBrown.PushBack({ 368, 18, 48,73 });
	attackBrown.PushBack({ 422, 18,48,73 });
	attackBrown.PushBack({ 476, 18,73,73 });
	attackBrown.PushBack({ 555, 18,48,73 });
	attackBrown.PushBack({ 609, 18,48,73 });
	
	attackBrown.speed = 0.1f;

	//muerte

	deathBrown.PushBack({ 414, 108, 44, 65 });
	deathBrown.PushBack({ 464, 130, 44, 43 });
	deathBrown.PushBack({ 514, 153, 44, 20 });
	deathBrown.loop = false;
	deathBrown.speed = 0.1f;





	collider = App->collisions->AddCollider({ 0, 0,44,65 }, Collider::Type::ENEMY, (Module*)App->enemy);
}

void EnemyBrownShield::Update()
{

	if (!destroyed)
	{
		currentAnim = &idleBrown;
		facingLeft = true;
	}

	if (App->enemy->destroyed == true)
	{
		currentAnim = &deathBrown;
		destroyedCountdown--;

		if (destroyedCountdown <= 0)
		{
			currentAnim = &idleBrown;
			App->enemy->destroyed = false;
		}
	}


	Enemy::Update();
}



