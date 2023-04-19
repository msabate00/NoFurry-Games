#include "Enemy_Basic.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include <iostream>

using namespace std;

Enemy_Basic::Enemy_Basic(int x, int y) : Enemy(x, y)
{
	walkBasic.PushBack({ 5,6,24,24 });
	walkBasic.speed = 0.2f;
	walkBasic.loop = true;

	currentAnim = &walkBasic;
	
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::NONE, (Module*)App->enemy);
}

void Enemy_Basic::Update()
{

	
	waveRatio += waveRatioSpeed;

	//position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	//position.x -= 1;

	Enemy::Update();
}

