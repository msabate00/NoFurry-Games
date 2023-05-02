#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"

#include <iostream>
 
using namespace std;

Enemy::Enemy(int x, int y, bool secondFloor) : position(x, y)
{
	spawnPos = position;
	this->secondFloor = secondFloor;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{


	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
		collider->SetSize(currentAnim->GetCurrentFrame().w, currentAnim->GetCurrentFrame().h);
	}

}

void Enemy::Draw()
{
	
	if (currentAnim != nullptr) {
		
		App->render->Blit(texture, position.x, position.y, SDL_FLIP_NONE, &(currentAnim->GetCurrentFrame()));
	}
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT && !setHasReceivedDamage) {
		//c muere
		this->setHasReceivedDamage = true;
		App->audio->PlayFx(destroyedFx);
	}
	
}