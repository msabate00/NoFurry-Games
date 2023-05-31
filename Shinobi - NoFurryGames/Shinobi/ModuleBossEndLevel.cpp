#include "ModuleBossEndLevel.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level2.h"
#include "ModuleScene_Level1_SecondFloor.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleParticlesBoss.h"
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
#include "ModuleBoss.h"

using namespace std;

ModuleBossEndLevel::ModuleBossEndLevel(bool startEnabled) : Module(startEnabled)
{


	
	idleAnim.PushBack({ 98, 750, 87, 92 });
	idleAnim.speed = 0.2f;

	attackAnim.PushBack({ 98, 750, 87, 92 });
	attackAnim.PushBack({ 5, 852, 87, 92 });
	attackAnim.PushBack({ 5, 852, 87, 92 });
	attackAnim.PushBack({ 5, 852, 87, 92 });
	attackAnim.PushBack({ 98, 750, 87, 92 });
	attackAnim.speed = 0.05f;
	attackAnim.loop = false;

	walkAnim.PushBack({298, 750, 87,92});
	walkAnim.PushBack({205, 750, 87, 92 });
	walkAnim.PushBack({ 298, 750, 87, 92 });
	walkAnim.PushBack({391, 750, 87, 92 });




	walkAnim.speed = 0.05f;


}

ModuleBossEndLevel::~ModuleBossEndLevel()
{

}

bool ModuleBossEndLevel::Start()
{
	LOG("Loading player textures");

	bool ret = true;


	texture = App->textures->Load("Assets/Sprites/Boss1/SpriteSheet_Boss1.png");

	//collider = App->collisions->AddCollider({ 0,0,39,60 }, Collider::Type::PLAYER, this);

	BoladeFuegoFX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Fire_Boss.wav");
	currentParticleDirection = fPoint(-2, 0);
	currentParticlePosition = fPoint(0, 0);

	currentAnimation = &idleAnim;
	triggered = false;
	facingRight = false;
	timeContador = 0;
	fireBallParticle = -1;
	position.y = SCREEN_HEIGHT - 9;

	idleAnim.Reset();
	attackAnim.Reset();
	walkAnim.Reset();

	bossWall = App->collisions->AddCollider({ 30,30,20,20 }, Collider::Type::WALL, this);

	return ret;
}

update_status ModuleBossEndLevel::Update()
{
	if (!triggered) {
		currentAnimation = &idleAnim;
	}
	if (App->player->position.x - position.x > -150 && !triggered) {
		triggered = true;
		firstParticle = true;
		SpawnFireball();
		//lanzar bola di fogo
		currentAnimation = &attackAnim;

	}

	if (triggered) {

		if (attackAnim.HasFinished()) {
			facingRight = true;
			currentAnimation = &walkAnim;
			position.x++;
		}
		else {
			currentAnimation = &attackAnim;
		}
		SpawnFireball();
	}


	timeContador++;


	bossWall->SetPos(position.x+30, position.y- currentAnimation->GetCurrentFrame().h);
	bossWall->SetSize(30, currentAnimation->GetCurrentFrame().h);
	

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;


}

update_status ModuleBossEndLevel::PostUpdate()
{


	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if (!facingRight) {
		App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_NONE, &rect);
	}
	else {
		App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_HORIZONTAL, &rect);
	}

	


	return update_status::UPDATE_CONTINUE;
}

void ModuleBossEndLevel::OnCollision(Collider* c1, Collider* c2)
{

	
	if (c1->type == Collider::Type::BOSS_PROYECTILE && c2->active && c2->type == Collider::Type::WALL && c2 != bossWall) {
		if (c2->GetRect().y > c1->GetRect().y) {
			currentParticleDirection.y *= -1;
			
		}
		else {
			currentParticleDirection.x *= -1;
			
		}
		return;
	}
	

}

bool ModuleBossEndLevel::CleanUp() {

	

	return true;
}

void ModuleBossEndLevel::SpawnFireball() {

	//BOLA DI FOGO 1
	int aux = BOSS_PARTICLE_DURATION;
	//App->audio->PlayFx(BoladeFuegoFX);
	if (firstParticle) {

		
		if (firstParticle) {
			currentParticlePosition = fPoint(position.x, position.y - currentAnimation->GetCurrentFrame().h/2);
			currentParticleDirection.x = -particleSpeed;
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
		if (!firstParticle && timeContador < (aux - aux / 4)) {
			currentParticlePosition.x += currentParticleDirection.x;
			currentParticlePosition.y += currentParticleDirection.y;

			

			


			//Y
			if (App->player->position.y - App->player->currentAnimation->GetCurrentFrame().h > App->particlesBoss->GetPositionParticle(fireBallParticle).y) {
				currentParticleDirection.y = min(currentParticleDirection.y + particleAdjustmen, particleSpeed);
			}
			else if (App->player->position.y - App->player->currentAnimation->GetCurrentFrame().h < App->particlesBoss->GetPositionParticle(fireBallParticle).y) {
				currentParticleDirection.y = max(currentParticleDirection.y - particleAdjustmen, -particleSpeed);
			}


			//X
			if (App->player->position.x > App->particlesBoss->GetPositionParticle(fireBallParticle).x) {

				currentParticleDirection.x = min(currentParticleDirection.x + particleAdjustmen, particleSpeed);
			}
			else if (App->player->position.x < App->particlesBoss->GetPositionParticle(fireBallParticle).x) {

				currentParticleDirection.x = max(currentParticleDirection.x - particleAdjustmen, -particleSpeed);
			}

			fireBall_Collider->SetPos(currentParticlePosition.x + 5, currentParticlePosition.y + 5);
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

}