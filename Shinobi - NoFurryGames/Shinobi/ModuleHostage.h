#ifndef __MODULE_HOSTAGE_H__
#define __MODULE_HOSTAGE_H__

#include "Module.h"

#define MAX_HOSTAGE 100

enum class HOSTAGE_TYPE
{
	NO_TYPE,
	HOSTAGE

};

struct HostageSpawnpoint
{
	HOSTAGE_TYPE type = HOSTAGE_TYPE::NO_TYPE;
	int id;
	int x, y;
	bool gun;
	int points;
	bool secondFloor = false;
	bool spawnStart = false;
	bool spawned = false;
};

class HostageEntity;
struct SDL_Texture;
struct Collider;


class ModuleHostage : public Module
{
public:
	// Constructor
	ModuleHostage(bool startEnabled);

	// Destructor
	~ModuleHostage();

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

	// Add an enemy into the queue to be spawned later
	bool AddHostage(HOSTAGE_TYPE type, int x, int y, bool gun, int points, bool secondFloor = false, int id = -1, bool spawnStart = false);

	// Iterates the queue and checks for camera position
	void HandleHostageSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleHostageDespawn(bool all);
	void HandleHostageDespawnEnemy(HostageEntity* enemy);

	HostageEntity* getHostage(int i);

	// The enemy's collider
	Collider* collider = nullptr;

	// A flag to detect when the enemy has been destroyed
	int destroyedCountdown = 30;

private:
	// Spawns a new enemy using the data from the queue
	void SpawnHostage(const HostageSpawnpoint& info);

private:
	// A queue with all spawn points information
	HostageSpawnpoint spawnQueue[MAX_HOSTAGE];

	// All spawned enemies in the scene
	HostageEntity* hostages[MAX_HOSTAGE] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an enemy
	int hostageDestroyedFx = 0;
};

#endif // __MODULE_ENEMIES_H__