#include "ModuleBoss.h"
#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleParticlesBoss.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleScene_MainMenu.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level1_SecondFloor_Enemies.h"
#include "ModuleFadeToBlack.h" 
#include "ModuleMapaV.h" 
#include "ModuleInterface.h"

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
#include "SDL_mixer/include/SDL_mixer.h"

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
	
	
	//Torso atraque 1

	//torso_AttackAnim1

	torso_AttackAnim1.PushBack({ 3,50, 66, 53 });
	torso_AttackAnim1.PushBack({ 75,50, 66, 53 });
	torso_AttackAnim1.PushBack({ 147,50, 66, 53 });
	torso_AttackAnim1.PushBack({ 219,50, 66, 53 });
	torso_AttackAnim1.PushBack({ 219,50, 66, 53 });
	torso_AttackAnim1.PushBack({ 219,50, 66, 53 });
	torso_AttackAnim1.PushBack({ 219,50, 66, 53 });
	torso_AttackAnim1.PushBack({ 147,50, 66, 53 });
	torso_AttackAnim1.PushBack({ 75,50, 66, 53 });
	torso_AttackAnim1.PushBack({ 3,50, 66, 53 });
	torso_AttackAnim1.speed = 0.05;
	torso_AttackAnim1.loop = false;

	//Torso ataque 2

	//torso_AttackAnim2
	
	torso_AttackAnim2.PushBack({ 3,50, 66, 53 });
	torso_AttackAnim2.PushBack({ 75,50, 66, 53 });
	torso_AttackAnim2.PushBack({ 147,50, 66, 53 });
	torso_AttackAnim2.PushBack({ 219,50, 66, 53 });
	torso_AttackAnim2.PushBack({ 3,109, 66, 53 });
	torso_AttackAnim2.PushBack({ 75,109, 66, 53 });
	torso_AttackAnim2.PushBack({ 147,109, 66, 53 });
	torso_AttackAnim2.PushBack({ 219,109, 66, 53 });
	torso_AttackAnim2.PushBack({ 3,168, 66, 53 });
	torso_AttackAnim2.PushBack({ 75,168, 66, 53 });
	torso_AttackAnim2.PushBack({ 147,168, 66, 53 });
	torso_AttackAnim2.speed = 0.05;
	torso_AttackAnim2.loop = false;
	

	//Torso ataque 3

	//torso_AttackAnim3

	torso_AttackAnim3.PushBack({ 147,109, 66, 53 });
	torso_AttackAnim3.PushBack({ 219,109, 66, 53 });
	torso_AttackAnim3.PushBack({ 3,168, 66, 53 });
	torso_AttackAnim3.PushBack({ 75,168, 66, 53 });
	torso_AttackAnim3.PushBack({ 147,168, 66, 53 });
	torso_AttackAnim3.speed = 0.05;
	torso_AttackAnim3.loop = false;



	
	/*
	torso_AttackAnim.PushBack({ 75,50, 66, 53 });
	torso_AttackAnim.PushBack({ 147,50, 66, 53 });
	torso_AttackAnim.PushBack({ 219,50, 66, 53 });
	torso_AttackAnim.speed = 0.05;
	torso_AttackAnim.loop = false;
	*/

	torso_DamageAnim.PushBack({ 407,170, 66, 53 });
	torso_DamageAnim.PushBack({ 3,168, 66, 53 });
	torso_DamageAnim.speed = 0.3;
	torso_DamageAnim.loop = false;

	torso_dead.PushBack({ 0,0,0,0 });

	head_DamageAnim.PushBack({ 444,134,28,26 });
	head_DamageAnim.PushBack({ 139,16,28,26 });
	head_DamageAnim.speed = 0.3;
	head_DamageAnim.loop = false;

	legs_DamageAnim.PushBack({ 409, 236, 63, 59 });
	legs_DamageAnim.PushBack({ 211, 234, 63, 59 });
	legs_DamageAnim.speed = 0.3;
	legs_DamageAnim.loop = false;

	legs_dead.PushBack({ 0,0,0,0 });

	legs_IdleAnim.PushBack({ 280, 234, 63, 59 });
	legs_IdleAnim.speed = 0.05;


	legs_WalkForwardAnim.PushBack({4, 234, 63, 59});
	legs_WalkForwardAnim.PushBack({73, 234, 63, 59});
	legs_WalkForwardAnim.PushBack({142, 234, 63, 59});
	legs_WalkForwardAnim.PushBack({211, 234, 63, 59});
	legs_WalkForwardAnim.PushBack({280, 234, 63, 59});
	legs_WalkForwardAnim.speed = 0.2f;
	

	generalDying.PushBack({ 4,458,112,90 });
	generalDying.PushBack({ 122,458,112,90 });
	generalDying.PushBack({ 240,458,112,90 });
	generalDying.PushBack({ 4,554,112,90 });
	generalDying.PushBack({ 122,554,112,90 });
	generalDying.PushBack({ 240,554,112,90 });
	generalDying.PushBack({ 358,554,112,90 });
	generalDying.PushBack({ 5,650,112,90 });
	
	generalDying.loop = false;

	generalDying.speed = 0.05;

	//Animacion Primer Nivel
	//Cambio de cabezas
	// { 5,750,87,92 }
	// { 98,750,87,92 }
	//Andar
	// { 205,750,87,92 }
	// { 298,750,87,92 }
	// { 391,750,87,92 }
	//Ataque
	// { 5,852,87,92 }



	/*
	generalDying.PushBack({ 5,345,59,94 });
	generalDying.PushBack({ 70,345,59,94 });
	generalDying.PushBack({ 135,345,109,94 });
	generalDying.PushBack({ 250,345,109,94 });
	generalDying.PushBack({ 365,345,109,94 });
	generalDying.speed = 0.05;*/

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
	life = 1;
	inmune = false;
	dead = false;
	timeContador = 0;

	RecieveDamageFX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Get_Shooted(right area).wav");
	FuegoFX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Fire_Boss");
	RecieveDamage_2FX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Get_Shooted");
	Boss_DieFX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Boss_Die");

	generalDying.Reset();

	return true;
}

update_status ModuleBoss::Update()
{
	
	//App->particlesBoss->DestroyCollision(fireBallParticle);
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_MainMenu, 20);
	}

	if (dead) {
		current_head_Animation = &generalDying;
		current_torso_Animation = &torso_dead;
		current_legs_Animation = &legs_dead;
		if (current_head_Animation->HasFinished()) {

			timerChangeFinal += App->deltaTime;
			App->interface_module->gameChange = false;

			if (timerChangeFinal <= 20) {
				App->interface_module->texture_num += 5000;
				App->interface_module->texture_num += 20000;
			}
			if (timerChangeFinal >= 5000 || App->interface_module->remaining_time == 0) {
				App->interface_module->gameChange = true;
				App->fade->FadeToBlack(App->activeModule, App->mapaV);
			}
		}
		current_head_Animation->Update();
		return update_status::UPDATE_CONTINUE;
	}
	current_head_Animation = &head_IdleAnim;
	current_torso_Animation = &torso_IdleAnim;
	current_legs_Animation = &legs_WalkForwardAnim;

	if (App->player->destroyed) {
		return update_status::UPDATE_CONTINUE;
	}

	//BOLA DI FOGO 1
	int aux = BOSS_PARTICLE_DURATION;
	if (timeContador % aux == 0) {

		//animacion ataque
		if (attacking == -1) {
			int ran = (rand() % 2) + 1; //1-3
				attacking = ran;
		}

		firstParticle = true;
		if (firstParticle) {
			currentParticlePosition = fPoint(position.x, position.y);
			currentParticleDirection.x = particleSpeed;
			currentParticleDirection.y = 0;
			int ran = rand() % 3;
			switch (ran) {
			case 0:
				fireBallParticle = App->particlesBoss->AddParticle(App->particlesBoss->fireBall1, currentParticlePosition.x, currentParticlePosition.y);
				break;
			case 1:
				fireBallParticle = App->particlesBoss->AddParticle(App->particlesBoss->fireBall2, currentParticlePosition.x, currentParticlePosition.y);
				break;
			case 2:
				fireBallParticle = App->particlesBoss->AddParticle(App->particlesBoss->fireBall3, currentParticlePosition.x, currentParticlePosition.y);
				break;
			}
			
			
			fireBall_Collider = App->collisions->AddCollider({ 0,0,20,20 }, Collider::Type::BOSS_PROYECTILE, this);
			timeContador = 0;
			firstParticle = false;
		}
		
	}
	else {
		if (!firstParticle && timeContador < (aux - aux /4)) {
			currentParticlePosition.x += currentParticleDirection.x;
			currentParticlePosition.y += currentParticleDirection.y;
			
			//cout << "x: " << currentParticleDirection.x << " Y: " << currentParticleDirection.y << endl;

			current_torso_Animation = &torso_AttackAnim;
			

			//Y
			if (App->player->position.y - App->player->currentAnimation->GetCurrentFrame().h > App->particlesBoss->GetPositionParticle(fireBallParticle).y) {
				currentParticleDirection.y = min(currentParticleDirection.y + particleAdjustmen, particleSpeed);
			}
			else if (App->player->position.y - App->player->currentAnimation->GetCurrentFrame().h  < App->particlesBoss->GetPositionParticle(fireBallParticle).y) {
				currentParticleDirection.y = max(currentParticleDirection.y - particleAdjustmen, -particleSpeed);
			}


			//X
			if (App->player->position.x > App->particlesBoss->GetPositionParticle(fireBallParticle).x) {
			
				currentParticleDirection.x = min(currentParticleDirection.x + particleAdjustmen, particleSpeed);
			}
			else if (App->player->position.x < App->particlesBoss->GetPositionParticle(fireBallParticle).x) {
				
				currentParticleDirection.x = max(currentParticleDirection.x - particleAdjustmen, -particleSpeed);
			}

			fireBall_Collider->SetPos(currentParticlePosition.x+5, currentParticlePosition.y+5);
			//fireBallParticle = App->particlesBoss->AddParticle(App->particlesBoss->fireBall, currentParticlePosition.x, currentParticlePosition.y);
			int ran = rand() % 3;
			switch (ran) {
			case 0:
				fireBallParticle = App->particlesBoss->AddParticle(App->particlesBoss->fireBall1, currentParticlePosition.x, currentParticlePosition.y);
				break;
			case 1:
				fireBallParticle = App->particlesBoss->AddParticle(App->particlesBoss->fireBall2, currentParticlePosition.x, currentParticlePosition.y);
				break;
			case 2:
				fireBallParticle = App->particlesBoss->AddParticle(App->particlesBoss->fireBall3, currentParticlePosition.x, currentParticlePosition.y);
				break;
			}

		}
		else {
			if (fireBall_Collider != nullptr)
				fireBall_Collider->pendingToDelete = true;
		}
	}

	if (timeContador2 % (aux+30) == 0) {
		firstParticle2 = true;
		
		if (firstParticle2) {
			
			currentParticlePosition2 = fPoint(position.x, position.y+20);
			currentParticleDirection2.x = particleSpeed2;
			currentParticleDirection2.y = 0;
		
			int ran = rand() % 3;
			switch (ran) {
			case 0:
				fireBallParticle2 = App->particlesBoss->AddParticle(App->particlesBoss->fireBall1, currentParticlePosition2.x, currentParticlePosition2.y);
				break;
			case 1:
				fireBallParticle2 = App->particlesBoss->AddParticle(App->particlesBoss->fireBall2, currentParticlePosition2.x, currentParticlePosition2.y);
				break;
			case 2:
				fireBallParticle2 = App->particlesBoss->AddParticle(App->particlesBoss->fireBall3, currentParticlePosition2.x, currentParticlePosition2.y);
				break;
			}
			fireBall_Collider2 = App->collisions->AddCollider({ 0,0,20,20 }, Collider::Type::BOSS_PROYECTILE2, this);
			timeContador2 = 0;
			firstParticle2 = false;
		}

	}
	else {
		if (!firstParticle2 && timeContador2 < (aux - aux / 4)) {
			currentParticlePosition2.x += currentParticleDirection2.x;
			currentParticlePosition2.y += currentParticleDirection2.y;

			//cout << "x: " << currentParticleDirection2.x << " Y: " << currentParticleDirection2.y << endl;

			current_torso_Animation = &torso_AttackAnim;


			//Y
			if (App->player->position.y - App->player->currentAnimation->GetCurrentFrame().h > App->particlesBoss->GetPositionParticle(fireBallParticle2).y) {
				currentParticleDirection2.y = min(currentParticleDirection2.y + particleAdjustmen2, particleSpeed2);
			}
			else if (App->player->position.y - App->player->currentAnimation->GetCurrentFrame().h < App->particlesBoss->GetPositionParticle(fireBallParticle2).y) {
				currentParticleDirection2.y = max(currentParticleDirection2.y - particleAdjustmen2, -particleSpeed2);
			}


			//X
			if (App->player->position.x > App->particlesBoss->GetPositionParticle(fireBallParticle2).x) {

				currentParticleDirection2.x = min(currentParticleDirection2.x + particleAdjustmen2, particleSpeed2);
			}
			else if (App->player->position.x < App->particlesBoss->GetPositionParticle(fireBallParticle2).x) {

				currentParticleDirection2.x = max(currentParticleDirection2.x - particleAdjustmen2, -particleSpeed2);
			}

			fireBall_Collider2->SetPos(currentParticlePosition2.x + 5, currentParticlePosition2.y + 5);
			int ran = rand() % 3;
			switch (ran) {
			case 0:
				fireBallParticle2 = App->particlesBoss->AddParticle(App->particlesBoss->fireBall1, currentParticlePosition2.x, currentParticlePosition2.y);
				break;
			case 1:
				fireBallParticle2 = App->particlesBoss->AddParticle(App->particlesBoss->fireBall2, currentParticlePosition2.x, currentParticlePosition2.y);
				break;
			case 2:
				fireBallParticle2 = App->particlesBoss->AddParticle(App->particlesBoss->fireBall3, currentParticlePosition2.x, currentParticlePosition2.y);
				break;
			}

		}
		else {
			if(fireBall_Collider2 != nullptr)
				fireBall_Collider2->pendingToDelete = true;
		}
	}


	
	
	//Movimiento di boss
	if (!stunned) {
		if (timeMovingContador >= (bossMovingTime)) {

			(App->player->position.x > position.x) ? facingRight = true : facingRight = false;

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
	}
	

	//Animacion ataque
	switch (attacking) {
			

		case 1:
			current_torso_Animation = &torso_AttackAnim1;
			break;
		case 2:
			current_torso_Animation = &torso_AttackAnim2;
			break;
		case 3:
			current_torso_Animation = &torso_AttackAnim3;
			break;

		default:
			current_torso_Animation = &torso_IdleAnim;
			break;
	}
	if (torso_AttackAnim1.HasFinished() || torso_AttackAnim2.HasFinished() || torso_AttackAnim3.HasFinished()) {
		attacking = -1;
		torso_AttackAnim1.Reset();
		torso_AttackAnim2.Reset();
		torso_AttackAnim3.Reset();
	}




	
	if (stunned || inmune) { //recibir damage
		if (stunnedTime > 0) {
			(facingRight && stunnedTime % 3 == 0) ? position.x-- : position.x++;
			current_head_Animation = &head_DamageAnim;
			current_torso_Animation = &torso_DamageAnim;
			current_legs_Animation = &legs_DamageAnim;
			stunnedTime--;
			App->audio->PlayFx(RecieveDamageFX);
		}
		else {
			stunned = false;
			head_DamageAnim.Reset();
			torso_DamageAnim.Reset();
			legs_DamageAnim.Reset();
			current_head_Animation->Reset();
		}
	}
	inmuneTime--;
	if (inmuneTime <= 0) {
		inmuneTime = TOTAL_INMUNE_TIME;
		stunnedTime = TOTAL_STUNNED_TIME;
		inmune = false;
	}
	


	current_head_Animation->Update();
	current_torso_Animation->Update();
	current_legs_Animation->Update();

	timeContador++;
	timeContador2++;
	timeMovingContador++;


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBoss::PostUpdate()
{
	SDL_Rect rectHead =  current_head_Animation->GetCurrentFrame();
	SDL_Rect rectTorso = current_torso_Animation->GetCurrentFrame();
	SDL_Rect rectLegs =  current_legs_Animation->GetCurrentFrame();
	

	if (!facingRight) {
		
		if (dead) {

			App->render->Blit(texture, position.x - 23, position.y - 5, SDL_FLIP_NONE, &rectHead);
			App->render->Blit(texture, position.x, position.y - 10, SDL_FLIP_NONE, &rectTorso);
			App->render->Blit(texture, position.x + 21, position.y - 25 + rectTorso.h, SDL_FLIP_NONE, &rectLegs);

			return update_status::UPDATE_CONTINUE;
		}

		App->render->Blit(texture, position.x + 21, position.y - 5, SDL_FLIP_NONE, &rectHead);
		App->render->Blit(texture, position.x, position.y-10, SDL_FLIP_NONE, &rectTorso);
		App->render->Blit(texture, position.x + 21, position.y-25 + rectTorso.h, SDL_FLIP_NONE, &rectLegs);
		
		head_Collider->SetPos(position.x + 26, position.y - 5);
		//torso_Collider->SetPos(position.x, position.y - 10);
		legs_Collider->SetPos(position.x + 20, position.y - 25 + rectTorso.h );
		
	}
	else {

		if (dead) {

			App->render->Blit(texture, position.x - 23, position.y - 5, SDL_FLIP_NONE, &rectHead);
			App->render->Blit(texture, position.x, position.y - 10, SDL_FLIP_NONE, &rectTorso);
			App->render->Blit(texture, position.x + 21, position.y - 25 + rectTorso.h, SDL_FLIP_NONE, &rectLegs);

			return update_status::UPDATE_CONTINUE;
		}


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

	if (c1 == head_Collider && c2->type == Collider::Type::PLAYER_SHOT && !inmune) {
		inmune = true;
		stunned = true;
		App->audio->PlayFx(RecieveDamageFX);
		life--;
		
		if (life <= 0) {//morir
			
			current_head_Animation = &generalDying;
			App->audio->PlayFx(Boss_DieFX);
			Mix_FadeOutMusic(10);
			//App->fade->FadeToBlack(App->activeModule, App->mapaV);
			dead = true;
		}
	}

	if (c1->type == Collider::Type::BOSS_PROYECTILE && c2->active && c2->type == Collider::Type::WALL) {
		if (c2->GetRect().y > c1->GetRect().y) {
			App->boss->currentParticleDirection.y *= -1;
		}
		else {
			App->boss->currentParticleDirection.x *= -1;
		}
		return;
	}
	if (c1->type == Collider::Type::BOSS_PROYECTILE2 && c2->active && c2->type == Collider::Type::WALL) {
		if (c2->GetRect().y > c1->GetRect().y) {
			App->boss->currentParticleDirection2.y *= -1;
		}
		else {
			App->boss->currentParticleDirection2.x *= -1;
		}
		return;
	}

}



