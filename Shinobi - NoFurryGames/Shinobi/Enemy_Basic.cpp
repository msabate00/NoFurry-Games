#include "Enemy_Basic.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Basic::Enemy_Basic(int x, int y) : Enemy(x, y)
{
	walkBasic.PushBack({ 5,6,24,24 });
	walkBasic.speed = 0.2f;

	currentAnim = &walkBasic;
	
	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemy);
}

void Enemy_Basic::Update()
{
	waveRatio += waveRatioSpeed;

	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	position.x -= 1;

	Enemy::Update();
}

