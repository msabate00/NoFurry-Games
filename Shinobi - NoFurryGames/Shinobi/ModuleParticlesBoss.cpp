#include "ModuleParticlesBoss.h"

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

ModuleParticlesBoss::ModuleParticlesBoss(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticlesBoss::~ModuleParticlesBoss()
{

}

bool ModuleParticlesBoss::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/Player/Player.png");

	
	fireBallBig.anim.PushBack({ 524, 993, 31, 27 });
	fireBallBig.anim.PushBack({ 561, 993, 31, 27 });
	fireBallBig.anim.PushBack({ 598, 993, 31, 27 });
	fireBallBig.anim.loop = true;
	fireBallBig.anim.speed = 0.5f;

	fireBallMedium.anim.PushBack({ 376, 993, 31, 27 });
	fireBallMedium.anim.PushBack({ 413, 993, 31, 27 });
	fireBallMedium.anim.PushBack({ 450, 993, 31, 27 });
	fireBallMedium.anim.pingpong = true;
	fireBallMedium.anim.speed = 0.5f;

	fireBallLittle.anim.PushBack({ 302, 993, 31, 27 });
	fireBallLittle.anim.PushBack({ 339, 993, 31, 27 });
	fireBallLittle.anim.pingpong = true;
	fireBallLittle.anim.speed = 0.5f;

	/*fireBall.anim.PushBack({ 302, 993, 31, 27 });
	fireBall.anim.PushBack({ 339, 993, 31, 27 });
	fireBall.anim.PushBack({ 376, 993, 31, 27 });
	fireBall.anim.PushBack({ 413, 993, 31, 27 });
	fireBall.anim.PushBack({ 450, 993, 31, 27 });
	fireBall.anim.PushBack({ 487, 993, 31, 27 });
	fireBall.anim.PushBack({ 524, 993, 31, 27 });
	fireBall.anim.PushBack({ 561, 993, 31, 27 });
	fireBall.anim.PushBack({ 598, 993, 31, 27 });
	fireBall.anim.pingpong = true;
	fireBall.anim.speed = 0.5f;
	fireBall.speed = fPoint(-1, -1);
	fireBall.lifetime = BOSS_PARTICLE_DURATION;*/


	return true;
}

bool ModuleParticlesBoss::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}


void ModuleParticlesBoss::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{

			if (c1->type == Collider::Type::BOSS_PROYECTILE && c2->active && c2->type == Collider::Type::WALL) {
				if (c2->GetRect().y > c1->GetRect().y) {
					App->boss->currentParticleDirection.y *= -1;
				}
				else {
					App->boss->currentParticleDirection.x *= -1;
				}
				return;
			}


			if (!c2->active) { return; } //SI ESA COLISION NO ESTA ACTIVA, IGNORA TODO LO DE ABAJO


			
			if (particles[i]->collider != nullptr) {
				particles[i]->collider->pendingToDelete = true;
			}
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}


update_status ModuleParticlesBoss::Update()
{


	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		ParticleBoss* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update() == false)
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

update_status ModuleParticlesBoss::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		ParticleBoss* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, SDL_FLIP_NONE, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

int ModuleParticlesBoss::AddParticle(const ParticleBoss& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	ParticleBoss* p = new ParticleBoss(particle);

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


void ModuleParticlesBoss::SetSpeedParticle(int position, fPoint speed) {
	ParticleBoss* particle = particles[position];
	if (particle != nullptr && particle->isAlive) {
		particle->speed = speed;
	}
}

fPoint ModuleParticlesBoss::GetPositionParticle(int position) {

	ParticleBoss* particle = particles[position];
	if (particle != nullptr && particle->isAlive) {
		return particle->position;
	}
	else {
		return fPoint(0, 0);
	}


}
