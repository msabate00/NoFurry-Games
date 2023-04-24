#ifndef __HOSTAGE__
#define __HOSTAGE__

#include "Enemy.h"
#include "Path.h"

class Hostage : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Hostage(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	bool saved = false;

private:
	
	


	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation IdleHostage;
	Animation SaveHostage;

};

#endif // __ENEMY_BASIC_H__