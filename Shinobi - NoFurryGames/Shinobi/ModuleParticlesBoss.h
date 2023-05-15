#ifndef __MODULE_PARTICLESBOSS_H__
#define __MODULE_PARTICLESBOSS_H__

#include "Module.h"

#include "Globals.h"
#include "ParticleBoss.h"
#include "Collider.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;

class ModuleParticlesBoss : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticlesBoss(bool startEnabled);

	//Destructor
	~ModuleParticlesBoss();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;


	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	int AddParticle(const ParticleBoss& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

	void SetSpeedParticle(int position, fPoint speed);
	fPoint GetPositionParticle(int position);
	void DestroyCollision(int position);


private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	ParticleBoss* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

	// An index to the last added particle
	uint lastParticle = 0;

public:


	ParticleBoss fireBall;



};

#endif // !__MODULEPARTICLES_H__