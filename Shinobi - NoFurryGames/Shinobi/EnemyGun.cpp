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

	firesGun.PushBack({ 4,243,47,60 });
	firesGun.PushBack({ 95,351,47,60 });
	firesGun.PushBack({ 4,243,47,60 });
	firesGun.PushBack({ 95,351,47,60 });
	firesGun.PushBack({ 57,243,47,60 });
	firesGun.PushBack({ 124,243,47,60 });
	firesGun.PushBack({ 124,243,47,60 });
	firesGun.speed = 0.07f;
	firesGun.loop = true;

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

	recharging.PushBack({ 4,243,47,60 });
	recharging.PushBack({ 95,351,47,60 });
	recharging.loop = true;
	recharging.speed = 0.1f;

	//ataque

	attackAnim.PushBack({ 124,252,54,51 });
	attackAnim.PushBack({ 184,252,54,51 });
	
	attackAnim.speed = 0.2f;
	attackAnim.loop = false;

	//ANIMACI�N EST�TICA
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

	// Rango de visi�n - INDV
	if (facingLeft && App->player->position.x < (position.x - viewRange))
	{
		currentAnim = &firesGun;
		/*position.x += speed;*/
	}
	else if (!facingLeft && App->player->position.x > (position.x + viewRange))
	{
		currentAnim = &firesGun;
		/*position.x -= speed;*/
	}

	// Cuando entra en el rango, se mueve
	else
	{
		// Si el enemigo queda por detr�s del jugador, este primero cambia su direcci�n
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
			
		}
		else {
			
		}
	}

	// Salta
	/*if (!jumpsNow)
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
	}*/

	// Disparos hacia la izquierda
		
	if (facingLeft && (App->player->position.x + 250) > position.x /*&& *//*(App->player->isSecondFloor == false)*/)
	{
		hasToShot = true;
	}
	else hasToShot = false;

	if (hasToShot && facingLeft)	
	{
		currentAnim = &firesGun;
		position.x += 0;

		if (shotCounter > 0)
		{
			shotCounter--;
			bang = false;
			
			if (shotCounter == 0)
			{
				shotCounter = 90;
				bang = true;
			}
		} 
	}

	/*else if (!hasToShot)
	{
		shotCounter = 90;
	}*/

	// Disparos hacia la derecha

	if (!facingLeft && (App->player->position.x - 250) < position.x && (App->player->isSecondFloor == false))
	{
		hasToShot = true;
	}
	else hasToShot = false;

	if (hasToShot && !facingLeft)
	{
		currentAnim = &firesGun;
		position.x += 0;

		if (shotCounter > 0)
		{
			shotCounter--;
			bang = false;

			if (shotCounter == 0)
			{
				shotCounter = 90;
				bang = true;
			}
		}
	}

	/*else if (!hasToShot)
	{
		shotCounter = 90;
	}*/

	if (App->player->destroyed)
	{
		hasToShot = false;
		currentAnim = &recharging;
		shotCounter = 90;
	}

	Enemy::Update();
}