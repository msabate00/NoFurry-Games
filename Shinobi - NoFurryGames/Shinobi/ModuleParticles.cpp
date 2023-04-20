#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "SDL/include/SDL_timer.h"

#include <iostream>;

using namespace std;

ModuleParticles::ModuleParticles()
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
	shurikenR.lifetime = 60;
	shurikenR.speed = iPoint(4, 0);

	shurikenL.anim.PushBack({ 103, 292, 13, 10 });
	shurikenL.anim.PushBack({ 120, 292, 13, 10 });
	shurikenL.anim.PushBack({ 137, 292, 13, 10 });
	shurikenL.anim.loop = true;
	shurikenL.anim.speed = 0.3f;
	shurikenL.lifetime = 60;
	shurikenL.speed = iPoint(-4, 0);


	shurikenDying.anim.PushBack({});
	shurikenDying.anim.loop = false;
	shurikenDying.speed = iPoint(0, 0);



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
			particles[i]->collider->pendingToDelete = true;
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
			particle->collider->pendingToDelete = true;
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