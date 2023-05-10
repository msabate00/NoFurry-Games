#include "EnemyGun.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include <iostream>
#include <math.h>

#include "SDL/include/SDL_render.h"

using namespace std;

EnemyGun::EnemyGun(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor)
{
	walkBasic.PushBack({ 57, 245,47,58 });

	walkBasic.loop = true;
	walkBasic.speed = 0.1f;

	recharge.PushBack({ 4,245,47,58 });

	//salto
	jumping.PushBack({ 202, 317,34,68 });
	
	jumping.loop = false;
	jumping.speed = 0.01f;

	//muerte
	Death.PushBack({ 4, 316, 19, 63 });
	Death.PushBack({ 73, 316, 19, 63 });

	Death.speed = 0.1f;
	Death.loop = false;

	Disapear.PushBack({ 0,0,0,0 });

	//ataque

	attackAnim.PushBack({ 205,13,38,63 });
	attackAnim.PushBack({ 250,13,38,63 });
	
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
	currentAnim = &walkBasic;

	//Gravedad
	jumpSpeed += -GRAVITY;
	float grav = GRAVITY;
	if (jumpSpeed < -grav) {
		isJumping = true;
	}
	position.y -= jumpSpeed;




	if (facingLeft && App->player->position.x < (position.x - (viewRange - 20)))
	{
		currentAnim = &recharge;
		position.x += speed;
	}
	else if (!facingLeft && App->player->position.x > (position.x + (viewRange-20)))
	{
		currentAnim = &recharge;
		position.x -= speed;
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
		currentAnim = &attackAnim;

		if (currentAnim->HasFinished()) {
			isAttacking = false;
			currentAnim->Reset();
		}

	}

	Enemy::Update();
}