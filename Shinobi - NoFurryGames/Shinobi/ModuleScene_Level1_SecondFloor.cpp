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

#include <iostream>

using namespace std;

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene_Level1_SecondFloor::ModuleScene_Level1_SecondFloor(bool startEnabled) : Module(startEnabled)
{
	// ground
	up_level_fence1Rect.x = 96;
	up_level_fence1Rect.y = 204;
	up_level_fence1Rect.w = 447;
	up_level_fence1Rect.h = 28;

	up_level_fence2Rect.x = 576;
	up_level_fence2Rect.y = 204;
	up_level_fence2Rect.w = 509;
	up_level_fence2Rect.h = 28;

	up_level_fence3Rect.x = 1293;
	up_level_fence3Rect.y = 204;
	up_level_fence3Rect.w = 655;
	up_level_fence3Rect.h = 28;

}

ModuleScene_Level1_SecondFloor::~ModuleScene_Level1_SecondFloor()
{

}

// Load assets
bool ModuleScene_Level1_SecondFloor::Start()
{
	LOG("Loading background assets");
	up_level_fenceTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_solido.png");



	bool ret = true;


	//SueloArriba
	collisions[0] = App->collisions->AddCollider({ 96, 103, 990, 9 }, Collider::Type::WALL);
	collisions[1] = App->collisions->AddCollider({ 1293, 103, 655, 9 }, Collider::Type::WALL);

	//Paredes
	collisions[2] = App->collisions->AddCollider({ 80, 0, 16, 103 }, Collider::Type::WALL);
	collisions[3] = App->collisions->AddCollider({ 1086, 0, 16, 103 }, Collider::Type::WALL);
	collisions[4] = App->collisions->AddCollider({ 1278, 0, 16, 103 }, Collider::Type::WALL);
	collisions[5] = App->collisions->AddCollider({ 1949, 0, 16, 103 }, Collider::Type::WALL);
	

	//Cajas arriba
	collisions[6] = App->collisions->AddCollider({ 544, 196 - 125, 32, 32 }, Collider::Type::WALL);

	EnabledColliderForPlayer(showFence);

	return ret;
}

update_status ModuleScene_Level1_SecondFloor::Update()
{
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene_Level1_SecondFloor::PostUpdate()
{
	if (showFence) {
		App->render->Blit(up_level_fenceTexture, 96, 79, SDL_FLIP_NONE, &up_level_fence1Rect, 1.0f); // Suelo y eso
		App->render->Blit(up_level_fenceTexture, 576, 79, SDL_FLIP_NONE, &up_level_fence2Rect, 1.0f); // Suelo y eso
		App->render->Blit(up_level_fenceTexture, 1293, 79, SDL_FLIP_NONE, &up_level_fence3Rect, 1.0f); // Suelo y eso
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleScene_Level1_SecondFloor::EnabledColliderForPlayer(bool active)
{
	
	for (int i = 0; i < 7; i++) {
		collisions[i]->active = active;
	}
	showFence = active;


}

bool ModuleScene_Level1_SecondFloor::CleanUp()
{
	return true;
}
