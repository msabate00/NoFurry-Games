#include "Enemy_Basic.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "Enemy.h"
#include <iostream>

#include "SDL/include/SDL_render.h"



using namespace std;

Enemy_Basic::Enemy_Basic(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor, ENEMY_TYPE::BASIC)
{
	walkBasic.PushBack({ 11, 12,35,64 });
	walkBasic.PushBack({ 52, 12,35,64 });
	walkBasic.PushBack({ 93, 12,35,64 });

	walkBasic.loop = true;
	walkBasic.speed = 0.1f;

	//salto
	fallJumping.PushBack({ 12, 161,42,65 });
	jumping.PushBack({ 108, 161,42,65 });
	jumping.PushBack({ 60, 161,42,65 });

	fallJumping.loop = false;
	fallJumping.speed = 0.1f;
	jumping.loop = false;
	jumping.speed = 0.1f;

	//muerte
	Death.PushBack({ 22, 92, 30, 54 });
	Death.PushBack({ 59, 108, 65, 26 });
	Death.PushBack({ 131, 108, 65, 26 });

	Death.speed = 0.2f;
	Death.loop = false;

	Disapear.PushBack({ 0,0,0,0 });

	//ataque

	attackAnim.PushBack({ 205,13,38,63 });
	attackAnim.PushBack({ 250,13,38,63 });
	attackAnim.PushBack({ 143,13,56,63 });
	attackAnim.PushBack({ 143,13,56,63 });
	attackAnim.PushBack({ 250,13,38,63 });
	attackAnim.PushBack({ 11, 12,35,64 });


	/*attackAnim.PushBack({ 250,13,38,63 });
	attackAnim.PushBack({ 143,13,56,63 });
	attackAnim.PushBack({ 143,13,56,63 });
	attackAnim.PushBack({ 250,13,38,63 });
	attackAnim.PushBack({ 205,13,38,63 });*/

	attackAnim.speed = 0.1f;
	attackAnim.loop = false;

	//ANIMACIÓN ESTÁTICA
	staticAnim.PushBack({ 11, 12,35,64 });
	staticAnim.speed = 0.1f;
	staticAnim.loop = true;

	facingLeft = true;

	goingToPlayer = true;
	facingLeft = true;
	moveToDie = false;

	viewRange = 250;
	wanderRange = 50;
	attackRange = 0;
	points = 100;

}

void Enemy_Basic::Update()
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
	
	// Ataque :)
	if (isAttacking)
	{
		currentAnim = &attackAnim;
		/*cout << "ataca" << endl;*/

		if (currentAnim->HasFinished())
		{
			currentAnim = &walkBasic;
			isAttacking = false;
		}
	}
	
	Enemy::Update();
}