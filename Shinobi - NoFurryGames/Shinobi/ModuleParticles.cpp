#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
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

	
	shurikenR.anim.PushBack({103, 292, 13, 10});
	shurikenR.anim.PushBack({ 120, 292, 13, 10 });
	shurikenR.anim.PushBack({ 137, 292, 13, 10 });
	shurikenR.anim.loop = true;
	shurikenR.anim.speed = 0.3f;
	shurikenR.lifetime = 80;
	shurikenR.speed = iPoint(4, 0);

	shurikenL.anim.PushBack({ 103, 292, 13, 10 });
	shurikenL.anim.PushBack({ 120, 292, 13, 10 });
	shurikenL.anim.PushBack({ 137, 292, 13, 10 });
	shurikenL.anim.loop = true;
	shurikenL.anim.speed = 0.3f;
	shurikenL.lifetime = 80;
	shurikenL.speed = iPoint(-4, 0);


	shurikenDying.anim.PushBack({ 378, 328, 15, 15});
	shurikenDying.anim.PushBack({ 399, 328, 15, 15 });
	shurikenDying.anim.PushBack({ 420, 328, 15, 15 });
	shurikenDying.anim.loop = false;
	shurikenDying.anim.speed = 0.5f;
	shurikenDying.speed = iPoint(0, 0);



	bulletR.anim.PushBack({ 279, 297, 14, 7 });
	bulletR.anim.PushBack({ 297, 297, 14, 7 });
	bulletR.anim.PushBack({ 315, 297, 14, 7 });
	bulletR.anim.loop = true;
	bulletR.anim.speed = 0.3f;
	bulletR.lifetime = 80;
	bulletR.speed = iPoint(4, 0);

	bulletL.anim.PushBack({ 279, 297, 14, 7 });
	bulletL.anim.PushBack({ 297, 297, 14, 7 });
	bulletL.anim.PushBack({ 315, 297, 14, 7 });
	bulletL.anim.loop = true;
	bulletL.anim.speed = 0.3f;
	bulletL.lifetime = 80;
	bulletL.speed = iPoint(-4, 0);


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
	bulletDying.speed = iPoint(0, 0);






	bonus200.anim.PushBack({ 28,2095,38,17 });
	bonus200.anim.loop = false;
	bonus200.anim.speed = 0.5f;
	bonus200.speed = iPoint(0, -1);
	bonus200.lifetime = 60;

	bonus500.anim.PushBack({76,2095,38,17});
	bonus500.anim.loop = false;
	bonus500.anim.speed = 0.5f;
	bonus500.speed = iPoint(0, -1);
	bonus500.lifetime = 60;

	bonus1000.anim.PushBack({ 122,2095,47,17 });
	bonus1000.anim.loop = false;
	bonus1000.anim.speed = 0.5f;
	bonus1000.speed = iPoint(0, -1);
	bonus1000.lifetime = 60;

	bonusGun.anim.PushBack({ 49,2095,228,19 });
	bonusGun.anim.loop = false;
	bonusGun.anim.speed = 0.5f;
	bonusGun.speed = iPoint(0, -1);
	bonusGun.lifetime = 60;
	

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
			if (particles[i]->collider->type == Collider::Type::PLAYER_SHOT && !App->player->holdingGun) {
				App->particles->AddParticle(shurikenDying, particles[i]->position.x, particles[i]->position.y-3, Collider::Type::NONE);
				particles[i]->collider->pendingToDelete = true;
			}
			else if (particles[i]->collider->type == Collider::Type::PLAYER_SHOT && App->player->holdingGun) {
				App->particles->AddParticle(bulletDying, particles[i]->position.x-10, particles[i]->position.y - 14, Collider::Type::NONE);
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
			App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE,&(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* p = new Particle(particle);
	
	p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
	p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
	p->position.y = y;						

	//Adding the particle's collider
	if (colliderType != Collider::Type::NONE)
		p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

	particles[lastParticle++] = p;
	lastParticle %= MAX_ACTIVE_PARTICLES;
}