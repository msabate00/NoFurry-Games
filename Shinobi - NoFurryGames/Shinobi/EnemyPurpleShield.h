#ifndef __ENEMYPURPLESHIELD__
#define __ENEMYPURPLESHIELD__

#include "Enemy.h"


class EnemyPurpleShield : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	EnemyPurpleShield(int x, int y, bool secondFloor);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	iPoint diePos;

	float currJumpForce = 0;
	bool goingToPlayer = true;
	bool secondFloor = false;
	int points = 100;


private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.05f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	int speed = 1;

	int destroyedCountdown = 30;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation attackPurple;

};

#endif 

