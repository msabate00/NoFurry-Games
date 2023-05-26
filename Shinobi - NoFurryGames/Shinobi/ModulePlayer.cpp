#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level2.h"
#include "ModuleScene_Level1_SecondFloor.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleMapa2.h"
#include "ModuleAudio.h"
#include "Collider.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemies.h"
#include "ModuleBoss.h"
#include "Hostage.h"
#include "Enemy.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_render.h"

#include <iostream>

using namespace std;



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

	//Espada

	PatadaAnim.PushBack({ 375, 656, 44, 37 });
	PatadaAnim.PushBack({ 427, 654, 65, 39 });
	PatadaAnim.PushBack({ 375, 656, 44, 37 });
	PatadaAnim.speed = 0.2f;
	PatadaAnim.loop = false;

	EspadaCrouchAnim.PushBack({ 10, 825, 69, 51 });
	EspadaCrouchAnim.PushBack({ 85, 825, 69, 51 });
	EspadaCrouchAnim.PushBack({ 160, 825, 69, 51 });
	EspadaCrouchAnim.PushBack({ 235, 825, 69, 51 });
	EspadaCrouchAnim.PushBack({ 310, 825, 69, 51 });
	EspadaCrouchAnim.PushBack({ 385, 825, 69, 51 });
	EspadaCrouchAnim.PushBack({ 460, 825, 69, 51 });
	EspadaCrouchAnim.speed = 0.5f;
	EspadaCrouchAnim.loop = false;

	EspadaAnim.PushBack({ 10, 916, 67, 63 });
	EspadaAnim.PushBack({ 83, 916, 67, 63 });
	EspadaAnim.PushBack({ 156, 916, 67, 63 });
	EspadaAnim.PushBack({ 229, 916, 67, 63 });
	EspadaAnim.PushBack({ 302, 916, 67, 63 });
	EspadaAnim.PushBack({ 375, 916, 67, 63 });
	EspadaAnim.PushBack({ 448, 916, 67, 63 });
	EspadaAnim.PushBack({ 521, 916, 67, 63 });
	EspadaAnim.speed = 0.5f;
	EspadaAnim.loop = false;

	

	PatadaSaltoAnim.PushBack({ 11, 449, 29, 49 });
	PatadaSaltoAnim.PushBack({ 44, 460, 45, 38 });
	PatadaSaltoAnim.PushBack({ 93, 467, 75, 38 });
	PatadaSaltoAnim.PushBack({ 172, 460, 45, 38 });
	PatadaSaltoAnim.PushBack({ 221, 449, 29, 49 });
	PatadaSaltoAnim.PushBack({ 254, 439, 34, 59 });
	
	PatadaSaltoAnim.speed = 0.2f;
	PatadaSaltoAnim.loop = false;

	

	PatadaKatanaAnim.PushBack({ 14, 543, 39, 58 });
	PatadaKatanaAnim.PushBack({ 57, 543, 39, 58 });
	PatadaKatanaAnim.PushBack({ 100, 537, 40, 64 });
	PatadaKatanaAnim.PushBack({ 144, 540, 51, 61 });
	PatadaKatanaAnim.PushBack({ 199, 552, 62, 49 });
	PatadaKatanaAnim.PushBack({ 265, 543, 39, 58 });
	PatadaKatanaAnim.PushBack({ 308, 543, 39, 58 });
	PatadaKatanaAnim.PushBack({ 351, 543, 39, 58 });
	PatadaKatanaAnim.PushBack({ 394, 543, 39, 58 });
	PatadaKatanaAnim.PushBack({ 437, 543, 39, 58 });

	PatadaKatanaAnim.speed = 0.2f;
	PatadaKatanaAnim.loop = false;


	
	ultiEspadaAnim.PushBack({ 10, 1106, 30, 62 });
	ultiEspadaAnim.PushBack({ 10, 1106, 30, 62 });
	ultiEspadaAnim.speed = 0.025f;
	ultiEspadaAnim.loop = false;

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

	collider = App->collisions->AddCollider({ (int)position.x, (int)position.y, 32, 16 }, Collider::Type::PLAYER, this);
	rangeCollider = App->collisions->AddCollider({ (int)position.x, (int)position.y, 32, 16 }, Collider::Type::PLAYER_RANGE, this);

	position.x = 100;
	position.y = FLOOR_LEVEL;

	currJumpForce = 0;
	destroyedCountdown = 120;

	isJumping = false;
	isChangingFloorF1 = false;
	isChangingFloorF2 = false;
	isAttacking = false;
	isCrouchedAttacking = false;
	isUlti = false;
	facingRight = true;
	isSecondFloor = false;
	gameOver = false;
	isChangingZone = false;
	holdingGun = false;
	haveUlti = true;

	DeathAnim.Reset();
	currentAnimation = &idleAnim;
	sumaPoint = true;


	return ret;
}

update_status ModulePlayer::Update()
{

	
	if (gameOver) {
		timerGameover += App->deltaTime;
		//cout << timerGameover << endl;
		if (timerGameover >= 3000) {
			App->interface_module->coinNum = 0;
			App->interface_module->gameover = false;
		App->fade->FadeToBlack((Module*)App->activeModule, (Module*)App->scene_MainMenu, 20);
		}
	}
	if (isChangingZone) {
		inmune = true;

		currentAnimation = &idleAnim;

		collider->SetPos(position.x + marginCollider, position.y - currentAnimation->GetCurrentFrame().h);
		collider->SetSize(currentAnimation->GetCurrentFrame().w - marginCollider * 2, currentAnimation->GetCurrentFrame().h);
		rangeCollider->SetPos(position.x - rangeLength, position.y - currentAnimation->GetCurrentFrame().h);
		rangeCollider->SetSize(currentAnimation->GetCurrentFrame().w + rangeLength * 2, currentAnimation->GetCurrentFrame().h);

		currentAnimation->Update();

		return update_status::UPDATE_CONTINUE;
	}


	//Aplica la gravedad a su altura
	//position.y += GRAVITY;
	currJumpForce += -GRAVITY;
	float grav = GRAVITY;
	if (currJumpForce < -grav) {
		isJumping = true;
	}
	position.y -= currJumpForce;
	

	if (isUlti) {

		inmune = true;
		currentAnimation = &ultiEspadaAnim;
		
		/*App->particles->AddParticle(App->particles->ulti, position.x - 30, position.y - currentAnimation->GetCurrentFrame().h, Collider::Type::NONE, 0);*/


		if (ultiEspadaAnim.HasFinished()) {

			/*App->particles->AddParticle(App->particles->ultiEspada, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, fPoint(10, -10), Collider::Type::PLAYER_SWORD_ULTI, 0);
			App->particles->AddParticle(App->particles->ultiEspada, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, fPoint(0, -10), Collider::Type::PLAYER_SWORD_ULTI, 0);
			App->particles->AddParticle(App->particles->ultiEspada, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, fPoint(-10, -10), Collider::Type::PLAYER_SWORD_ULTI, 0);
			App->particles->AddParticle(App->particles->ultiEspada, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, fPoint(5, -10), Collider::Type::PLAYER_SWORD_ULTI, 0);
			App->particles->AddParticle(App->particles->ultiEspada, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, fPoint(-5, -10), Collider::Type::PLAYER_SWORD_ULTI, 0);
			App->particles->AddParticle(App->particles->ultiEspada, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, fPoint(15, -10), Collider::Type::PLAYER_SWORD_ULTI, 0);
			App->particles->AddParticle(App->particles->ultiEspada, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, fPoint(-15, -10), Collider::Type::PLAYER_SWORD_ULTI, 0);
			App->particles->AddParticle(App->particles->ultiEspada, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, fPoint(-15, -5), Collider::Type::PLAYER_SWORD_ULTI, 0);
			App->particles->AddParticle(App->particles->ultiEspada, position.x, position.y - currentAnimation->GetCurrentFrame().h + 12, fPoint(15, -5), Collider::Type::PLAYER_SWORD_ULTI, 0);
			*/
			App->particles->AddParticle(App->particles->ultiTornado, position.x, 10, fPoint(0, 0), Collider::Type::PLAYER_SWORD_ULTI, 0);
			
			if (!App->boss->IsEnabled()) {
				App->enemy->KillAll();
			}
			else {
				App->boss->life -= 2;
			}

			
		}

		if (ultiEspadaAnim.HasFinished()) {
			isUlti = false;
			inmune = false;
			currentAnimation->Reset();
			
		}
		currentAnimation->Update();

		collider->SetPos(position.x + marginCollider, position.y - currentAnimation->GetCurrentFrame().h);
		collider->SetSize(currentAnimation->GetCurrentFrame().w - marginCollider * 2, currentAnimation->GetCurrentFrame().h);
		rangeCollider->SetPos(position.x - rangeLength, position.y - currentAnimation->GetCurrentFrame().h);
		rangeCollider->SetSize(currentAnimation->GetCurrentFrame().w + rangeLength * 2, currentAnimation->GetCurrentFrame().h);

		return update_status::UPDATE_CONTINUE;
	}

	
	
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
			if (App->life_num <= 0) {
				App->interface_module->gameover = true;
				gameOver = true;
			}
			else {
				App->fade->FadeToBlack((Module*)App->activeModule, (Module*)App->activeModule, 20);
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
			if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {
				position.x += speed;
				facingRight = true;
			}
			else if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {
				position.x -= speed;
				facingRight = false;
			}
			

		}
		else {

			if (enemyInRange) {
				//ANIMACION DE ATAQUE KATANA HACER
				currentAnimation = &EspadaAnim;
				inmune = true;

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
			inmune = false;
			currentAnimation->Reset();
			currentAnimation = &idleAnim;
			collider->SetPos(position.x + marginCollider, position.y - currentAnimation->GetCurrentFrame().h);
			collider->SetSize(currentAnimation->GetCurrentFrame().w - marginCollider * 2, currentAnimation->GetCurrentFrame().h);
			rangeCollider->SetPos(position.x - rangeLength, position.y - currentAnimation->GetCurrentFrame().h);
			rangeCollider->SetSize(currentAnimation->GetCurrentFrame().w + rangeLength * 2, currentAnimation->GetCurrentFrame().h);
			currentAnimation->Update();
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

		if (enemyInRange && !holdingGun) {
			//ANIMACION DE ATAQUE KATANA HACER

			
			inmune = true;
			currentAnimation = &PatadaAnim;

		}
		else if (enemyInRange && holdingGun) {
			currentAnimation = &EspadaCrouchAnim;

		}
		else if (!holdingGun) {
				currentAnimation = &crouched_AttackAnim;
		}else{
			currentAnimation = &Pistolacrouched_AttackAnim;
		}
		
		if (currentAnimation->HasFinished()) {
			isCrouchedAttacking = false;
			inmune = false;
			currentAnimation->Reset();
			currentAnimation = &idleAnim;
			collider->SetPos(position.x + marginCollider, position.y - currentAnimation->GetCurrentFrame().h);
			collider->SetSize(currentAnimation->GetCurrentFrame().w - marginCollider * 2, currentAnimation->GetCurrentFrame().h);
			rangeCollider->SetPos(position.x - rangeLength, position.y - currentAnimation->GetCurrentFrame().h);
			rangeCollider->SetSize(currentAnimation->GetCurrentFrame().w + rangeLength * 2, currentAnimation->GetCurrentFrame().h);
			currentAnimation->Update();
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
			if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT) {
				position.x -= crouchedSpeed;
			}
			else {
				position.x += crouchedSpeed;
			}
		}
	}

	
	//ULTI
	if (App->input->keys[SDL_SCANCODE_K] == KEY_DOWN && haveUlti)
	{
		if (!isUlti) {
			App->particles->AddParticle(App->particles->ulti, position.x - 30, position.y - currentAnimation->GetCurrentFrame().h, Collider::Type::NONE, 0);
			haveUlti = false;

		}
		isUlti = true;

		
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
		App->interface_module->spacePoint = false;
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

		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
			App->render->camera.x += App->player->crouchedSpeed * SCREEN_SIZE;
		}
		else {
			App->render->camera.x += App->player->speed * SCREEN_SIZE;
		}

		
	}
	if ((App->player->position.x * SCREEN_SIZE) +
		App->player->currentAnimation->GetCurrentFrame().w / 2 <= App->render->camera.x + SCREEN_WIDTH / 4 * SCREEN_SIZE) {

		if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
			App->render->camera.x -= App->player->crouchedSpeed * SCREEN_SIZE;
		}
		else {
			App->render->camera.x -= App->player->speed * SCREEN_SIZE;
		}
	}


	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if(facingRight) {
		App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_NONE,&rect);
	}
	else {
		App->render->Blit(texture, position.x, position.y - rect.h, SDL_FLIP_HORIZONTAL,&rect);
	}


	




	//App->fonts->BlitText(SCREEN_WIDTH - 275, SCREEN_HEIGHT - 50, scoreFont, "hola marti xd 123");
	
	
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	if (!c2->active) { return; }
	if (c1 == collider && c2->type == Collider::WALL)
	{
		if(c2->GetRect().y <= 103){ 
		//ta arriba	
			isSecondFloor = true;
			
		}
		else {
			//ta abajo
			if (App->scene_Level1->IsEnabled()) {
				App->scene_Level1_SecondFloor->EnabledColliderForPlayer(false);
				isSecondFloor = false;
			}
			else if (App->scene_Level2->IsEnabled()){
				isSecondFloor = false;
			}
		}
		
		if (c2->GetRect().x >= position.x && c2->GetRect().y+2 <= position.y) {
			//NO SE PUEDE MOVER PARA LA DERECHA
			position.x -= speed;
		}else if (c2->GetRect().x + c2->GetRect().w+1 >= position.x && c2->GetRect().y+2 <= position.y) {
			//NO SE PUEDE MOVER PARA LA IZQUIERDA
			position.x += speed;
		}
		if (c2->GetRect().y+1 >= position.y + currJumpForce && currJumpForce<=0){ //COLISION arriba
			position.y = c2->GetRect().y+1;
			currJumpForce = 0;
			isJumping = false;
			jumpAnim.Reset();
			
		}	
	}

	if (c1 == collider && (c2->type == Collider::Type::ENEMY || c2->type == Collider::Type::BOSS_PROYECTILE) && !destroyed && !inmune && !App->godMode)
	{

		if (c2->type == Collider::Type::ENEMY) {
			for (uint i = 0; i < MAX_ENEMIES; i++) {

				if (App->enemy->getEnemy(i) != nullptr && App->enemy->getEnemy(i)->GetCollider() == c2) {
					if (App->enemy->getEnemy(i)->secondFloor != isSecondFloor || App->enemy->getEnemy(i)->setHasReceivedDamage) {
						return;
					}
					else {
						break;
					}

				}

			}
		}
		holdingGun = false;
		destroyed = true;
		App->life_num--;
	}

	if (c1 == collider && c2->type == Collider::Type::CHANGE_LEVEL) {

		isChangingZone = true;
		
		if ((Module*)App->scene_Level1->IsEnabled()) {
			timerChangeLv2 += App->deltaTime;
			App->interface_module->gameChange = false;

			if (timerChangeLv2 <= 20 && sumaPoint) {
				cout << "lv1" << endl;
				if (haveUlti) {
				App->interface_module->texture_num += 5000;
				}
				if (App->interface_module->spacePoint) {
					App->interface_module->texture_num += 20000;
				}
				sumaPoint = false;
			}
			if (timerChangeLv2 >= 5000 || App->interface_module->remaining_time <= 0) {
				App->interface_module->gameChange = true;
				App->fade->FadeToBlack((Module*)App->scene_Level1, (Module*)App->mapa2, 2);
				timerChangeLv2 = 0;
			}
		}

		if ((Module*)App->scene_Level2->IsEnabled()) {
			timerChangeLv2 += App->deltaTime;
			App->interface_module->gameChange = false;
			
			if (timerChangeLv2 <= 20 && sumaPoint) {
				cout << "lv2" << endl;
				if (haveUlti) {
					App->interface_module->texture_num += 5000;
				}
				if (App->interface_module->spacePoint) {
					App->interface_module->texture_num += 20000;
				}
				sumaPoint = false;
			}
			if (timerChangeLv2 >= 5000 || App->interface_module->remaining_time <= 0) {
				App->interface_module->gameChange = true;
				App->fade->FadeToBlack((Module*)App->scene_Level2, (Module*)App->mapa3, 2);
				timerChangeLv2 = 0;
			}
		}
		
	}




	//Colision rango
	//if (c1 == rangeCollider && c2->type == Collider::Type::ENEMY && (c2->GetRect().x > position.x && facingRight) || (c2->GetRect().x < position.x && !facingRight)) {
	if (c1 == rangeCollider && c2->type == Collider::Type::ENEMY) {

		if (c2->GetRect().x > position.x && facingRight) {
			enemyInRange = true;
		}
		else if (c2->GetRect().x < position.x && !facingRight) {
			enemyInRange = true;
		}
		
	}
	else {
		enemyInRange = false;
	}




}

bool ModulePlayer::CleanUp() {

	collider->pendingToDelete = true;

	return true;
}