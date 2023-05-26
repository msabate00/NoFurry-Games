#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleBoss.h"
#include "Enemy.h"
#include "SDL/include/SDL_timer.h"

#include <iostream>;

using namespace std;

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/Player/Player.png");


	ulti.anim.PushBack({ 399, 1447, 81, 63 });
	ulti.anim.PushBack({ 486, 1447, 81, 63 });
	ulti.anim.PushBack({ 573, 1447, 81, 63 });
	ulti.anim.PushBack({ 660, 1447, 81, 63 });
	ulti.anim.PushBack({ 747, 1447, 81, 63 });
	ulti.anim.PushBack({ 834, 1447, 81, 63 });

	ulti.anim.PushBack({ 51, 1516, 81, 63 });
	ulti.anim.PushBack({ 138, 1516, 81, 63 });
	ulti.anim.PushBack({ 225, 1516, 81, 63 });
	ulti.anim.PushBack({ 312, 1516, 81, 63 });
	ulti.anim.PushBack({ 399, 1516, 81, 63 });
	ulti.anim.PushBack({ 486, 1516, 81, 63 });
	ulti.anim.PushBack({ 573, 1516, 81, 63 });
	ulti.anim.PushBack({ 660, 1516, 81, 63 });
	ulti.anim.PushBack({ 747, 1516, 81, 63 });
	ulti.anim.PushBack({ 834, 1516, 81, 63 });

	ulti.anim.PushBack({ 51, 1516, 81, 63 });
	ulti.anim.PushBack({ 138, 1585, 81, 63 });
	ulti.anim.PushBack({ 225, 1585, 81, 63 });
	ulti.anim.PushBack({ 312, 1585, 81, 63 });
	ulti.anim.PushBack({ 399, 1585, 81, 63 });
	ulti.anim.PushBack({ 486, 1585, 81, 63 });
	ulti.anim.PushBack({ 573, 1585, 81, 63 });
	ulti.anim.PushBack({ 660, 1585, 81, 63 });
	ulti.anim.PushBack({ 747, 1585, 81, 63 });
	ulti.anim.PushBack({ 834, 1585, 81, 63 });

	ulti.anim.PushBack({ 51, 1654, 81, 63 });
	ulti.anim.PushBack({ 138, 1654, 81, 63 });
	ulti.anim.PushBack({ 225, 1654, 81, 63 });
	ulti.anim.PushBack({ 312, 1654, 81, 63 });
	ulti.anim.PushBack({ 399, 1654, 81, 63 });
	ulti.anim.PushBack({ 486, 1654, 81, 63 });
	ulti.anim.PushBack({ 573, 1654, 81, 63 });
	ulti.anim.PushBack({ 660, 1654, 81, 63 });
	ulti.anim.PushBack({ 747, 1654, 81, 63 });
	ulti.anim.PushBack({ 834, 1654, 81, 63 });

	ulti.anim.PushBack({ 51, 1723, 81, 63 });
	ulti.anim.PushBack({ 138, 1723, 81, 63 });
	ulti.anim.PushBack({ 225, 1723, 81, 63 });
	ulti.anim.PushBack({ 312, 1723, 81, 63 });
	ulti.anim.PushBack({ 399, 1723, 81, 63 });
	ulti.anim.PushBack({ 486, 1723, 81, 63 });
	ulti.anim.PushBack({ 573, 1723, 81, 63 });
	ulti.anim.PushBack({ 660, 1723, 81, 63 });
	ulti.anim.PushBack({ 747, 1723, 81, 63 });
	ulti.anim.PushBack({ 834, 1723, 81, 63 });

	ulti.anim.PushBack({ 51, 1792, 81, 63 });
	ulti.anim.PushBack({ 138, 1792, 81, 63 });
	ulti.anim.PushBack({ 225, 1792, 81, 63 });
	ulti.anim.PushBack({ 312, 1792, 81, 63 });
	ulti.anim.PushBack({ 399, 1792, 81, 63 });
	ulti.anim.PushBack({ 486, 1792, 81, 63 });
	ulti.anim.PushBack({ 573, 1792, 81, 63 });
	ulti.anim.PushBack({ 660, 1792, 81, 63 });
	ulti.anim.PushBack({ 747, 1792, 81, 63 });
	ulti.anim.PushBack({ 834, 1792, 81, 63 });

	ulti.anim.PushBack({ 51, 1861, 81, 63 });
	ulti.anim.PushBack({ 138, 1861, 81, 63 });
	ulti.anim.PushBack({ 225, 1861, 81, 63 });
	ulti.anim.PushBack({ 312, 1861, 81, 63 });
	ulti.anim.PushBack({ 399, 1861, 81, 63 });
	ulti.anim.PushBack({ 486, 1861, 81, 63 });
	ulti.anim.PushBack({ 573, 1861, 81, 63 });
	ulti.anim.PushBack({ 660, 1861, 81, 63 });
	ulti.anim.PushBack({ 747, 1861, 81, 63 });
	ulti.anim.PushBack({ 834, 1861, 81, 63 });
	
	ulti.anim.PushBack({ 51, 1930, 81, 63 });
	ulti.anim.PushBack({ 138, 1930, 81, 63 });
	ulti.anim.PushBack({ 225, 1930, 81, 63 });
	ulti.anim.PushBack({ 312, 1930, 81, 63 });
	ulti.anim.PushBack({ 399, 1930, 81, 63 });
	ulti.anim.PushBack({ 486, 1930, 81, 63 });
	ulti.anim.PushBack({ 573, 1930, 81, 63 });
	ulti.anim.PushBack({ 660, 1930, 81, 63 });
	ulti.anim.PushBack({ 747, 1930, 81, 63 });
	ulti.anim.PushBack({ 834, 1930, 81, 63 });

	ulti.anim.PushBack({ 51, 1999, 81, 63 });
	ulti.anim.PushBack({ 138, 1999, 81, 63 });
	ulti.anim.PushBack({ 225, 1999, 81, 63 });
	ulti.anim.PushBack({ 312, 1999, 81, 63 });
	ulti.anim.PushBack({ 399, 1999, 81, 63 });
	ulti.anim.PushBack({ 486, 1999, 81, 63 });
	ulti.anim.PushBack({ 573, 1999, 81, 63 });
	ulti.anim.PushBack({ 660, 1999, 81, 63 });
	ulti.anim.PushBack({ 747, 1999, 81, 63 });
	ulti.anim.PushBack({ 834, 1999, 81, 63 });


	ulti.anim.PushBack({ 0, 0, 0, 0 });

	ulti.anim.loop = false;
	ulti.anim.speed = 1;
	ulti.lifetime = 400;
	ulti.speed = fPoint(0, 0);




	ultiEspada.anim.PushBack({ 445, 1110, 20, 58 });

	ultiEspada.anim.loop = true;
	ultiEspada.anim.speed = 0.3f;
	ultiEspada.lifetime = 90;
	ultiEspada.speed = fPoint(0, 0);

	
	
	ultiTornado.anim.PushBack({ 528, 2098, 44, 208 });
	ultiTornado.anim.PushBack({ 578, 2098, 44, 208 });
	ultiTornado.anim.PushBack({ 628, 2098, 44, 208 });
	ultiTornado.anim.PushBack({ 678, 2098, 44, 208 });
	ultiTornado.anim.PushBack({ 728, 2098, 44, 208 });
	ultiTornado.anim.PushBack({ 28, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 78, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 128, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 178, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 228, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 278, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 328, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 378, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 428, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 478, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 528, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 578, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 628, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 678, 2312, 44, 208 });
	ultiTornado.anim.PushBack({ 728, 2312, 44, 208 });

	ultiTornado.anim.PushBack({ 28, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 78, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 128, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 178, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 228, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 278, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 328, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 378, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 428, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 478, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 528, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 578, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 628, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 678, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 728, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 28, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 78, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 128, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 178, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 228, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 278, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 328, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 378, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 428, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 478, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 528, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 578, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 628, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 678, 2526, 44, 208 });
	ultiTornado.anim.PushBack({ 728, 2526, 44, 208 });

	ultiTornado.anim.loop = false;
	ultiTornado.anim.speed = 0.5f;
	ultiTornado.lifetime = 105;
	ultiTornado.speed = fPoint(0, 0);

	ultiTornadoatack.anim.PushBack({ 626, 1157, 33, 11 });
	ultiTornadoatack.anim.PushBack({ 665, 1157, 33, 11 });
	ultiTornadoatack.anim.PushBack({ 704, 1157, 33, 11 });
	ultiTornadoatack.anim.PushBack({ 743, 1157, 33, 11 });

	ultiTornadoatack.anim.loop = true;
	ultiTornadoatack.anim.speed = 0.3f;
	ultiTornadoatack.lifetime = 90;
	ultiTornadoatack.speed = fPoint(0, 0);

	ultiNegro.anim.PushBack({ 445, 1110, 20, 58 });
	ultiNegro.anim.PushBack({ 0, 0, 0, 0 });

	ultiNegro.anim.loop = true;
	ultiNegro.anim.speed = 0.3f;
	ultiNegro.lifetime = 90;



	shurikenR.anim.PushBack({103, 292, 13, 10});
	shurikenR.anim.PushBack({ 120, 292, 13, 10 });
	shurikenR.anim.PushBack({ 137, 292, 13, 10 });
	shurikenR.anim.loop = true;
	shurikenR.anim.speed = 0.3f;
	shurikenR.lifetime = 80;
	shurikenR.speed = fPoint(4, 0);

	shurikenL.anim.PushBack({ 103, 292, 13, 10 });
	shurikenL.anim.PushBack({ 120, 292, 13, 10 });
	shurikenL.anim.PushBack({ 137, 292, 13, 10 });
	shurikenL.anim.loop = true;
	shurikenL.anim.speed = 0.3f;
	shurikenL.lifetime = 80;
	shurikenL.speed = fPoint(-4, 0);


	shurikenDying.anim.PushBack({ 378, 328, 15, 15});
	shurikenDying.anim.PushBack({ 399, 328, 15, 15 });
	shurikenDying.anim.PushBack({ 420, 328, 15, 15 });
	shurikenDying.anim.loop = false;
	shurikenDying.anim.speed = 0.5f;
	shurikenDying.speed = fPoint(0, 0);



	bulletR.anim.PushBack({ 279, 297, 14, 7 });
	bulletR.anim.PushBack({ 297, 297, 14, 7 });
	bulletR.anim.PushBack({ 315, 297, 14, 7 });
	bulletR.anim.loop = true;
	bulletR.anim.speed = 0.3f;
	bulletR.lifetime = 80;
	bulletR.speed = fPoint(4, 0);

	bulletL.anim.PushBack({ 279, 297, 14, 7 });
	bulletL.anim.PushBack({ 297, 297, 14, 7 });
	bulletL.anim.PushBack({ 315, 297, 14, 7 });
	bulletL.anim.loop = true;
	bulletL.anim.speed = 0.3f;
	bulletL.lifetime = 80;
	bulletL.speed = fPoint(-4, 0);


	bulletDying.anim.PushBack({ 475, 302, 41, 41 });
	bulletDying.anim.PushBack({ 520, 302, 41, 41 });
	bulletDying.anim.PushBack({ 565, 302, 41, 41 });
	bulletDying.anim.PushBack({ 610, 302, 41, 41 });
	bulletDying.anim.PushBack({ 655, 302, 41, 41 });
	bulletDying.anim.PushBack({ 700, 302, 41, 41 });
	bulletDying.anim.PushBack({ 745, 302, 41, 41 });
	bulletDying.anim.PushBack({ 790, 302, 41, 41 });
	bulletDying.anim.loop = false;
	bulletDying.anim.speed = 0.5f;
	bulletDying.speed = fPoint(0, 0);

	//Balas

	enemyShotL.anim.PushBack({ 447, 64, 13, 8 });
	enemyShotL.anim.PushBack({ 464, 64, 13, 8 });
	enemyShotL.anim.loop = true;
	enemyShotL.anim.speed = 0.3f;
	enemyShotL.lifetime = 80;
	enemyShotL.speed = fPoint(-4, 0);

	enemyShotR.anim.PushBack({ 447, 64, 13, 8 });
	enemyShotR.anim.PushBack({ 464, 64, 13, 8 });
	enemyShotR.anim.loop = true;
	enemyShotR.anim.speed = 0.3f;
	enemyShotR.lifetime = 80;
	enemyShotR.speed = fPoint(4, 0);



	bonus200.anim.PushBack({ 28,2095,38,17 });
	bonus200.anim.loop = false;
	bonus200.anim.speed = 0.5f;
	bonus200.speed = fPoint(0, -1);
	bonus200.lifetime = 60;

	bonus500.anim.PushBack({76,2095,38,17});
	bonus500.anim.loop = false;
	bonus500.anim.speed = 0.5f;
	bonus500.speed = fPoint(0, -1);
	bonus500.lifetime = 60;

	bonus1000.anim.PushBack({ 122,2095,47,17 });
	bonus1000.anim.loop = false;
	bonus1000.anim.speed = 0.5f;
	bonus1000.speed = fPoint(0, -1);
	bonus1000.lifetime = 60;

	bonusGun.anim.PushBack({ 179,2095,49,19 });
	bonusGun.anim.loop = false;
	bonusGun.anim.speed = 0.5f;
	bonusGun.speed = fPoint(0, -1);
	bonusGun.lifetime = 60;


	/*fireBall.anim.PushBack({302, 993, 31, 27});
	fireBall.anim.PushBack({339, 993, 31, 27});
	fireBall.anim.PushBack({376, 993, 31, 27});
	fireBall.anim.PushBack({413, 993, 31, 27});
	fireBall.anim.PushBack({450, 993, 31, 27});
	fireBall.anim.PushBack({487, 993, 31, 27});
	fireBall.anim.PushBack({524, 993, 31, 27});
	fireBall.anim.PushBack({561, 993, 31, 27});
	fireBall.anim.PushBack({598, 993, 31, 27});*/

	
	fireBall.anim.PushBack({ 598, 993, 31, 27 });
	fireBall.anim.PushBack({ 561, 993, 31, 27 });
	fireBall.anim.PushBack({ 524, 993, 31, 27 });
	fireBall.anim.PushBack({ 487, 993, 31, 27 });
	fireBall.anim.PushBack({ 450, 993, 31, 27 });
	fireBall.anim.PushBack({ 413, 993, 31, 27 });
	fireBall.anim.PushBack({ 376, 993, 31, 27 });
	fireBall.anim.PushBack({ 339, 993, 31, 27 });
	fireBall.anim.PushBack({ 302, 993, 31, 27 });
	fireBall.anim.PushBack({ 0, 0, 0, 0 });
	fireBall.anim.PushBack({ 0, 0, 0, 0 });
	fireBall.anim.PushBack({ 0, 0, 0, 0 });
	fireBall.anim.PushBack({ 0, 0, 0, 0 });
	fireBall.anim.PushBack({ 0, 0, 0, 0 });
	fireBall.anim.PushBack({ 0, 0, 0, 0 });
	fireBall.anim.PushBack({ 0, 0, 0, 0 });
	fireBall.anim.PushBack({ 0, 0, 0, 0 });
	fireBall.anim.pingpong = true;
	fireBall.anim.speed = 0.5f;
	fireBall.speed = fPoint(0, 0);
	fireBall.lifetime = 40;
	

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}


void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{

			if (c2->type == Collider::Type::ENEMY) {
				for (uint i = 0; i < MAX_ENEMIES; i++){
					if (App->enemy->getEnemy(i) != nullptr && c2 == App->enemy->getEnemy(i)->GetCollider()) {
						if (App->enemy->getEnemy(i)->secondFloor != App->player->isSecondFloor) {
							return;
						}
						break;
					}
				}
			}

			


			if (!c2->active) { return; } //SI ESA COLISION NO ESTA ACTIVA, IGNORA TODO LO DE ABAJO


			if (particles[i]->collider->type == Collider::Type::PLAYER_SHOT && !App->player->holdingGun) {
				App->particles->AddParticle(shurikenDying, particles[i]->position.x, particles[i]->position.y-3, Collider::Type::NONE);
				particles[i]->collider->pendingToDelete = true;
			}
			else if (particles[i]->collider->type == Collider::Type::PLAYER_SHOT && App->player->holdingGun) {
				App->particles->AddParticle(bulletDying, particles[i]->position.x-10, particles[i]->position.y - 14, Collider::Type::NONE);
				particles[i]->collider->pendingToDelete = true;
			}
			if (particles[i]->collider != nullptr) {
				particles[i]->collider->pendingToDelete = true;
			}
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}


update_status ModuleParticles::Update()
{

	
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;


		if (particle->collider != nullptr) {
			if (particle->collider->type == Collider::Type::PLAYER_SWORD_ULTI) {


				if ((particle->position.x * SCREEN_SIZE) + particle->anim.GetCurrentFrame().w >= App->render->camera.x + SCREEN_WIDTH * SCREEN_SIZE) {
					if (particle->speed.x >= 0) {
						particle->speed.x *= -1;
					}
				}
	
				if ((particle->position.x * SCREEN_SIZE) + particle->anim.GetCurrentFrame().w <= App->render->camera.x + SCREEN_WIDTH/100 * SCREEN_SIZE) {
					if (particle->speed.x <= 0) {
						particle->speed.x *= -1;
					}
				}
				if ((particle->position.y * SCREEN_SIZE) + particle->anim.GetCurrentFrame().h >= App->render->camera.y + SCREEN_HEIGHT * SCREEN_SIZE) {
					if (particle->speed.y >= 0) {
						particle->speed.y *= -1;
					}
				}
				if ((particle->position.y * SCREEN_SIZE) <= App->render->camera.y) {
					particle->position.y =  10;
					particle->speed.y *= -1;
				}
			}
		}


		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			if (particle->collider != nullptr) {
				particle->collider->pendingToDelete = true;
			}
			
			delete particle;
			particles[i] = nullptr;
		}

	}
	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			if (!App->player->isChangingZone && particle->collider != nullptr && particle->collider->type == Collider::Type::PLAYER_SWORD_ULTI) {


				if (particle->speed.x > 0 && particle->speed.y > 0) {
					App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()), 1, 135);
				}
				if (particle->speed.x < 0 && particle->speed.y > 0) {
					App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()), 1, 225);

				}
				if (particle->speed.x > 0 && particle->speed.y < 0) {
					App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()), 1, 45);

				}
				if (particle->speed.x < 0 && particle->speed.y < 0) {
					App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()), 1, 315);
				}
				if (particle->speed.x == 0 && particle->speed.y == 0) {
					App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()), 1, 0);
				}
				if (particle->speed.x == 0) {
					if (particle->speed.y > 0) {
						App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()), 1, 180);
					}
					if (particle->speed.y < 0) {
						App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()), 1, 0);
					}
				}
				if (particle->speed.y == 0) {
					if (particle->speed.x > 0) {
						App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()), 1, 0);
					}
					if (particle->speed.x < 0) {
						App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()), 1, 0);
					}
				}

			}
			else {
				App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()));
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

int ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* p = new Particle(particle);
	
	p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
	p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
	p->position.y = y;						

	//Adding the particle's collider
	if (colliderType != Collider::Type::NONE)
		p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
	int aux = lastParticle++;
	particles[aux] = p;
	lastParticle %= MAX_ACTIVE_PARTICLES;

	return aux;

}

int ModuleParticles::AddParticle(const Particle& particle, int x, int y, fPoint initial_speed, Collider::Type colliderType, uint delay)
{
	Particle* p = new Particle(particle);

	p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
	p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
	p->position.y = y;
	p->speed = initial_speed;

	//Adding the particle's collider
	if (colliderType != Collider::Type::NONE)
		p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);
	int aux = lastParticle++;
	particles[aux] = p;
	lastParticle %= MAX_ACTIVE_PARTICLES;

	return aux;

}


void ModuleParticles::SetSpeedParticle(int position, fPoint speed) {
	Particle* particle = particles[position];
	if (particle != nullptr && particle->isAlive) {
		particle->speed = speed;
	}
}

fPoint ModuleParticles::GetPositionParticle(int position) {

	Particle* particle = particles[position];
	if (particle != nullptr && particle->isAlive) {
		return particle->position;
	}
	else {
		return fPoint(0, 0);
	}
}

fPoint ModuleParticles::GetPositionSpeed(int position) {

	Particle* particle = particles[position];
	if (particle != nullptr && particle->isAlive) {
		return particle->speed;
	}
	else {
		return fPoint(0, 0);
	}
}


void ModuleParticles::DestroyCollision(int position) {
	Particle* particle = particles[position];
	if (particle != nullptr && particle->isAlive) {
		particle->collider->pendingToDelete = true;
	}
}
