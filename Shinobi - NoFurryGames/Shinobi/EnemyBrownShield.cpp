#include "EnemyBrownShield.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include <iostream>

using namespace std;

EnemyBrownShield::EnemyBrownShield(int x, int y, bool secondFloor) : Enemy(x, y, secondFloor)
{
	
	
	walkBasic.PushBack({282, 332, 51, 41});
	walkBasic.loop = true;
	walkBasic.speed = 0.1f;
	
	idleBrown.PushBack({ 314, 108,44,65 });
	idleBrown.PushBack({ 364, 108,44,65 });
	idleBrown.speed = 0.01f;

	attackBrown.PushBack({ 314, 18,48,73 });
	attackBrown.PushBack({ 368, 18, 48,73 });
	attackBrown.PushBack({ 422, 18,48,73 });
	attackBrown.PushBack({ 476, 18,73,73 });
	attackBrown.PushBack({ 555, 18,48,73 });
	attackBrown.PushBack({ 609, 18,48,73 });
	
	attackBrown.speed = 0.1f;

	//muerte

	Death.PushBack({ 414, 108, 44, 65 });
	Death.PushBack({ 464, 130, 44, 43 });
	Death.PushBack({ 514, 153, 44, 20 });
	Death.loop = false;
	Death.speed = 0.1f;


	


	collider = App->collisions->AddCollider({ 0, 0,44,65 }, Collider::Type::ENEMY, (Module*)App->enemy);
}

void EnemyBrownShield::Update()
{
	// Enemigo se queda quieto si el jugador no está en su rango de visión
	if (position.x - App->player->position.x > 250)
	{
		currentAnim = &idleBrown;
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
		position.x += 1;
	}

	if (killed && !facingLeft)
	{
		position.x -= 2;
	}
	
	
	/*if (this->setHasReceivedDamage)
	{
		if (!moveToDie)
		{
			diePos = { position.x, position.y + currentAnim->GetCurrentFrame().h };
			moveToDie = true;
		}
		currentAnim = &Death;
		position.y = diePos.y - currentAnim->GetCurrentFrame().h;

		if (currentAnim->HasFinished())
		{
			currentAnim = &Disapear;
		}
	}
	else
	{

		currentAnim = &idleBrown;
		facingLeft = true;

	}

	if ((position.x - App->player->position.x) <= 80)
	{
		currentAnim = &walkBasic;
		position.x += 1;
		facingLeft = false;
	}
	else currentAnim = &idleBrown;*/
	

	/*if (!this->setHasReceivedDamage)
	{
		currentAnim = &walkBasic;
		position.x -= 1;
		facingLeft = true;

	}
	if (position.x > App->player->position.x)
	{
		position.x += 2;
		facingLeft = true;
		lookForPlayer = 10;
	}
	else{
		position.x += 2;
		facingLeft = false;
		lookForPlayer = 10;
	}*/


	Enemy::Update();
}



