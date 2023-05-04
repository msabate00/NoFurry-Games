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
	staticAnim.speed = 0.012f;

	attackBrown.PushBack({ 314, 18,48,73 });
	attackBrown.PushBack({ 368, 18, 48,73 });
	attackBrown.PushBack({ 422, 18,48,73 });
	attackBrown.PushBack({ 476, 18,73,73 });
	attackBrown.PushBack({ 555, 18,48,73 });
	attackBrown.PushBack({ 609, 18,48,73 });

	attackBrown.speed = 0.1f;

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
	// Enemigo se queda quieto si el jugador no está en su rango de visión
	if (position.x - App->player->position.x > 150)
	{
		currentAnim = &staticAnim;
		position.x += 0;
		facingLeft = true;
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
		position.x += 0;
	}

	if (killed && currentAnim == &walkBasic)
	{
		position.x += 1;
	}

	if (killed && !facingLeft)
	{
		position.x -= 2;
	}

	Enemy::Update();
}
