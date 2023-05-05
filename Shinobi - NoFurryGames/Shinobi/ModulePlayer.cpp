#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level1_SecondFloor.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "Collider.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "Hostage.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_render.h"

#include <iostream>

using namespace std;

// Street Fighter reference at https://www.youtube.com/watch?v=OEhmUuehGOA

int frameContador = 0;

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	

	///////////////////////
	//    ANIMACIONES    //
	///////////////////////
	
	// idle animation
	idleAnim.PushBack({ 281, 112, 46, 60 });
	idleAnim.speed = 0.2f;

	// walk forward animation
	forwardAnim.PushBack({ 11, 112, 46, 60 });
	forwardAnim.PushBack({ 65, 112, 46, 60 });
	forwardAnim.PushBack({ 119, 112, 46, 60 });
	forwardAnim.PushBack({ 173, 112, 46, 60 });
	forwardAnim.PushBack({ 227, 112, 46, 60 });
	forwardAnim.PushBack({ 281, 112, 46, 60 });
	forwardAnim.speed = 0.17f;

	// crouched idle anim
	crouched_idleAnim.PushBack({ 270, 211, 51, 36 });
	crouched_idleAnim.speed = 0.2f;

	//crouched forward anim
	crouched_forwardAnim.PushBack({ 158, 211, 51, 36 });
	crouched_forwardAnim.PushBack({ 214, 211, 51, 36 });
	crouched_forwardAnim.PushBack({ 270, 211, 51, 36 });
	crouched_forwardAnim.speed = 0.1f;

	//crouched attack anim
	//crouched_AttackAnim.PushBack({ 661, 210, 52, 36 });
	crouched_AttackAnim.PushBack({ 744, 211, 51, 36 });
	crouched_AttackAnim.speed = 0.2f;
	crouched_AttackAnim.loop = false;

	//jump anim
	jumpAnim.PushBack({ 10, 357, 33, 58 });
	jumpAnim.PushBack({ 47, 357, 33, 58 });
	jumpAnim.PushBack({ 84, 357, 33, 58 });
	jumpAnim.speed = 0.035f;

	jumpAttackAnim.PushBack({ 190, 357, 49, 59 });
	jumpAttackAnim.PushBack({ 243, 357, 49, 59 });

	jumpAttackAnim.speed = 0.1f;
	jumpAttackAnim.loop = false;



	//attack shuriken Anim
	attack_shurikenAnim.PushBack({ 14, 267, 46, 60 });
	//attack_shurikenAnim.PushBack({ 84, 357, 33, 58 });
	//attack_shurikenAnim.PushBack({ 84, 357, 33, 58 });
	attack_shurikenAnim.speed = 0.1f;
	attack_shurikenAnim.loop = false;

	watching_UpAnimation.PushBack({120, 735, 47, 51});
	watching_DownAnimation.PushBack({ 303, 744, 39, 42 }); 


	
	bigJumpUpAnim.PushBack({ 171, 735, 47, 51 });
	bigJumpUpAnim.PushBack({ 222, 735, 47, 51 });
	bigJumpUpAnim.speed = 0.15f;
	bigJumpUpAnim.loop = false;

	bigJumpDownAnim.PushBack({ 346, 744, 39, 42 });
	bigJumpDownAnim.speed = 0.15f;
	bigJumpDownAnim.loop = false;


	DeathAnim.PushBack({ 67, 651, 41, 43 });
	DeathAnim.PushBack({ 112, 651, 41, 43 });
	DeathAnim.PushBack({ 157, 672, 72, 22 });
	DeathAnim.PushBack({ 233, 672, 72, 22 });
	DeathAnim.loop = false;


	DeathAnim.speed = 0.1f;



	
//Anim Pistola
	PistolaidleAnim.PushBack({ 485, 112, 35, 60 });
	PistolaidleAnim.speed = 0.2f;


	PistolaforwardAnim.PushBack({ 407, 112, 35, 60 });
	PistolaforwardAnim.PushBack({ 446, 112, 35, 60 });
	PistolaforwardAnim.PushBack({ 485, 112, 35, 60 });
	PistolaforwardAnim.PushBack({ 524, 112, 35, 60 });
	PistolaforwardAnim.PushBack({ 563, 112, 35, 60 });
	PistolaforwardAnim.PushBack({ 602, 112, 35, 60 });
	PistolaforwardAnim.speed = 0.1f;

	Pistolacrouched_idleAnim.PushBack({ 506, 210, 42, 36 });
	Pistolacrouched_idleAnim.speed = 0.2f;

	Pistolacrouched_forwardAnim.PushBack({ 329, 210, 49, 36 });
	Pistolacrouched_forwardAnim.PushBack({ 382, 210, 49, 36 });
	Pistolacrouched_forwardAnim.PushBack({ 435, 210, 49, 36 });
	Pistolacrouched_forwardAnim.speed = 0.1f;


	Pistolacrouched_AttackAnim.PushBack({ 506, 210, 42, 36 });
	Pistolacrouched_AttackAnim.speed = 0.2f;
	Pistolacrouched_AttackAnim.loop = false;


	PistolajumpAnim.PushBack({ 423, 357, 35, 58 });
	PistolajumpAnim.PushBack({ 462, 357, 35, 58 });
	PistolajumpAnim.PushBack({ 501, 357, 35, 58 });
	PistolajumpAnim.speed = 0.035f;

	PistolajumpAttackAnim.PushBack({ 672, 357, 43, 58 });
	PistolajumpAttackAnim.speed = 0.1f;
	PistolajumpAttackAnim.loop = false;

	PistolaattackAnim.PushBack({ 212, 268, 31, 57 });
	PistolaattackAnim.speed = 0.1f;
	PistolaattackAnim.loop = false;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;


	texture = App->textures->Load("Assets/Sprites/Player/Player.png"); // arcade version

	//collider = App->collisions->AddCollider({ 0,0,39,60 }, Collider::Type::PLAYER, this);
	
	///////////////////////
	//      SONIDOS      //
	///////////////////////
	saltarFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Jump.wav");
	saltarPlataformaFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Plataform_Jump.wav");
	efectoSaltoPlataformaFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Efecto_SaltoPlataforma.wav");
	ataqueFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Attack.wav");
	shurikenAtaqueFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Shuriken_Attack.wav");
	morirFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Die.wav");

	currentAnimation = &idleAnim;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);
	rangeCollider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER_RANGE, this);

	position.x = 100;
	position.y = FLOOR_LEVEL;

	currJumpForce = 0;
	destroyedCountdown = 120;

	isJumping = false;
	isChangingFloorF1 = false;
	isChangingFloorF2 = false;
	isAttacking = false;
	isCrouchedAttacking = false;

	facingRight = true;
	isSecondFloor = false;

	DeathAnim.Reset();
	currentAnimation = &idleAnim;
	

	return ret;
}

update_status ModulePlayer::Update()
{

	

	//Aplica la gravedad a su altura
	//position.y += GRAVITY;
	currJumpForce += -GRAVITY;
	float grav = GRAVITY;
	if (currJumpForce < -grav) {
		isJumping = true;
	}

	

	position.y -= currJumpForce;
	

	
	//Reset the currentAnimation back to idle before updating the logic
	if (!holdingGun) {
		currentAnimation = &idleAnim;
	}
	else {
		currentAnimation = &PistolaidleAnim;
	}

	

	if (destroyed) {
		//PLAY ANIMACION MORIR;


		currentAnimation = &DeathAnim;
		
		
		if (hasPlayedDeathSound == true) {
			App->audio->PlayFx(morirFX);
			hasPlayedDeathSound = false;
		}
		
		
		destroyedCountdown--;
		if (destroyedCountdown <= 0) 
		{
			if (App->scene_Level1->life_num <= 0) {
				App->fade->FadeToBlack((Module*)App->scene_Level1, (Module*)App->scene_MainMenu, 60);
			}
			else {
				App->fade->FadeToBlack((Module*)App->scene_Level1, (Module*)App->scene_Level1, 60);
			}
		}


		currentAnimation->Update();
		collider->SetPos(position.x + marginCollider, position.y - currentAnimation->GetCurrentFrame().h);
		collider->SetSize(currentAnimation->GetCurrentFrame().w - marginCollider * 2, currentAnimation->GetCurrentFrame().h);
		rangeCollider->SetPos(position.x - rangeLength, position.y - currentAnimation->GetCurrentFrame().h);
		rangeCollider->SetSize(currentAnimation->GetCurrentFrame().w + rangeLength * 2, currentAnimation->GetCurrentFrame().h);



		return update_status::UPDATE_CONTINUE;
	}


	//CAMBIANDO DE ALTURA
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN &&
		App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT &&
		!isJumping && !isChangingFloorF1 && !isChangingFloorF2 && position.y > 110 && App->scene_Level1->IsEnabled()) {
		

		App->audio->PlayFx(saltarPlataformaFX);
		App->audio->PlayFx(efectoSaltoPlataformaFX);
		currJumpForce = jumpForce * 1.6;
		currentAnimation = &bigJumpUpAnim;
		currentJumpAnim = &bigJumpUpAnim;
		isChangingFloorF1 = true;
		frameContador = 0;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN &&
		App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT &&
		!isJumping && !isChangingFloorF1 && !isChangingFloorF2 && position.y <= 110 && App->scene_Level1->IsEnabled()) {
		
		
		App->audio->PlayFx(saltarPlataformaFX);
		App->audio->PlayFx(efectoSaltoPlataformaFX);
		currJumpForce = jumpForce * 1.6;
		currentAnimation = &bigJumpDownAnim;
		currentJumpAnim = &bigJumpDownAnim;
		isChangingFloorF1 = true;
		frameContador = 0;

	}

	if (isChangingFloorF1 || isChangingFloorF2) {
		currentAnimation = currentJumpAnim;
		if (isChangingFloorF1) {
			
			position.y -= 0.5f;
			if (position.y <= 85) {
				isChangingFloorF1 = false;
				isChangingFloorF2 = true;
				currJumpForce = jumpForce / 2;
				//App->scene_Level1->secondFloor->active = !App->scene_Level1->secondFloor->active;
				//(App->scene_Level1_SecondFloor->IsEnabled()) ? App->scene_Level1_SecondFloor->Disable() : App->scene_Level1_SecondFloor->Enable();
				App->scene_Level1_SecondFloor->EnabledColliderForPlayer(!App->scene_Level1_SecondFloor->showFence);
				//App->scene_Level1_SecondFloor->Disable();
			}
		}
		if (isChangingFloorF2) {
			//currentAnimation = &bigJumpUpDownAnim;

			if (positionBefore.y == position.y && position.y >= 72) {
				isChangingFloorF2 = false;
			}

			positionBefore.y = position.y;
		}
		
		collider->SetPos(position.x + marginCollider, position.y - currentAnimation->GetCurrentFrame().h);
		collider->SetSize(currentAnimation->GetCurrentFrame().w - marginCollider * 2, currentAnimation->GetCurrentFrame().h);
		rangeCollider->SetPos(position.x - rangeLength, position.y - currentAnimation->GetCurrentFrame().h);
		rangeCollider->SetSize(currentAnimation->GetCurrentFrame().w + rangeLength * 2, currentAnimation->GetCurrentFrame().h);


		currentAnimation->Update();

		return update_status::UPDATE_CONTINUE;

	}



	

	if (isAttacking) {
		if (isJumping) {
			if (enemyInRange) {
				//ANIMACION DE ATAQUE KATANA EN EL AIRE, A LO MEJOR NO HACER
				currentAnimation = &jumpAttackAnim;
			}
			else if (!holdingGun) {
				currentAnimation = &jumpAttackAnim;
			}
			else 
			{
				currentAnimation = &PistolajumpAttackAnim;
			}
			

		}
		else {

			if (enemyInRange) {
				//ANIMACION DE ATAQUE KATANA HACER
				currentAnimation = &attack_shurikenAnim;

			}else if (!holdingGun) {
				currentAnimation = &attack_shurikenAnim;
			}
			else
			{
				currentAnimation = &PistolaattackAnim;
			}
			
		}

		
		if (currentAnimation->HasFinished()) {
			isAttacking = false;
			currentAnimation->Reset();
		}
		else {
			collider->SetPos(position.x + marginCollider, position.y - currentAnimation->GetCurrentFrame().h);
			collider->SetSize(currentAnimation->GetCurrentFrame().w - marginCollider * 2, currentAnimation->GetCurrentFrame().h);
			rangeCollider->SetPos(position.x - rangeLength, position.y - currentAnimation->GetCurrentFrame().h);
			rangeCollider->SetSize(currentAnimation->GetCurrentFrame().w + rangeLength * 2, currentAnimation->GetCurrentFrame().h);
			currentAnimation->Update();
			return update_status::UPDATE_CONTINUE;
		}
	}

	if (isCrouchedAttacking) {

		if (enemyInRange) {
			//ANIMACION DE ATAQUE KATANA HACER
			currentAnimation = &crouched_AttackAnim;

		}else if (!holdingGun) {
			currentAnimation = &crouched_AttackAnim;
		}else{
			currentAnimation = &Pistolacrouched_AttackAnim;
		}
		
		if (currentAnimation->HasFinished()) {
			isCrouchedAttacking = false;
			currentAnimation->Reset();
		}
		else {
			collider->SetPos(position.x + marginCollider, position.y - currentAnimation->GetCurrentFrame().h);
			collider->SetSize(currentAnimation->GetCurrentFrame().w - marginCollider * 2, currentAnimation->GetCurrentFrame().h);
			rangeCollider->SetPos(position.x - rangeLength, position.y - currentAnimation->GetCurrentFrame().h);
			rangeCollider->SetSize(currentAnimation->GetCurrentFrame().w + rangeLength * 2, currentAnimation->GetCurrentFrame().h);
			currentAnimation->Update();
			return update_status::UPDATE_CONTINUE;
		}
	}


	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT) {
		currentAnimation = &watching_UpAnimation;
	}

	//MOVERSE A LA DERECHA
	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		if (!holdingGun) {
			currentAnimation = &forwardAnim;
		}
		else {
			currentAnimation = &PistolaforwardAnim;
		}
		
		position.x += speed;
		facingRight = true;
	}

	//MOVERSE A LA IZQUIERDA
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		if (!holdingGun) {
			currentAnimation = &forwardAnim;
		}
		else {
			currentAnimation = &PistolaforwardAnim;
		}

		position.x -= speed;
		facingRight = false;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
		if (!holdingGun) {
			currentAnimation = &crouched_idleAnim;
		}
		else {
			currentAnimation = &Pistolacrouched_idleAnim;
		}

		if (position.y <= 110 && !holdingGun) {
			currentAnimation = &watching_DownAnimation;

		} else if (position.y <= 110 && holdingGun) {
			currentAnimation = &Pistolacrouched_idleAnim;
		}


		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT || App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {
			
			if (!holdingGun) {
				currentAnimation = &crouched_forwardAnim;
			}
			else {
				currentAnimation = &Pistolacrouched_forwardAnim;
			}
		}
	}

	

	//MECANICA DEL SALTO
	if (isJumping) {
		if (!holdingGun) {
			currentAnimation = &jumpAnim;
		}
		else {
			currentAnimation = &PistolajumpAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping) {
		App->audio->PlayFx(saltarFX);
		isJumping = true;
		currJumpForce = jumpForce;
		
		if (!holdingGun) {
			currentAnimation = &jumpAnim;
		}
		else {
			currentAnimation = &PistolajumpAnim;
		}

		

	}

	


	collider->SetPos(position.x+ marginCollider, position.y - currentAnimation->GetCurrentFrame().h);
	collider->SetSize(currentAnimation->GetCurrentFrame().w - marginCollider*2, currentAnimation->GetCurrentFrame().h);
	rangeCollider->SetPos(position.x - rangeLength, position.y - currentAnimation->GetCurrentFrame().h);
	rangeCollider->SetSize(currentAnimation->GetCurrentFrame().w + rangeLength*2, currentAnimation->GetCurrentFrame().h);


	//ATAQUE SHURIKEN
	if (App->input->keys[SDL_SCANCODE_J] == KEY_DOWN) {
		App->audio->PlayFx(shurikenAtaqueFX);

		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
			isCrouchedAttacking = true;
			App->audio->PlayFx(shurikenAtaqueFX);
		}
		else
		{
			isAttacking = true;
		}
		

		if (facingRight) {
			if (!holdingGun) {
				App->particles->AddParticle(App->particles->shurikenR, position.x + 46, position.y - currentAnimation->GetCurrentFrame().h + 12, Collider::Type::PLAYER_SHOT, 0);
			}
			else {
				App->particles->AddParticle(App->particles->bulletR, position.x + 46, position.y - currentAnimation->GetCurrentFrame().h + 12, Collider::Type::PLAYER_SHOT, 0);
			}
		}
		else {
			if (!holdingGun) {
				App->particles->AddParticle(App->particles->shurikenL, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, Collider::Type::PLAYER_SHOT, 0);
			}
			else {
				App->particles->AddParticle(App->particles->bulletL, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, Collider::Type::PLAYER_SHOT, 0);
			}
		}
	}



	if (App->input->keys[SDL_SCANCODE_R] == KEY_DOWN) {
		
		destroyed = true;

	}


	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN) {
		holdingGun = !holdingGun;
	}


	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{

	if ((App->player->position.x * SCREEN_SIZE) +
		App->player->currentAnimation->GetCurrentFrame().w / 2 >= App->render->camera.x + SCREEN_WIDTH / 2 * SCREEN_SIZE) {
		App->render->camera.x += App->player->speed * SCREEN_SIZE;
	}
	if ((App->player->position.x * SCREEN_SIZE) +
		App->player->currentAnimation->GetCurrentFrame().w / 2 <= App->render->camera.x + SCREEN_WIDTH / 4 * SCREEN_SIZE) {
		App->render->camera.x -= App->player->speed * SCREEN_SIZE;
	}


	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if(facingRight) {
		App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_NONE,&rect);
	}
	else {
		App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_HORIZONTAL,&rect);
	}


	
	
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	if (!c2->active) { return; }
	if (c1 == collider && c2->type == Collider::WALL)
	{
		//cout << " Caja x: " << c2->GetRect().x << " Caja y: " << c2->GetRect().y << " Caja w: " << c2->GetRect().w << " Posi x: " << position.x << " Posi y: " << position.y << " CurrJump: " << currJumpForce << endl;

		if(c2->GetRect().y <= 103){ 
		//ta arriba	
			isSecondFloor = true;
		}
		else {
			//ta abajo
			//App->scene_Level1->secondFloor->active = false;
			//App->scene_Level1_SecondFloor->Disable();
			App->scene_Level1_SecondFloor->EnabledColliderForPlayer(false);
			isSecondFloor = false;
		}
		
		if (c2->GetRect().x >= position.x && c2->GetRect().y+2 <= position.y) {
			//NO SE PUEDE MOVER PARA LA DERECHA
			position.x -= speed;
		}else
		if (c2->GetRect().x + c2->GetRect().w+1 >= position.x && c2->GetRect().y+2 <= position.y) {
			position.x += speed;
		}
		if (c2->GetRect().y+1 >= position.y + currJumpForce && currJumpForce<=0){ //COLISION arriba
			position.y = c2->GetRect().y+1;
			currJumpForce = 0;
			isJumping = false;
			jumpAnim.Reset();
			
		}	
	}

	if (c1 == collider && c2->type == Collider::Type::ENEMY && !destroyed)
	{

		for(uint i = 0; i<MAX_ENEMIES; i++){
		
			if (App->enemy->getEnemy(i) != nullptr && App->enemy->getEnemy(i)->GetCollider() == c2) {
				if (App->enemy->getEnemy(i)->secondFloor != isSecondFloor || App->enemy->getEnemy(i)->setHasReceivedDamage) {
					return;
				}
				else {
					break;
				}
				
			}
		
		}
		holdingGun = false;
		destroyed = true;
		App->scene_Level1->life_num--;
	}

	if (c1 == collider && c2->type == Collider::Type::CHANGE_LEVEL) {
	
		App->fade->FadeToBlack((Module*)App->scene_Level1, (Module*)App->scene_MainMenu, 60);

	}






	//Colision rango
	if (c1 == rangeCollider && c2->type == Collider::Type::ENEMY && (c2->GetRect().x > position.x && facingRight) || (c2->GetRect().x < position.x && !facingRight)) {

		enemyInRange = true;
	}
	else {
		enemyInRange = false;
	}




}

bool ModulePlayer::CleanUp() {

	
	

	collider->pendingToDelete = true;

	return true;
}