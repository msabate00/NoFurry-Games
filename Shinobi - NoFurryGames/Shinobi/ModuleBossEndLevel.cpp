#include "ModuleBossEndLevel.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level2.h"
#include "ModuleScene_Level1_SecondFloor.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleMapa2.h"
#include "ModuleAudio.h"
#include "Collider.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "Hostage.h"
#include "Enemy.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_render.h"

#include <iostream>

using namespace std;

ModuleBossEndLevel::ModuleBossEndLevel(bool startEnabled) : Module(startEnabled)
{


	///////////////////////
	//    ANIMACIONES    //
	///////////////////////

	// idle animation
	idleAnim.PushBack({ 281, 112, 46, 60 });
	idleAnim.speed = 0.2f;


}

ModuleBossEndLevel::~ModuleBossEndLevel()
{

}

bool ModuleBossEndLevel::Start()
{
	LOG("Loading player textures");

	bool ret = true;


	texture = App->textures->Load("Assets/Sprites/Player/Player.png"); // arcade version

	//collider = App->collisions->AddCollider({ 0,0,39,60 }, Collider::Type::PLAYER, this);

	
	currentAnimation = &idleAnim;



	return ret;
}

update_status ModuleBossEndLevel::Update()
{


	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;


}

update_status ModuleBossEndLevel::PostUpdate()
{




	


	return update_status::UPDATE_CONTINUE;
}

void ModuleBossEndLevel::OnCollision(Collider* c1, Collider* c2)
{

	



}

bool ModuleBossEndLevel::CleanUp() {

	

	return true;
}