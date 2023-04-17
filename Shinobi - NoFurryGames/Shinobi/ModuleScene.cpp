#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene()
{
	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 2046;
	ground.h = 350;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;


}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_solido.png");
	stageBackgroundTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_fondo.png");


	// Colliders ---
	App->collisions->AddCollider({ 0, SCREEN_HEIGHT-9, 3930, 9 }, Collider::Type::WALL);
	App->collisions->AddCollider({416, 183, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({703, 183, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({863, 183, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({163, 183, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({173, 183-32, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({183, 183-32-32, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({193, 183-32-32-32, 32, 32}, Collider::Type::WALL);

	//Enemies ---
	/*App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 600, 80);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 625, 80);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 640, 80);
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 665, 80);*/


	return ret;
}

update_status ModuleScene::Update()
{
	flag.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(stageBackgroundTexture, 0, 0, SDL_FLIP_NONE,&background, 0.75f); // Edificios del fondo
	App->render->Blit(stageTexture, 0, -125, SDL_FLIP_NONE,&ground, 1.0f); // Suelo y eso

	return update_status::UPDATE_CONTINUE;
}