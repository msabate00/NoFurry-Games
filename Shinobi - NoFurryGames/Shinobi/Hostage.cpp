#include "Hostage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleScene_Level1.h"
#include <iostream>

using namespace std;

Hostage::Hostage(int x, int y, bool gun, int points, bool secondFloor) : Enemy(x, y, secondFloor)
{

	this->gun = gun;
	this->points = points;

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
		if (!check) {
			position.y -= 20;
			check = true;
		}
		position.y--;
		currentAnim = &SaveHostage;
	}

	if (saved && !check2) {
		
		switch (points)
		{
			case 0:
				App->particles->AddParticle(App->particles->bonusGun, position.x, position.y, Collider::Type::NONE);
				break;
			case 200:
				App->particles->AddParticle(App->particles->bonus200, position.x, position.y, Collider::Type::NONE);
				App->scene_Level1->texture_num += 200;
				break;
			case 500:
				App->particles->AddParticle(App->particles->bonus500, position.x, position.y, Collider::Type::NONE);
				App->scene_Level1->texture_num += 500;
				break;
			case 1000:
				App->particles->AddParticle(App->particles->bonus1000, position.x, position.y, Collider::Type::NONE);
				App->scene_Level1->texture_num += 1000;
				break;
		}
		App->scene_Level1->hostage_num--;
		check2 = true;
	}

	Enemy::Update();
}


int Hostage::getPoints() {
	return this->points;
}
void Hostage::setPoints(int points) {
	this->points = points;
}
bool Hostage::getGun() {

	return gun;
}
void Hostage::setGun(bool gun) {
	this->gun = gun;
}

