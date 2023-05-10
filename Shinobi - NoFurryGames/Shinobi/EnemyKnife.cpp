#include "EnemyKnife.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include <iostream>

#include "SDL/include/SDL_render.h"

using namespace std;

Enemy_Knife::Enemy_Knife(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor)
{
	walkBasic.PushBack({ 680, 20,42,61 });
	walkBasic.PushBack({ 728, 20,42,61 });
	walkBasic.PushBack({ 776, 20,42,61 });

	walkBasic.loop = true;
	walkBasic.speed = 0.1f;

	//salto
	jumping.PushBack({ 845, 89,38,60 });
	jumping.PushBack({ 889, 89,38,60 });

	jumping.loop = false;
	jumping.speed = 0.01f;

	//muerte
	Death.PushBack({ 680, 93, 34, 47 });
	Death.PushBack({ 720, 93, 34, 47 });
	Death.PushBack({ 760, 93, 34, 47 });

	Death.speed = 0.1f;
	Death.loop = false;

	Disapear.PushBack({ 0,0,0,0 });

	//ataque

	attackAnim.PushBack({ 844,20,47,60 });
	attackAnim.PushBack({ 897,20,47,60 });


	/*attackAnim.PushBack({ 250,13,38,63 });
	attackAnim.PushBack({ 143,13,56,63 });
	attackAnim.PushBack({ 143,13,56,63 });
	attackAnim.PushBack({ 250,13,38,63 });
	attackAnim.PushBack({ 205,13,38,63 });*/

	attackAnim.speed = 0.2f;
	attackAnim.loop = false;

	//ANIMACIÓN ESTÁTICA
	staticAnim.PushBack({ 728, 20,42,61 });
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

void Enemy_Knife::Update()
{
	currentAnim = &walkBasic;

	//Gravedad
	jumpSpeed += -GRAVITY;
	float grav = GRAVITY;
	if (jumpSpeed < -grav) {
		isJumping = true;
	}
	position.y -= jumpSpeed;




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