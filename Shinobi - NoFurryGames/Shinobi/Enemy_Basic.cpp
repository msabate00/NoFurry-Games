#include "Enemy_Basic.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include <iostream>

using namespace std;

Enemy_Basic::Enemy_Basic(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor)
{
	walkBasic.PushBack({ 11, 12,35,64 });
	walkBasic.PushBack({ 52, 12,35,64 });
	walkBasic.PushBack({ 93, 12,35,64 });
	walkBasic.loop = true;
	walkBasic.speed = 0.1f;

	//muerte
	DeathBasic.PushBack({ 22, 92, 30, 54 });
	DeathBasic.PushBack({ 59, 108, 65, 26 });
	DeathBasic.PushBack({ 131, 108, 65, 26 });
	DeathBasic.PushBack({ 131, 108, 65, 26 });
	DeathBasic.PushBack({ 131, 108, 65, 26 });
	DeathBasic.speed = 0.1f;
	DeathBasic.loop = false;

	//path.PushBack({ -0.8f, 0.0f }, 150, &walkBasic);
	
	collider = App->collisions->AddCollider({ 0, 0, 35, 64 }, Collider::Type::ENEMY, (Module*)App->enemy);

	facingLeft = true;
	facingRight = false;
	destroyed = false;

	goingToPlayer = true;
	facingRight = false;
	facingLeft = true;
	secondFloor = false;
	moveToDie = false;

	
}

void Enemy_Basic::Update()
{

	if (this->setHasReceivedDamage) {
		if (!moveToDie) {
			position.y = (position.y + currentAnim->GetCurrentFrame().h);
		}
		currentAnim = &DeathBasic;
		currentAnim->Update();
		if (!moveToDie) {
			position.y = (position.y - 26);
			moveToDie = true;
		}
		if (currentAnim->HasFinished()) {
			//HACER QUE DESAPAREZCA
		}
	}
	else {

		currentAnim = &walkBasic;


	}

	/*if (destroyed == false)
	{
		
		currentAnim = &walkBasic;
		position.y -= 2;
		facingLeft = true;
	}*/

	/*if (App->enemy->destroyed == true)
	{
		currentAnim = &DeathBasic;
		destroyedCountdown--;

			if (destroyedCountdown <= 0) 
			{
				currentAnim = &walkBasic;
				App->enemy->destroyed = false;
			}
	}*/




	

	Enemy::Update();
}


