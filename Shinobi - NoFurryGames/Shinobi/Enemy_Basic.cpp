#include "Enemy_Basic.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include <iostream>

#include "SDL/include/SDL_render.h"

using namespace std;

Enemy_Basic::Enemy_Basic(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor)
{
	walkBasic.PushBack({ 11, 12,35,64 });
	walkBasic.PushBack({ 52, 12,35,64 });
	walkBasic.PushBack({ 93, 12,35,64 });
	walkBasic.loop = true;
	walkBasic.speed = 0.1f;

	//muerte
	Death.PushBack({ 22, 92, 30, 54 });
	Death.PushBack({ 59, 108, 65, 26 });
	Death.PushBack({ 131, 108, 65, 26 });
	Death.PushBack({ 131, 108, 65, 26 });
	Death.PushBack({ 131, 108, 65, 26 });
	Death.speed = 0.1f;
	Death.loop = false;

	Disapear.PushBack({ 0,0,0,0 });

	//ANIMACIÓN ESTÁTICA
	staticAnim.PushBack({ 11, 12,35,64 });
	staticAnim.PushBack({ 52, 12,35,64 });
	staticAnim.PushBack({ 93, 12,35,64 });
	staticAnim.speed = 0.1f;

	//path.PushBack({ -0.8f, 0.0f }, 150, &walkBasic);
	
	collider = App->collisions->AddCollider({ 0, 0, 35, 64 }, Collider::Type::ENEMY, (Module*)App->enemy);

	facingLeft = true;
	facingRight = false;

	goingToPlayer = true;
	facingRight = false;
	facingLeft = true;
	secondFloor = false;
	moveToDie = false;

	points = 100;

	
}

void Enemy_Basic::Update()
{

	if (!this->setHasReceivedDamage) 
	{

		currentAnim = &walkBasic;
		position.x -= 1;
		facingLeft = true;

	}
	if (position.x < App->player->position.x) 
	{
		position.x += 2;
		facingLeft = false;
		lookForPlayer = 10;
	}
	
	/*SDL_Rect rect = currentAnim->GetCurrentFrame();
	if (facingLeft) 
	{
		App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_NONE, &rect);
	}
	else 
	{
		App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_HORIZONTAL, &rect);
	}*/
	
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