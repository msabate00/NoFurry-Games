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
#include "EnemyGun.h"

#include <iostream>
#include "SDL/include/SDL_scancode.h"

using namespace std;


ModuleBoss::ModuleBoss(bool startEnabled) : Module(startEnabled) {

	//head_IdleAnim.PushBack({ 3,16,28,26 });

	head_IdleAnim.PushBack({ 3,16,28,26 });
	head_IdleAnim.PushBack({ 37,16,28,26 });
	head_IdleAnim.PushBack({ 71,16,28,26 });
	head_IdleAnim.PushBack({ 105,16,28,26 });
	//head_IdleAnim.PushBack({ 139,16,28,26 });
	head_IdleAnim.speed = 0.05;

	//torso_IdleAnim.PushBack({3,50, 66, 53});

	
	
	torso_IdleAnim.PushBack({75,50, 66, 53});
	torso_IdleAnim.PushBack({147,50, 66, 53});
	torso_IdleAnim.PushBack({219,50, 66, 53});
	torso_IdleAnim.speed = 0.05;
	/* NO BORRAR

	torso_IdleAnim.PushBack({3,109, 66, 53});
	torso_IdleAnim.PushBack({75,109, 66, 53});
	torso_IdleAnim.PushBack({147,109, 66, 53});
	torso_IdleAnim.PushBack({219,109, 66, 53});


	torso_IdleAnim.PushBack({3,168, 66, 53});
	torso_IdleAnim.PushBack({ 75,168, 66, 53});
	torso_IdleAnim.PushBack({ 147,168, 66, 53});
	torso_IdleAnim.PushBack({ 219,168, 66, 53});*/


	legs_IdleAnim.PushBack({4, 234, 63, 59});
	legs_IdleAnim.PushBack({73, 234, 63, 59});
	legs_IdleAnim.PushBack({142, 234, 63, 59});
	legs_IdleAnim.PushBack({211, 234, 63, 59});
	legs_IdleAnim.PushBack({280, 234, 63, 59});
	legs_IdleAnim.speed = 0.05;


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
	//torso_Collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::ENEMY, this);
	legs_Collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::ENEMY, this);



	facingRight = false;
	position.x = 375;
	position.y = 130;
	life = 5;
	inmune = false;

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
		current_legs_Animation = &legs_WalkForwardAnim;
		facingRight = true;
	}
	else if (facingRight && position.x >= 300) {
		current_legs_Animation = &legs_WalkForwardAnim;
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
		
		App->render->Blit(texture, position.x + 23, position.y - 5, SDL_FLIP_NONE, &rectHead);
		App->render->Blit(texture, position.x, position.y-10, SDL_FLIP_NONE, &rectTorso);
		App->render->Blit(texture, position.x + 21, position.y-25 + rectTorso.h, SDL_FLIP_NONE, &rectLegs);
		
		head_Collider->SetPos(position.x + 26, position.y - 5);
		//torso_Collider->SetPos(position.x, position.y - 10);
		legs_Collider->SetPos(position.x + 20, position.y - 25 + rectTorso.h );
		
	}
	else {
		App->render->Blit(texture, position.x + 11, position.y - 5, SDL_FLIP_HORIZONTAL, &rectHead);
		App->render->Blit(texture, position.x, position.y-10, SDL_FLIP_HORIZONTAL, &rectTorso);
		App->render->Blit(texture, position.x - 20, position.y-25 + rectTorso.h, SDL_FLIP_HORIZONTAL, &rectLegs);
		
		head_Collider->SetPos(position.x + 11, position.y - 5);
		//torso_Collider->SetPos(position.x, position.y+2);
		legs_Collider->SetPos(position.x - 11, position.y-25 + rectTorso.h );
		
	}


	head_Collider->SetSize(current_head_Animation->GetCurrentFrame().w, current_head_Animation->GetCurrentFrame().h);
	//torso_Collider->SetSize(current_torso_Animation->GetCurrentFrame().w, current_torso_Animation->GetCurrentFrame().h);
	legs_Collider->SetSize(current_legs_Animation->GetCurrentFrame().w, current_legs_Animation->GetCurrentFrame().h);
	


	return update_status::UPDATE_CONTINUE;
}

bool ModuleBoss::CleanUp()
{


	return true;
}

void ModuleBoss::OnCollision(Collider* c1, Collider* c2)
{

	if (c1 == head_Collider) {
		cout << "ay me dieron en la pinche cabesa";
	}


}
