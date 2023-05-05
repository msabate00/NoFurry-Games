#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleScene_Level1.h"

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

	if (setHasReceivedDamage)
	{
		if (!moveToDie)
		{
			diePos = { position.x, position.y + currentAnim->GetCurrentFrame().h };
			App->scene_Level1->texture_num += this->points;
			moveToDie = true;
		}
		currentAnim = &Death;
		position.y = diePos.y - currentAnim->GetCurrentFrame().h;

		if (currentAnim->HasFinished())
		{
			
			currentAnim = nullptr;
			App->enemy->HandleEnemiesDespawnEnemy(this);
			return;
		}
	}

	if (boxCollision)
	{
		if (currentAnim->HasFinished())
		{
			currentAnim = &walkBasic;
			position.y += 0;
		}
	}

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
		collider->SetSize(currentAnim->GetCurrentFrame().w, currentAnim->GetCurrentFrame().h);
	}

}

void Enemy::Draw()
{
	
	/*if (currentAnim != nullptr) 
	{
		
		App->render->Blit(texture, position.x, position.y, SDL_FLIP_NONE, &(currentAnim->GetCurrentFrame()));
	}*/

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	if (facingLeft)
	{
		App->render->Blit(texture, position.x, position.y, SDL_FLIP_NONE, &rect);
	}
	else
	{
		App->render->Blit(texture, position.x, position.y, SDL_FLIP_HORIZONTAL, &rect);
	}


}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT && !setHasReceivedDamage) {
		//c muere
		this->setHasReceivedDamage = true;
		App->audio->PlayFx(destroyedFx);
	}
		
	if (collider->type == Collider::Type::WALL && !collidesWithWall) 
	{
		//Cambia de sentido (derecha)
		this->collidesWithWall = true;
	}
	if (collider->type == Collider::Type::WALL && collidesWithWall)
	{
		//Cambia de sentido (izquierda)
		this->collidesWithWall = false;
	}
	
}