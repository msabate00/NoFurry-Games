#ifndef __MODULE_BOSS_H__
#define __MODULE_BOSS_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;





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
	int speed = 1;
	int life = 3;
	float inmuneTime = 3;
	bool facingRight = false;

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
	Animation torso_DamageAnim;

	//Legs
	Animation legs_IdleAnim;
	Animation legs_WalkForwardAnim;
	Animation legs_DamageAnim;

	Animation generalDying;




	Collider* head_Collider = nullptr;
	Collider* legs_Collider = nullptr;


};





#endif