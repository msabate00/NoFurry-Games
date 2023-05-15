#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleScene_Level1.h"
#include "ModuleInterface.h"

#include <iostream>
 
using namespace std;

Enemy::Enemy(int x, int y, bool secondFloor, ENEMY_TYPE type) : position(x, y)
{
	spawnPos = position;
	this->secondFloor = secondFloor;
	this->type = type;
	


	collider = App->collisions->AddCollider({ 0, 0, 35, 64 }, Collider::Type::ENEMY, (Module*)App->enemy);
	colliderRange = App->collisions->AddCollider({ 0, 0, 35, 64 }, Collider::Type::ENEMY_RANGE, (Module*)App->enemy);

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

const Collider* Enemy::GetColliderRange() const
{
	return colliderRange;
}

void Enemy::Update()
{

	if (!jumpsNow)
	{
		currentAnim = &walkBasic;
	}
	else currentAnim = &jumping;
		
	if (currentAnim->HasFinished())
	{
		jumpsNow = false;
	}



	if (setHasReceivedDamage)
	{
		if (!moveToDie)
		{
			diePos = { position.x, position.y + currentAnim->GetCurrentFrame().h };
			App->interface_module->texture_num += this->points;
			moveToDie = true;
		}
		currentAnim = &Death;
		position.y = diePos.y - currentAnim->GetCurrentFrame().h;

		if (currentAnim->HasFinished())
		{
			
			currentAnim = nullptr;
			
			if (collider != nullptr)
				collider->pendingToDelete = true;

			if (colliderRange != nullptr)
				colliderRange->pendingToDelete = true;

			App->enemy->AddEnemy(this->type, this->spawnPos.x, this->spawnPos.y, this->secondFloor);
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
	if (colliderRange != nullptr) {
		colliderRange->SetPos(position.x- attackRange, position.y);
		colliderRange->SetSize(currentAnim->GetCurrentFrame().w+ attackRange*2, currentAnim->GetCurrentFrame().h);
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

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	//Si no es de la segunda planta, y la colision esta inactiva, y es de tipo wall, ignora la colision
	if (!secondFloor && !c2->active && c2->type == Collider::Type::WALL) { return;  }

	if (c2->type == Collider::Type::PLAYER_SHOT && !setHasReceivedDamage) 
	{
		//c muere
		this->setHasReceivedDamage = true;
		App->audio->PlayFx(destroyedFx);
	}
		

	//Colisiona con la pre-caja, para saltar
	if (c2->type == Collider::Type::BOX_HELP) 
	{
		if (facingLeft || currentAnim == &walkBasic)
		{
			jumpsNow = true;
			position.y -= 4;
		}
	}
	if (c2->type == Collider::Type::BOX_HELP_RIGHT)
	{
		if (!facingLeft || currentAnim == &walkBasic)
		{
			jumpsNow = true;
			position.y -= 6;
		}
	}
	

	//Colisiona con pared, caja, suelo
	if (c2->type == Collider::Type::WALL) {
		
		if (c2->GetRect().x >= position.x && c2->GetRect().y + jumpSpeed + 2 <= position.y)
		{
			//NO SE PUEDE MOVER PARA LA DERECHA

			position.x -= speed;
		}
		else if (c2->GetRect().x + c2->GetRect().w  >= position.x && c2->GetRect().y+2 <= position.y + currentAnim->GetCurrentFrame().h + jumpSpeed) 
		{
		
			position.x += speed;
			
		}



		if (c2->GetRect().y >= position.y + currentAnim->GetCurrentFrame().h - 2 + jumpSpeed && jumpSpeed <= 0) {
			position.y = c2->GetRect().y - currentAnim->GetCurrentFrame().h + 1;
			jumpSpeed = 0;
			isJumping = false;
		}

		//if (c2->GetRect().y <= position.y + currentAnim->GetCurrentFrame().h + jumpSpeed && jumpSpeed <= 0) {
		//	position.y = c2->GetRect().y - currentAnim->GetCurrentFrame().h+1;
		//	jumpSpeed = 0;
		//	isJumping = false;
		//	
		//	cout << c2->GetRect().y << " p: " << position.y<< " cf: " << currentAnim->GetCurrentFrame().h << endl;
		//	//jumpAnim.Reset();

		//}
		//else {
		//	//cout << "aaaa" << endl;
		//}
	}

	 
	if (c1 == colliderRange && !isAttacking) {
		isAttacking = true;

		(facingLeft) ? position.x += 1 : position.x -= 1;

		
	}
	
	
	/*
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
	*/
}