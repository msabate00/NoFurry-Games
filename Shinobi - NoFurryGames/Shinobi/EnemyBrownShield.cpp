#include "EnemyBrownShield.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include <iostream>

using namespace std;

EnemyBrownShield::EnemyBrownShield(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor, ENEMY_TYPE::BROWNSHIELD)
{
	
	walkBasic.PushBack({282, 332, 41, 51});
	walkBasic.PushBack({ 329, 332, 41, 51 });
	walkBasic.PushBack({ 376, 332, 41, 51 });
	walkBasic.loop = true;
	walkBasic.speed = 0.1f;
	
	staticAnim.PushBack({ 509, 258,33,65 });
	staticAnim.PushBack({ 548, 258,33,65 });
	staticAnim.loop = true;
	staticAnim.speed = 0.012f;

	attackBrown.PushBack({ 314, 18, 48,73 });
	attackBrown.PushBack({ 368, 18, 48,73 });
	attackBrown.PushBack({ 422, 18, 48,73 });
	attackBrown.PushBack({ 476, 18, 73,73 });
	attackBrown.PushBack({ 555, 18, 48,73 });
	attackBrown.PushBack({ 609, 18, 48,73 });
	
	attackBrown.speed = 0.1f;

	//muerte

	Death.PushBack({ 422, 100, 39, 65 });
	Death.PushBack({ 477, 100, 39, 65 });
	Death.PushBack({ 532, 100, 39, 65 });
	Death.loop = false;
	Death.speed = 0.1f;

	staticAnim.PushBack({ 314, 100, 48, 73 });
	staticAnim.PushBack({ 368, 100, 48, 73 });
	staticAnim.loop = true;
	staticAnim.speed = 0.1f;
	
	collider = App->collisions->AddCollider({ 0, 0,44,65 }, Collider::Type::ENEMY, (Module*)App->enemy);
}

void EnemyBrownShield::Update()
{

		// Gravedad - INDV
		jumpSpeed += -GRAVITY;
		float grav = GRAVITY;
		if (jumpSpeed < -grav) {
			isJumping = true;
		}
		position.y -= jumpSpeed;


		// Rango de visión - INDV
		if (facingLeft && App->player->position.x < (position.x - viewRange))
		{
			currentAnim = &staticAnim;
			position.x += speed;
		}
		else if (!facingLeft && App->player->position.x > (position.x + viewRange))
		{
			currentAnim = &staticAnim;
			position.x -= speed;
		}

		// Cuando entra en el rango, se mueve
		else
		{
			// Si el enemigo queda por detrás del jugador, este primero cambia su dirección
			if (position.x < App->player->position.x - wanderRange && facingLeft)
			{
				facingLeft = false;
			}
			if (position.x > App->player->position.x + wanderRange && !facingLeft)
			{
				facingLeft = true;
			}
		}

		//Movimiento dependiendo para donde esta mirando
		if (!setHasReceivedDamage && !isAttacking) {
			if (facingLeft) {
				position.x -= speed;
			}
			else {
				position.x += speed;
			}
		}

		// Salta
		if (!jumpsNow)
		{
			currentAnim = &walkBasic;
		}
		else if (jumpsNow)
		{
			currentAnim = &jumping;
		}

		if (currentAnim->HasFinished())
		{
			jumpsNow = false;
		}

		// Ataque :)
		if (isAttacking) {
			currentAnim = &attackBrown;

			if (currentAnim->HasFinished()) {
				isAttacking = false;
				currentAnim->Reset();
			}
		}

		// Si lo mata, quedarse quieto
		if (facingLeft && App->player->destroyed)
		{
			currentAnim = &staticAnim;
			position.x += speed;
		}
		else if (!facingLeft && App->player->destroyed)
		{
			currentAnim = &staticAnim;
			position.x -= speed;
		}
	


	Enemy::Update();
}



