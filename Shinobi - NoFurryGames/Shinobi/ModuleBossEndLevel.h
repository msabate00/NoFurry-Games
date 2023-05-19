#ifndef __MODULE_BOSSENDLEVEL_H__
#define __MODULE_BOSSENDLEVEL_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleBossEndLevel : public Module
{
public:
	// Constructor
	ModuleBossEndLevel(bool startEnabled);

	// Destructor
	~ModuleBossEndLevel();

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
	



	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation actionAnim;
	


};

#endif //!__MODULE_PLAYER_H__