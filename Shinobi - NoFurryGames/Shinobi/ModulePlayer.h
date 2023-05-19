#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

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

	bool CleanUp();


public:
	// Position of the player in the map
	iPoint position;
	iPoint positionBefore;

	int timeContador = 0;

	// The speed in which we move the player (pixels per frame)
	int speed = 2;
	int crouchedSpeed = 1;

	float jumpForce = 4.8f;
	float currJumpForce = 0;
	float maxFallSpeed = -5;
	bool isJumping = false;
	bool isChangingFloorF1 = false;
	bool isChangingFloorF2 = false;
	bool isAttacking = false;
	bool isCrouchedAttacking = false;

	bool facingRight = true;

	bool holdingGun = false;

	bool isSecondFloor = false;

	bool enemyInRange = false;

	int marginCollider = 10;
	int rangeLength = 8;

	

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;
	Animation* currentJumpAnim = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation forwardAnim;
	Animation crouched_idleAnim;
	Animation crouched_forwardAnim;
	Animation crouched_AttackAnim;
	Animation jumpAnim;
	Animation jumpAttackAnim;
	Animation attack_shurikenAnim;
	Animation watching_UpAnimation;
	Animation watching_DownAnimation;
	Animation bigJumpUpAnim;		
	Animation bigJumpDownAnim;
	Animation DeathAnim;

	Animation PistolaidleAnim;
	Animation PistolaforwardAnim;
	Animation Pistolacrouched_idleAnim;
	Animation Pistolacrouched_forwardAnim;
	Animation Pistolacrouched_AttackAnim;
	Animation PistolajumpAnim;
	Animation PistolajumpAttackAnim;
	Animation PistolaattackAnim;

	Animation PatadaAnim;
	Animation EspadaCrouchAnim;
	Animation EspadaAnim;
	Animation PatadaSaltoAnim;
	Animation PatadaKatanaAnim;

	Animation ultiEspadaAnim;

	

	// The player's collider
	Collider* collider = nullptr;
	Collider* rangeCollider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool hasPlayedDeathSound = true;
	bool inmune = false;
	bool ulti = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

	// Sounds Effects 
	uint saltarFX = 0;
	uint saltarPlataformaFX = 0;
	uint shurikenAtaqueFX = 0;
	uint ataqueFX = 0;
	uint morirFX = 0;
	uint efectoSaltoPlataformaFX = 0;

	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	float timerChangeLv2 = 0.0f;
	float timerGameover = 0.0f;
	bool gameOver = false;
	

};

#endif //!__MODULE_PLAYER_H__