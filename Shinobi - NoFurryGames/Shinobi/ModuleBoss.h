#ifndef __MODULE_BOSS_H__
#define __MODULE_BOSS_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;
struct Particle;


#define TOTAL_INMUNE_TIME 180;
#define TOTAL_STUNNED_TIME 8;
#define BOSS_PARTICLE_DURATION 600;


class ModuleBoss : public Module {

public:
	// Constructor
	ModuleBoss(bool startEnabled); 

	// Destructor
	~ModuleBoss();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;


	iPoint position;
	const int speed = 1;
	int life;
	int inmuneTime = TOTAL_INMUNE_TIME;
	int stunnedTime = TOTAL_STUNNED_TIME;
	bool facingRight = false;
	bool inmune = false;
	bool stunned = false;
	int timeContador = 0;
	int timeContador2 = 0;
	int timeMovingContador = 0; 

	const int bossMovingTime = 480;
	const int bossMovingTimer = 20;


	float particleSpeed = 2.0f;
	float particleAdjustmen = 0.03f;
	fPoint currentParticleDirection = fPoint(0, 0);
	fPoint currentParticlePosition = fPoint(0, 0);
	float firstParticle = true;


	float particleSpeed2 = 2.0f;
	float particleAdjustmen2 = 0.03f;
	fPoint currentParticleDirection2 = fPoint(0, 0);
	fPoint currentParticlePosition2 = fPoint(0, 0);
	float firstParticle2 = true;



	SDL_Texture* texture = nullptr;
	Animation* current_head_Animation = nullptr;
	Animation* current_torso_Animation = nullptr;
	Animation* current_legs_Animation = nullptr;

	//Head
	Animation head_IdleAnim;
	Animation head_DamageAnim;

	//Torso
	Animation torso_IdleAnim;
	Animation torso_AttackAnim;
	Animation torso_AttackAnim1;
	Animation torso_AttackAnim2;
	Animation torso_AttackAnim3;
	Animation torso_DamageAnim;

	//Legs
	Animation legs_IdleAnim;
	Animation legs_WalkForwardAnim;
	Animation legs_DamageAnim;

	Animation generalDying;

	int fireBallParticle = -1;
	int fireBallParticle2 = -1;


	Collider* head_Collider = nullptr;
	Collider* legs_Collider = nullptr;
	Collider* fireBall_Collider = nullptr;
	Collider* fireBall_Collider2 = nullptr;

	//Efectos
	uint RecieveDamageFX = 0;
	uint FuegoFX = 0;
	uint RecieveDamage_2FX = 0;
	uint Boss_DieFX = 0;

};





#endif