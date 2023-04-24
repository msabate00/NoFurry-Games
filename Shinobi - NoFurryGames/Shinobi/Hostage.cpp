#include "Hostage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include <iostream>

using namespace std;

Hostage::Hostage(int x, int y) : Enemy(x, y)
{
	IdleHostage.PushBack({ 616, 259,25,29 });
	IdleHostage.PushBack({ 647, 259,25,29 });
	IdleHostage.PushBack({ 678, 259,25,29 });
	IdleHostage.PushBack({ 709, 259,25,29 });


	IdleHostage.speed = 0.1f;

	//muerte
	SaveHostage.PushBack({ 616, 297, 25, 51 });
	SaveHostage.PushBack({ 647, 297, 25, 51 });
	SaveHostage.PushBack({ 678, 297, 25, 51 });
	SaveHostage.PushBack({ 709, 297, 25, 51 });


	SaveHostage.speed = 0.1f;



	//walkBasic.loop = true;


	collider = App->collisions->AddCollider({ 0, 0, 35, 64 }, Collider::Type::ENEMY, (Module*)App->enemy);
}

void Hostage::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	//position.y = spawnPos.y + (waveHeight * sinf(waveRatio));
	//position.x -= 1;

	Enemy::Update();
}

