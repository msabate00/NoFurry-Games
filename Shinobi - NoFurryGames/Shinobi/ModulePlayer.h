#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer();

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;


public:
	// Position of the player in the map
	iPoint position;
	iPoint positionBefore;

	// The speed in which we move the player (pixels per frame)
	int speed = 2;

	float jumpForce = 4.8f;
	float currJumpForce = 0;
	float maxFallSpeed = -5;
	bool isJumping = false;
	bool isChangingFloorF1 = false;
	bool isChangingFloorF2 = false;
	bool isAttacking = false;
	bool isCrouchedAttacking = false;

	bool facingRight = true;

	enum STATE {
		NONE = -1,
		IDLE,
		MOVING,
		ATTACKING,
		JUMPING,
		LONG_JUMP,

		DYING
	};
	

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation forwardAnim;
	Animation backwardAnim;
	Animation crouched_idleAnim;
	Animation crouched_forwardAnim;
	Animation crouched_AttackAnim;
	Animation jumpAnim;
	Animation attack_shurikenAnim;
	Animation watching_UpAnimation;
	Animation bigJumpUpUpAnim;		
	Animation bigJumpDownUpAnim;



	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sounds Effects 
	uint saltarFX = 0;
	uint saltarPlataformaFX = 0;
	uint shurikenAtaqueFX = 0;
	uint ataqueFX = 0;
	uint morirFX = 0;

};

#endif //!__MODULE_PLAYER_H__