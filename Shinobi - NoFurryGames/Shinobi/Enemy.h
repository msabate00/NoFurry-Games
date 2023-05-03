#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y, bool secondFloor);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collider);

	int getPoints();
	void setPoints(int points);

	float timeToDestroy;
	float lookForPlayer = 10;
	bool secondFloor;

	bool setHasReceivedDamage = false;
	bool moveToDie = false;
	bool collidesWithWall = false;
	bool facingLeft = false;
	bool killed = false;
	bool boxCollision = false;

	int points;

public:
	// The current position in the world
	iPoint position;

	iPoint diePos;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	uint destroyedFx = 0;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	Animation walkBasic, staticAnim, jumping;
	Animation Death, Disapear;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H__