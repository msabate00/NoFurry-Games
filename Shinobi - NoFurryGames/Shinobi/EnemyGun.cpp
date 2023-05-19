#include "EnemyGun.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include <iostream>
#include <math.h>

#include "SDL/include/SDL_render.h"

using namespace std;

EnemyGun::EnemyGun(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor, ENEMY_TYPE::GUNSHOOTER)
{
	walkBasic.PushBack({ 8, 351,36,60 });
	walkBasic.PushBack({ 50, 351,36,60 });

	walkBasic.loop = true;
	walkBasic.speed = 0.1f;

	recharge.PushBack({ 4,245,47,58 });
	recharge.speed = 0.1f;
	recharge.loop = false;

	//salto
	jumping.PushBack({ 202, 317,34,68 });
	jumping.loop = false;
	jumping.speed = 0.1f;

	//muerte
	Death.PushBack({ 4, 316, 63, 19 });
	Death.PushBack({ 73, 316, 63, 19 });

	Death.speed = 0.1f;
	Death.loop = false;

	Disapear.PushBack({ 0,0,0,0 });

	//ataque

	attackAnim.PushBack({ 124,252,54,51 });
	attackAnim.PushBack({ 184,252,54,51 });
	
	attackAnim.speed = 0.2f;
	attackAnim.loop = false;

	//ANIMACIÓN ESTÁTICA
	staticAnim.PushBack({ 11, 12,35,64 });
	staticAnim.speed = 0.1f;

	//path.PushBack({ -0.8f, 0.0f }, 150, &walkBasic);

	facingLeft = true;

	goingToPlayer = true;
	facingLeft = true;
	moveToDie = false;

	viewRange = 250;
	wanderRange = 50;
	attackRange = 0;
	points = 100;


}

void EnemyGun::Update()
{
	// Gravedad - INDV
	jumpSpeed += -GRAVITY;
	float grav = GRAVITY;
	if (jumpSpeed < -grav) 
	{
		isJumping = true;
	}
	position.y -= jumpSpeed;

	// Rango de visión - INDV
	if (facingLeft && App->player->position.x < (position.x - viewRange))
	{
		currentAnim = &recharge;
		position.x += speed;
	}
	else if (!facingLeft && App->player->position.x > (position.x + viewRange))
	{
		currentAnim = &recharge;
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

	// Movimiento dependiendo para donde esta mirando
	if (!setHasReceivedDamage && !isAttacking)
	{
		if (facingLeft)
		{
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


	// Disparos
		
	//if (facingLeft && (App->player->position.x + viewRange) > position.x)
	//{
	//	hasToShot = true;
	//}
	//else hasToShot = false;

	//if (hasToShot)
	//{
	//	currentAnim = &recharge;
	//	position.x += speed;

	//	if (currentAnim->HasFinished())
	//	{
	//		//aquí dispara
	//	}
	//}

	//if (currentAnim->HasFinished())
	//{
	//	currentAnim = &attackAnim;
	//	if (currentAnim->HasFinished())
	//	{
	//		hasToShot = false;
	//	}
	//}


	

	Enemy::Update();
}