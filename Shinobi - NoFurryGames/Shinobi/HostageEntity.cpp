#include "HostageEntity.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleHostage.h"
#include "ModuleScene_Level1.h"
#include "ModuleInterface.h"

#include <iostream>

using namespace std;

HostageEntity::HostageEntity(int x, int y, bool secondFloor, HOSTAGE_TYPE type) : position(x, y)
{
	spawnPos = position;
	this->secondFloor = secondFloor;
	this->type = type;



	//collider = App->collisions->AddCollider({ 0, 0, 35, 64 }, Collider::Type::HOSTAGE, (Module*)App->hostages);
}

HostageEntity::~HostageEntity()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;

}

const Collider* HostageEntity::GetCollider() const
{
	return collider;
}



void HostageEntity::Update()
{
	if (!isAttacking && !isJumping)
	{
		currentAnim = &walkBasic;
	}

	if (saved) {
		currentAnim = &Death;
	}
	

	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr) {
		collider->SetPos(position.x, position.y);
		collider->SetSize(currentAnim->GetCurrentFrame().w, currentAnim->GetCurrentFrame().h);
	}

}

void HostageEntity::Draw()
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

void HostageEntity::OnCollision(Collider* c1, Collider* c2)
{
	//Si no es de la segunda planta, y la colision esta inactiva, y es de tipo wall, ignora la colision
	if (!secondFloor && !c2->active && c2->type == Collider::Type::WALL) { return; }


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
		else if (c2->GetRect().x + c2->GetRect().w >= position.x && c2->GetRect().y + 2 <= position.y + currentAnim->GetCurrentFrame().h + jumpSpeed)
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

	if (c2->type == Collider::Type::PLAYER_RANGE)
	{
		isAttacking = true;
		(facingLeft) ? position.x -= 1 : position.x += 1;
	}


	/*else
	{
		(facingLeft) ? position.x -= 1 : position.x += 1;
		!isAttacking;
	}*/


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