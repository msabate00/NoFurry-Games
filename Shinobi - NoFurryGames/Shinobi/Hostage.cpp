#include "Hostage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleScene_Level1.h"
#include "ModuleAudio.h"
#include "ModuleInterface.h"
#include <iostream>

using namespace std;

Hostage::Hostage(int x, int y, bool gun, int points, bool secondFloor, int id) : HostageEntity(x, y, secondFloor, HOSTAGE_TYPE::HOSTAGE)
{
	
	this->gun = gun;
	this->points = points;
	this->id = id;
	//IdleHostage

	walkBasic.PushBack({ 616, 259,25,29 });
	walkBasic.PushBack({ 647, 259,25,29 });
	walkBasic.PushBack({ 678, 259,25,29 });
	walkBasic.PushBack({ 647, 259,25,29 });
	walkBasic.PushBack({ 678, 259,25,29 });
	walkBasic.PushBack({ 647, 259,25,29 });
	walkBasic.PushBack({ 616, 259,25,29 });
	walkBasic.PushBack({ 709, 259,25,29 });
	walkBasic.PushBack({ 616, 259,25,29 });
	walkBasic.PushBack({ 709, 259,25,29 });
	

	viewRange = 0;	//Distancia a la que ve el jugador
	wanderRange = 0;	//Distancia a la que va a estar deambulando alrededor del jugador
	attackRange = 0;	//Distancia a la que puede atacar al jugador




	/*IdleHostage.PushBack({ 616, 259,25,29 });

	IdleHostage.PushBack({ 647, 259,25,29 });

	IdleHostage.PushBack({ 678, 259,25,29 });

	IdleHostage.PushBack({ 709, 259,25,29 });


	1232321414*/

	walkBasic.speed = 0.1f;

	//muerte SaveHostage

	Death.PushBack({ 616, 297, 25, 51 });
	Death.PushBack({ 647, 297, 25, 51 });
	Death.PushBack({ 678, 297, 25, 51 });
	Death.PushBack({ 709, 297, 25, 51 });
	Death.PushBack({ 0, 0, 0, 0 });
	Death.loop = false;


	Death.speed = 0.1f;

	//walkBasic.loop = true;

	

	collider = App->collisions->AddCollider({ 0, 0,  25, 29 }, Collider::Type::HOSTAGE, (Module*)App->hostages);
}

void Hostage::Update()
{

	
	
	
	if (!saved) {
		currentAnim = &Death;
	}
	else {
		if (!check) {
			position.y -= 20;
			check = true;
			App->audio->PlayFx(App->audio->SalvadoFX);
		}
		position.y--;
		currentAnim = &Death;
		
	}

	if (saved && !check2) {
		
		switch (points)
		{
			case 0:
				App->particles->AddParticle(App->particles->bonusGun, position.x, position.y, Collider::Type::NONE);
				break;
			case 200:
				App->particles->AddParticle(App->particles->bonus200, position.x, position.y, Collider::Type::NONE);
				App->interface_module->texture_num += 200;
				break;
			case 500:
				App->particles->AddParticle(App->particles->bonus500, position.x, position.y, Collider::Type::NONE);
				App->interface_module->texture_num += 500;
				break;
			case 1000:
				App->particles->AddParticle(App->particles->bonus1000, position.x, position.y, Collider::Type::NONE);
				App->interface_module->texture_num += 1000;
				break;
		}
		App->interface_module->hostage_num--;
		check2 = true;
	}

	collider->SetPos(position.x, position.y - 2);

	HostageEntity::Update();
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

