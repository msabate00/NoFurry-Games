#include "EnemyPurpleShield.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include <iostream>

using namespace std;

EnemyPurpleShield::EnemyPurpleShield(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor)
{

	walkBasic.PushBack({ 282, 332, 41, 51 });
	walkBasic.PushBack({ 329, 332, 41, 51 });
	walkBasic.PushBack({ 376, 332, 41, 51 });
	walkBasic.loop = true;
	walkBasic.speed = 0.1f;

	staticAnim.PushBack({ 509, 258,33,65 });
	staticAnim.PushBack({ 548, 258,33,65 });
	staticAnim.loop = true;
	staticAnim.speed = 0.01f;

	attackPurple.PushBack({ 282, 253,47,70 });
	attackPurple.PushBack({ 335, 253, 47,70 });
	attackPurple.PushBack({ 388, 253,59,70 });
	attackPurple.PushBack({ 453, 253,47,70 });
	attackPurple.loop = false;

	attackPurple.speed = 0.1f;

	//muerte

	Death.PushBack({ 429, 331, 39, 65 });
	Death.PushBack({ 474, 331, 39, 65 });
	Death.PushBack({ 519, 331, 39, 65 });
	Death.loop = false;
	Death.speed = 0.1f;

	collider = App->collisions->AddCollider({ 0, 0,44,65 }, Collider::Type::ENEMY, (Module*)App->enemy);
}

void EnemyPurpleShield::Update()
{
	currentAnim = &walkBasic;

	//Gravedad
	jumpSpeed += -GRAVITY;
	float grav = GRAVITY;
	if (jumpSpeed < -grav) {
		isJumping = true;
	}
	position.y -= jumpSpeed;




	if (position.x - App->player->position.x > viewRange)
	{
		currentAnim = &staticAnim;
		position.x += 0;
	}
	// Cuando entra en el rango, se mueve
	else
	{
		//Si el enemigo queda por detrás del jugador, este primero cambia su dirección
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

	if (isAttacking) {
		currentAnim = &attackPurple;

		if (currentAnim->HasFinished()) {
			isAttacking = false;
			currentAnim->Reset();
		}

	}



	Enemy::Update();
	}


