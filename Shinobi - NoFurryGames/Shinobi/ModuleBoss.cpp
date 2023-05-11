#include "ModuleBoss.h"
#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleScene_MainMenu.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level1_SecondFloor_Enemies.h"
#include "ModuleFadeToBlack.h" 

#include "Enemy.h"
#include "Enemy_Basic.h"
#include "Hostage.h"
#include "p2Point.h"
#include "Particle.h"
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

	

	
	torso_IdleAnim.PushBack({ 75,50, 66, 53 });
	/*
	torso_IdleAnim.PushBack({75,50, 66, 53});
	torso_IdleAnim.PushBack({147,50, 66, 53});
	torso_IdleAnim.PushBack({219,50, 66, 53});*/
	torso_IdleAnim.speed = 0.05;
	/* NO BORRAR

	torso_IdleAnim.PushBack({3,109, 66, 53});
	torso_IdleAnim.PushBack({75,109, 66, 53});
	torso_IdleAnim.PushBack({147,109, 66, 53});
	torso_IdleAnim.PushBack({219,109, 66, 53});

	haz 
	torso_IdleAnim.PushBack({3,168, 66, 53});
	torso_IdleAnim.PushBack({ 75,168, 66, 53});
	torso_IdleAnim.PushBack({ 147,168, 66, 53});
	torso_IdleAnim.PushBack({ 219,168, 66, 53});*/

	
	torso_AttackAnim.PushBack({ 75,50, 66, 53 });
	torso_AttackAnim.PushBack({ 147,50, 66, 53 });
	torso_AttackAnim.PushBack({ 219,50, 66, 53 });
	torso_AttackAnim.speed = 0.05;
	torso_AttackAnim.loop = false;


	torso_DamageAnim.PushBack({ 3,168, 66, 53 });
	torso_DamageAnim.speed = 0.05;

	head_DamageAnim.PushBack({ 139,16,28,26 });
	head_DamageAnim.speed = 0.05;
	
	legs_DamageAnim.PushBack({ 211, 234, 63, 59 });
	legs_DamageAnim.speed = 0.05;

	legs_IdleAnim.PushBack({ 73, 234, 63, 59 });
	legs_IdleAnim.speed = 0.05;


	legs_WalkForwardAnim.PushBack({4, 234, 63, 59});
	legs_WalkForwardAnim.PushBack({73, 234, 63, 59});
	legs_WalkForwardAnim.PushBack({142, 234, 63, 59});
	legs_WalkForwardAnim.PushBack({211, 234, 63, 59});
	legs_WalkForwardAnim.PushBack({280, 234, 63, 59});
	legs_WalkForwardAnim.speed = 0.1f;
	

	generalDying.PushBack({ 5,345,59,94 });
	generalDying.PushBack({ 70,345,59,94 });
	generalDying.PushBack({ 135,345,109,94 });
	generalDying.PushBack({ 250,345,109,94 });
	generalDying.PushBack({ 365,345,109,94 });
	generalDying.speed = 0.05;

}

ModuleBoss::~ModuleBoss()
{
}

bool ModuleBoss::Start()
{

	texture = App->textures->Load("Assets/Sprites/Boss1/SpriteSheet_Boss1.png");


	current_head_Animation = &head_IdleAnim;
	current_torso_Animation = &torso_IdleAnim;
	current_legs_Animation = &legs_WalkForwardAnim;

	current_head_Animation->Update();
	current_torso_Animation->Update();
	current_torso_Animation->Update();


	head_Collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::ENEMY, this);
	//torso_Collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::ENEMY, this);
	legs_Collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::ENEMY, this);



	facingRight = false;
	position.x = 375;
	position.y = 130;
	life = 8;
	inmune = false;
	timeContador = 0;

	return true;
}

update_status ModuleBoss::Update()
{
	

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_MainMenu, 20);
	}

	

	


	current_head_Animation = &head_IdleAnim;
	current_torso_Animation = &torso_IdleAnim;
	current_legs_Animation = &legs_WalkForwardAnim;


	//SPAWN BOLA DI FOGO
	int aux = BOSS_PARTICLE_DURATION;
	if ((timeContador % aux) == 0) {
		//fireBallParticle = App->particles->AddParticle(App->particles->fireBall, position.x, position.y, Collider::Type::ENEMY_SHOT);
		fireBallParticle = App->particles->AddParticle(App->particles->fireBall, position.x, position.y, Collider::Type::BOSS_PROYECTILE);
		currentParticleDirection.x = particleSpeed;
		currentParticleDirection.y = 0;
		timeContador = 0;
		current_torso_Animation
	}
	if (fireBallParticle != -1) {
		
		if (App->player->position.y - App->player->currentAnimation->GetCurrentFrame().h > App->particles->GetPositionParticle(fireBallParticle).y) {
			currentParticleDirection.y = min(currentParticleDirection.y + particleAdjustmen, particleSpeed);

		}
		else if (App->player->position.y - App->player->currentAnimation->GetCurrentFrame().h / 3 < App->particles->GetPositionParticle(fireBallParticle).y) {
			currentParticleDirection.y = max(currentParticleDirection.y - particleAdjustmen, -particleSpeed);
		}
	
		

		if (App->player->position.x > App->particles->GetPositionParticle(fireBallParticle).x) {
			currentParticleDirection.x = min(currentParticleDirection.x + particleAdjustmen, particleSpeed);
		}
		else if (App->player->position.x < App->particles->GetPositionParticle(fireBallParticle).x) {
			currentParticleDirection.x = max(currentParticleDirection.x - particleAdjustmen, -particleSpeed);
		}
	}
	App->particles->SetSpeedParticle(fireBallParticle, currentParticleDirection);

	
	if (timeMovingContador >= (bossMovingTime)) {
		if (bossMovingTimer <= (timeMovingContador - bossMovingTime)) {
			timeMovingContador = 0;
		}

		if (facingRight) {
			position.x += speed;
		}
		else {
			position.x -= speed;
		}
		
		current_legs_Animation = &legs_WalkForwardAnim;
	}
	else {
		current_legs_Animation = &legs_IdleAnim;
	}



	
	


	//if (!stunned) {

	//	if (facingRight) {
	//		position.x += speed;
	//	}
	//	else {
	//		position.x -= speed;
	//	}
	//	
	//}
	//if(stunned || inmune) { //recibir damage
	//	if (stunnedTime > 0) {
	//		current_head_Animation = &head_DamageAnim;
	//		current_torso_Animation = &torso_DamageAnim;
	//		current_legs_Animation = &legs_DamageAnim;
	//		stunnedTime--;
	//	}
	//	else {
	//		stunned = false;
	//		current_head_Animation->Reset();
	//	}

	//	inmuneTime--;
	//	if (inmuneTime <= 0) {
	//		inmuneTime = TOTAL_INMUNE_TIME;
	//		stunnedTime = TOTAL_STUNNED_TIME;
	//		inmune = false;
	//		
	//	}
	//}

	//if (!facingRight && position.x <= 200) { //andar
	//	current_legs_Animation = &legs_WalkForwardAnim;
	//	facingRight = true;
	//}
	//else if (facingRight && position.x >= 400) {
	//	current_legs_Animation = &legs_WalkForwardAnim;
	//	facingRight = false;
	//}
	


	current_head_Animation->Update();
	current_torso_Animation->Update();
	current_legs_Animation->Update();

	timeContador++;
	timeMovingContador++;


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

	//if (life <= 0) {//morir

	//	App->render->Blit(texture, position.x + 11, position.y - 5, SDL_FLIP_HORIZONTAL, &rectHead);
	//	App->render->Blit(texture, position.x + 11, position.y - 5, SDL_FLIP_HORIZONTAL, &rectHead);
	//	App->render->Blit(texture, position.x + 11, position.y - 5, SDL_FLIP_HORIZONTAL, &rectHead);


	//}

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

	if (c1 == head_Collider && c2->type == Collider::Type::PLAYER_SHOT && !inmune) {
		inmune = true;
		stunned = true;
		life--;
		if (life <= 0) {//morir
			current_head_Animation = &generalDying;
			App->fade->FadeToBlack(App->activeModule, App->scene_MainMenu);
		}
	}


}
