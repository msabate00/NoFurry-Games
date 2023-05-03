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
	if ((position.x+40) < App->player->position.x) 
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

	Enemy::Update();
}