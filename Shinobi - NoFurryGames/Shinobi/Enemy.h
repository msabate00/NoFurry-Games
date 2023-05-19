#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleEnemies.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y, bool secondFloor, ENEMY_TYPE type);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;
	const Collider* GetColliderRange() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision responsefloat lookForPlayer = 10;
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* c1, Collider* c2);

	int getPoints();
	void setPoints(int points);

	float timeToDestroy;
	bool secondFloor;
	bool jumpsNow = false;

	bool isJumping = false;
	float jumpSpeed = 0.0f;		//Fuerza actual del salto
	float jumpForce = -3.0f;	//Fuerza del salto al saltar
	float jumpHeight = 100.0f;	

	bool setHasReceivedDamage = false;	//Cuando recibe daño
	bool moveToDie = false;
	bool collidesWithWall = false;
	bool facingLeft = false;
	bool killed = false;
	bool boxCollision = false;

	bool ignorePlayer;


	bool isAttacking = false;


	int points;
	int speed = 1;
	int viewRange = 220;	//Distancia a la que ve el jugador
	int wanderRange = 20;	//Distancia a la que va a estar deambulando alrededor del jugador
	int attackRange = 20;	//Distancia a la que puede atacar al jugador

	

public:

	// The current position in the world
	iPoint position;
	ENEMY_TYPE type;

	iPoint diePos;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	uint destroyedFx = 0;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	Animation walkBasic, staticAnim, jumping, attackAnim, fallJumping;
	Animation Death, Disapear;

	// The enemy's collider
	Collider* collider = nullptr;
	Collider* colliderRange = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H__