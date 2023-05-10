#ifndef __MODULE_ENEMIES_H__
#define __MODULE_ENEMIES_H__

#include "Module.h"

#define MAX_ENEMIES 100

enum class ENEMY_TYPE
{
	NO_TYPE,
	HOSTAGE,
	BASIC,
	BROWNSHIELD,
	PURPLESHIELD,
	KNIFE,
	GUNSHOOTER
};

struct EnemySpawnpoint
{
	ENEMY_TYPE type = ENEMY_TYPE::NO_TYPE;
	int id;
	int x, y;
	bool gun;
	int points;
	bool secondFloor = false;
	bool spawnStart = false;
};

class Enemy;
struct SDL_Texture;
struct Collider;


class ModuleEnemies : public Module
{
public:
	// Constructor
	ModuleEnemies(bool startEnabled);

	// Destructor
	~ModuleEnemies();

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
	bool AddEnemy(ENEMY_TYPE type, int x, int y, bool secondFloor = false, bool spawnStart = false);
	bool AddEnemy(ENEMY_TYPE type, int x, int y, bool gun, int points, bool secondFloor = false, int id = -1, bool spawnStart = false);

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemiesDespawn(bool all);
	void HandleEnemiesDespawnEnemy(Enemy* enemy);

	Enemy* getEnemy(int i);

	// The enemy's collider
	Collider* collider = nullptr;

	// A flag to detect when the enemy has been destroyed
	bool enemyDamaged = false;
	int destroyedCountdown = 30;

private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);

private:
	// A queue with all spawn points information
	EnemySpawnpoint spawnQueue[MAX_ENEMIES];

	// All spawned enemies in the scene
	Enemy* enemies[MAX_ENEMIES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an enemy
	int enemyDestroyedFx = 0;
};

#endif // __MODULE_ENEMIES_H__