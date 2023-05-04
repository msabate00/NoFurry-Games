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

	//salto
	jumping.PushBack({ 108, 161,42,65 });
	jumping.PushBack({ 12, 161,42,65 });
	jumping.PushBack({ 60, 161,42,65 });
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
	attackAnim.PushBack({205,13,38,63});
	attackAnim.PushBack({250,13,38,63});
	attackAnim.PushBack({243,13,56,63});
	attackAnim.PushBack({ 250,13,38,63 });
	attackAnim.PushBack({ 205,13,38,63 });
	attackAnim.speed = 1.2f;
	attackAnim.loop = false;

	//ANIMACIÓN ESTÁTICA
	staticAnim.PushBack({ 11, 12,35,64 });
	staticAnim.speed = 0.1f;

	//path.PushBack({ -0.8f, 0.0f }, 150, &walkBasic);
	
	collider = App->collisions->AddCollider({ 0, 0, 35, 64 }, Collider::Type::ENEMY, (Module*)App->enemy);

	facingLeft = true;

	goingToPlayer = true;
	facingRight = false;
	facingLeft = true;
	secondFloor = false;
	moveToDie = false;

	points = 100;

	
}

void Enemy_Basic::Update()
{

	if (boxCollision)
	{
		isJumping = true;
		jumpSpeed = -6.0f;
	}

	if (isJumping)
	{
		position.y += jumpSpeed;
		jumpSpeed += gravity;

		if (position.y >= position.y + jumpHeight)
		{
			isJumping = false;
			jumpSpeed = 0.0f;
			position.y = position.y + jumpHeight;
		}
	}

	if (!isJumping)
	{
		// Enemigo se queda quieto si el jugador no está en su rango de visión
		if (position.x - App->player->position.x > 250)
		{
			currentAnim = &staticAnim;
			position.x += 0;
		}
		// Cuando entra en el rango, se mueve
		else
		{
			currentAnim = &walkBasic;
			position.x -= 1;
			facingLeft = true;
		}

		//Si el enemigo queda por detrás del jugador, este primero cambia su dirección
		if ((position.x + 40) < App->player->position.x)
		{
			currentAnim = &walkBasic;
			position.x += 2;
			facingLeft = false;
		}

		// Lo siguiente es para que no se mueva al morir
		if (killed)
		{
			position.x += 1;
		}

		if (killed && !facingLeft)
		{
			position.x -= 2;
		}

		if (position.x == App->player->position.x)
		{
			position.x += 1;
			currentAnim = &staticAnim;
		}
	}

	if (boxCollision && !facingLeft)
	{
		currentAnim = &jumping;
		position.x -= 1;
		position.y -= 1;

		int MAX_JUMP_HEIGHT = position.y + 32;

		// Detener el salto a cierta altura
		if (position.y <= MAX_JUMP_HEIGHT)
		{
			jumpSpeed = 0.0f;
		}
	}

	if (boxCollision)
	{
		currentAnim = &jumping;
		position.x -= 1;
		position.y -= 2;
	}

	
	//// Enemigo se queda quieto si el jugador no está en su rango de visión
	//if (position.x - App->player->position.x > 250)
	//{
	//	currentAnim = &staticAnim;
	//	position.x += 0;
	//}
	//// Cuando entra en el rango, se mueve
	//else
	//{
	//	currentAnim = &walkBasic;
	//	position.x -= 1;
	//	facingLeft = true;
	//}

	////Si el enemigo queda por detrás del jugador, este primero cambia su dirección
	//if ((position.x+40) < App->player->position.x) 
	//{
	//	currentAnim = &walkBasic;
	//	position.x += 2;
	//	facingLeft = false;
	//}

	//// Lo siguiente es para que no se mueva al morir
	//if (killed)
	//{
	//	position.x += 1;
	//}

	//if (killed && !facingLeft)
	//{
	//	position.x -= 2;
	//}

	//if (position.x == App->player->position.x)
	//{
	//	position.x += 1;
	//	currentAnim = &staticAnim;
	//}

	//
	////// Mecánica de ataque

	////if (facingLeft && position.x > App->player->position.x && position.x < (App->player->position.x + 50))
	////{
	////	cout << "debe salir" << endl;
	////	position.x -= 1;
	////	currentAnim = &attackAnim;

	////	if (App->player->destroyed)
	////	{
	////		position.x += 1;
	////		currentAnim = &staticAnim;
	////	}

	////}


	//// Colisión con las cajas
	//if (boxCollision && !facingLeft)
	//{
	//	currentAnim = &jumping;
	//	position.x -= 2;
	//	position.y -= 2;

	//	/*if (position.y == )*/
	//}

	//if (boxCollision)
	//{
	//	currentAnim = &jumping;
	//	position.x -= 1;
	//	position.y -= 2;
	//}


	Enemy::Update();
}