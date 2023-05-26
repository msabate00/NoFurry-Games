#ifndef __ENEMY_GUN_H__
#define __ENEMY_GUN_H__

#include "Enemy.h"

class EnemyGun : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	EnemyGun(int x, int y, bool secondFloor);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	bool goingToPlayer = true;
	bool secondFloor = false;
	bool moveToDie = false;

	bool hasToShot = false;

	int shotCounter = 210;


	iPoint diePos;


private:

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;



	int attackCooldown = 30;

	int destroyedCountdown = 30;

	int distanceBetween;
	int distanceToAttack = 3;

	Animation firesGun;

};

#endif // __ENEMY_GUN_H__

