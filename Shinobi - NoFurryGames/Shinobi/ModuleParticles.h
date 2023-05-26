#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

#include "Globals.h"
#include "Particle.h"
#include "Collider.h"

#define MAX_ACTIVE_PARTICLES 1000

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles(bool startEnabled);

	//Destructor
	~ModuleParticles();

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
	int AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);
	int AddParticle(const Particle& particle, int x, int y, fPoint initial_speed, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

	void SetSpeedParticle(int position, fPoint speed);
	fPoint GetPositionParticle(int position);
	fPoint GetPositionSpeed(int position);
	void DestroyCollision(int position);


private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

	// An index to the last added particle
	uint lastParticle = 0;

public:

	Particle ultiNegro;
	Particle ultiEspada;
	Particle ultiTornado;
	Particle ultiTornadoatack;
	Particle ulti;

	Particle shurikenR;
	Particle shurikenL;
	Particle shurikenDying;

	Particle bulletR;
	Particle bulletL;
	Particle bulletDying;

	Particle enemyShotR;
	Particle enemyShotL;

	Particle bonus200;
	Particle bonus500;
	Particle bonus1000;
	Particle bonusGun;


	Particle fireBall;



};

#endif // !__MODULEPARTICLES_H__