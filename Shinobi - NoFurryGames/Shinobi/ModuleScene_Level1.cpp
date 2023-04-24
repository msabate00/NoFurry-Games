#include "ModuleScene_Level1.h"

#include "ModuleScene_Level1_SecondFloor.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene_Level1::ModuleScene_Level1(bool startEnabled) : Module(startEnabled)
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

ModuleScene_Level1::~ModuleScene_Level1()
{

}

// Load assets
bool ModuleScene_Level1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_solido.png");
	stageBackgroundTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_fondo.png");


	// Colliders ---
	colliders.push(App->collisions->AddCollider({ 0, SCREEN_HEIGHT - 9, 2046, 9 }, Collider::Type::WALL));

	//Cajas
	colliders.push(App->collisions->AddCollider({416, 183, 32, 32}, Collider::Type::WALL));
	colliders.push(App->collisions->AddCollider({703, 183, 32, 32}, Collider::Type::WALL));
	colliders.push(App->collisions->AddCollider({863, 183, 32, 32}, Collider::Type::WALL));
	colliders.push(App->collisions->AddCollider({1437, 183, 64, 32}, Collider::Type::WALL));
	colliders.push(App->collisions->AddCollider({1405, 151, 32, 64}, Collider::Type::WALL));

	//Para testear saltos
	/*App->collisions->AddCollider({163, 183, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({173, 183-32, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({183, 183-32-32, 32, 32}, Collider::Type::WALL);
	App->collisions->AddCollider({193, 183-32-32-32, 32, 32}, Collider::Type::WALL);*/

	//SueloArriba
	//secondFloor = App->collisions->AddCollider({ 0, 103, 2046, 9 }, Collider::Type::WALL);
	//Paredes Arriba
	
	
	//Cajas arriba
	//App->collisions->AddCollider({ 544, 196-125, 32, 32 }, Collider::Type::WALL);


	//Limites jugador
	colliders.push(App->collisions->AddCollider({ -16, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL));
	colliders.push(App->collisions->AddCollider({ 2046, 0, 16, SCREEN_HEIGHT }, Collider::Type::WALL));

	//secondFloor->active = false;
	
	//Musicadddd
	App->audio->PlayMusic("Assets/Audio/Music/Mission 1-1.ogg", 1.0f);

	//Enemies ---
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 320, FLOOR_LEVEL - 64); //Enemigo básico 1
	App->enemy->AddEnemy(ENEMY_TYPE::BASIC, 365, FLOOR_LEVEL - 64); //Enemigo básico 2
	
	App->player->Enable();
	App->enemy->Enable();
	//App->scene_Level1_SecondFloor->Enable();

	return ret;
}

update_status ModuleScene_Level1::Update()
{
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene_Level1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(stageBackgroundTexture, 0, 0, SDL_FLIP_NONE,&background, 0.35f); // Edificios del fondo
	App->render->Blit(stageTexture, 0, -125, SDL_FLIP_NONE,&ground, 1.0f); // Suelo y eso

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene_Level1::CleanUp()
{


	while (!colliders.empty()) {
		colliders.top()->pendingToDelete = true;
		colliders.pop();
	}

	App->player->Disable();
	App->enemy->Disable();
	return true;
}