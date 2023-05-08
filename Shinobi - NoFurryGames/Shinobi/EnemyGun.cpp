#include "EnemyGun.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include <iostream>

#include "SDL/include/SDL_render.h"

using namespace std;

EnemyGun::EnemyGun(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor)
{
	walkBasic.PushBack({ 11, 12,35,64 });
	walkBasic.PushBack({ 52, 12,35,64 });
	walkBasic.PushBack({ 93, 12,35,64 });

	walkBasic.loop = true;
	walkBasic.speed = 0.1f;

	//salto
	jumping.PushBack({ 12, 161,42,65 });
	jumping.PushBack({ 60, 161,42,65 });
	jumping.PushBack({ 108, 161,42,65 });

	jumping.loop = false;
	jumping.speed = 0.01f;

	//muerte
	Death.PushBack({ 22, 92, 30, 54 });
	Death.PushBack({ 59, 108, 65, 26 });
	Death.PushBack({ 131, 108, 65, 26 });

	Death.speed = 0.1f;
	Death.loop = false;

	Disapear.PushBack({ 0,0,0,0 });

	//ataque

	attackAnim.PushBack({ 205,13,38,63 });
	attackAnim.PushBack({ 250,13,38,63 });
	attackAnim.PushBack({ 143,13,56,63 });
	attackAnim.PushBack({ 143,13,56,63 });
	attackAnim.PushBack({ 250,13,38,63 });
	attackAnim.PushBack({ 11, 12,35,64 });

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
		//Si el enemigo queda por detr�s del jugador, este primero cambia su direcci�n
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

	if (App->player->destroyed && App->player->currentAnimation->HasFinished())
	{
		currentAnim = &walkBasic;
		if (facingLeft)
		{
			position.x -= speed;
		}
		else
		{
			position.x += speed;
		}

	}

	Enemy::Update();
}