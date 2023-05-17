#ifndef __HOSTAGE__
#define __HOSTAGE__

#include "HostageEntity.h"
#include "Path.h"

struct Collider;

class Hostage : public HostageEntity
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Hostage(int x, int y, bool gun, int points, bool secondFloor, int id);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	bool gun = false;
	int points = 0;
	bool saved = false;
	bool check = false;
	bool check2 = false;
	bool secondFloor = false;
	int id = -1;

	int getPoints();
	void setPoints(int points);
	bool getGun();
	void setGun(bool gun);

private:
	
	

	//Sound Effect
	uint SalvadoFX = 0;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation IdleHostage;
	Animation SaveHostage;


};

#endif // __ENEMY_BASIC_H__