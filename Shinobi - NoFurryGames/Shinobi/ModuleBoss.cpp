#include "ModuleBoss.h"
#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level1_SecondFloor_Enemies.h"
#include "ModuleFadeToBlack.h" 

#include "Enemy.h"
#include "Enemy_Basic.h"
#include "Hostage.h"
#include "EnemyBrownShield.h"
#include "EnemyPurpleShield.h"

#include <iostream>
#include "SDL/include/SDL_scancode.h"

using namespace std;


ModuleBoss::ModuleBoss(bool startEnabled) : Module(startEnabled) {

	head_IdleAnim.PushBack({ 0,0,18,24 });
	torso_IdleAnim.PushBack({0,25, 56, 27});
	legs_IdleAnim.PushBack({0, 122, 47, 53});


}

ModuleBoss::~ModuleBoss()
{
}

bool ModuleBoss::Start()
{

	texture = App->textures->Load("Assets/Sprites/Boss1/SpriteSheet_Boss1.png");


	current_head_Animation = &head_IdleAnim;
	current_torso_Animation = &torso_IdleAnim;
	current_legs_Animation = &legs_IdleAnim;

	current_head_Animation->Update();
	current_torso_Animation->Update();
	current_torso_Animation->Update();


	head_Collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::ENEMY, this);
	torso_Collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::ENEMY, this);
	legs_Collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::ENEMY, this);



	facingRight = false;
	position.x = 375;
	position.y = 136;

	return true;
}

update_status ModuleBoss::Update()
{

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_MainMenu, 20);
	}


	current_head_Animation = &head_IdleAnim;
	current_torso_Animation = &torso_IdleAnim;
	current_legs_Animation = &legs_IdleAnim;

	
	if (facingRight) {
		position.x += speed;
	}
	else {
		position.x -= speed;
	}

	if (!facingRight && position.x <= 100) {
		facingRight = true;
	}
	else if (facingRight && position.x >= 300) {
		facingRight = false;
	}
	


	current_head_Animation->Update();
	current_torso_Animation->Update();
	current_torso_Animation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBoss::PostUpdate()
{
	SDL_Rect rectHead =  current_head_Animation->GetCurrentFrame();
	SDL_Rect rectTorso = current_torso_Animation->GetCurrentFrame();
	SDL_Rect rectLegs =  current_legs_Animation->GetCurrentFrame();
	

	if (!facingRight) {
		
		App->render->Blit(texture, position.x, position.y+2, SDL_FLIP_NONE, &rectTorso);
		App->render->Blit(texture, position.x + 20, position.y + rectTorso.h, SDL_FLIP_NONE, &rectLegs);
		App->render->Blit(texture, position.x + 26, position.y - 9, SDL_FLIP_NONE, &rectHead);
		
		torso_Collider->SetPos(position.x, position.y + 2 );
		legs_Collider->SetPos(position.x + 20, position.y + rectTorso.h );
		head_Collider->SetPos(position.x + 26, position.y - 9);
	}
	else {
		
		App->render->Blit(texture, position.x, position.y+2, SDL_FLIP_HORIZONTAL, &rectTorso);
		App->render->Blit(texture, position.x - 11, position.y + rectTorso.h, SDL_FLIP_HORIZONTAL, &rectLegs);
		App->render->Blit(texture, position.x + 11, position.y - 9, SDL_FLIP_HORIZONTAL, &rectHead);
		
		torso_Collider->SetPos(position.x, position.y+2);
		legs_Collider->SetPos(position.x - 11, position.y + rectTorso.h );
		head_Collider->SetPos(position.x + 11, position.y - 9);
	}


	head_Collider->SetSize(current_head_Animation->GetCurrentFrame().w, current_head_Animation->GetCurrentFrame().h);
	torso_Collider->SetSize(current_torso_Animation->GetCurrentFrame().w, current_torso_Animation->GetCurrentFrame().h);
	legs_Collider->SetSize(current_legs_Animation->GetCurrentFrame().w, current_legs_Animation->GetCurrentFrame().h);
	


	return update_status::UPDATE_CONTINUE;
}

bool ModuleBoss::CleanUp()
{


	return true;
}

void ModuleBoss::OnCollision(Collider* c1, Collider* c2)
{
}
