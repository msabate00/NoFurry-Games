#include "Enemy_Basic.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include <iostream>

using namespace std;

Enemy_Basic::Enemy_Basic(int x, int y) : Enemy(x, y)
{
	walkBasic.PushBack({ 11, 12,35,64 });
	walkBasic.PushBack({ 52, 12,35,64 });
	walkBasic.PushBack({ 93, 12,35,64 });

	walkBasic.speed = 0.1f;

	//muerte
	
	//walkBasic.loop = true;

	path.PushBack({ -0.8f, 0.0f }, 150, &walkBasic);
	
	collider = App->collisions->AddCollider({ 0, 0, 35, 64 }, Collider::Type::ENEMY, (Module*)App->enemy);
}

void Enemy_Basic::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();
	
	//position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	//position.x -= 1;

	Enemy::Update();
}

