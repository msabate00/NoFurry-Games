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
	SaveHostage.PushBack({ 0, 0, 0, 0 });
	SaveHostage.loop = false;


	SaveHostage.speed = 0.1f;



	//walkBasic.loop = true;


	collider = App->collisions->AddCollider({ 0, 0,  25, 29 }, Collider::Type::HOSTAGE, (Module*)App->enemy);
}

void Hostage::Update()
{
	
	if (!saved) {
		currentAnim = &IdleHostage;
	}
	else {
		position.y--;
		currentAnim = &SaveHostage;
	}

	Enemy::Update();
}

