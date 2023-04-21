#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_render.h"

#include <iostream>

using namespace std;

// Street Fighter reference at https://www.youtube.com/watch?v=OEhmUuehGOA

int frameContador = 0;

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = FLOOR_LEVEL;

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
	forwardAnim.speed = 0.1f;

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

	//attack shuriken Anim
	attack_shurikenAnim.PushBack({ 14, 267, 46, 60 });
	//attack_shurikenAnim.PushBack({ 84, 357, 33, 58 });
	//attack_shurikenAnim.PushBack({ 84, 357, 33, 58 });
	attack_shurikenAnim.speed = 0.1f;
	attack_shurikenAnim.loop = false;

	watching_UpAnimation.PushBack({120, 735, 47, 51});


	
	bigJumpUpUpAnim.PushBack({ 171, 735, 47, 51 });
	bigJumpUpUpAnim.PushBack({ 222, 735, 47, 51 });

	bigJumpUpUpAnim.speed = 0.15f;
	bigJumpUpUpAnim.loop = false;

	

	bigJumpDownUpAnim.PushBack({ 303, 744, 39, 42 });
	bigJumpDownUpAnim.PushBack({ 346, 744, 39, 42 });

	bigJumpDownUpAnim.speed = 0.15f;
	bigJumpDownUpAnim.loop = false;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;


	texture = App->textures->Load("Assets/Sprites/Player/Player.png"); // arcade version

	collider = App->collisions->AddCollider({ 0,0,39,60 }, Collider::Type::PLAYER, this);
	
	///////////////////////
	//      SONIDOS      //
	///////////////////////
	saltarFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Jump.wav");
	saltarPlataformaFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Plataform_Jump.wav");
	ataqueFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Attack.wav");
	shurikenAtaqueFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Shuriken_Attack.wav");
	morirFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Die.wav");
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

	//cout << currJumpForce << endl;

	position.y -= currJumpForce;
	

	//Reset the currentAnimation back to idle before updating the logic
	currentAnimation = &idleAnim;





	//CAMBIANDO DE ALTURA
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && !isJumping && !isChangingFloorF1 && !isChangingFloorF2) {
		//App->scene->secondFloor->active = !App->scene->secondFloor->active;
		currJumpForce = jumpForce * 1.6;
		currentAnimation = &bigJumpUpUpAnim;
		isChangingFloorF1 = true;
		frameContador = 0;
	}

	if (isChangingFloorF1 || isChangingFloorF2) {
		currentAnimation = &bigJumpUpUpAnim;
		if (isChangingFloorF1) {
			
			position.y -= 0.5f;
			if (position.y <= 95) {
				isChangingFloorF1 = false;
				isChangingFloorF2 = true;
				currJumpForce = jumpForce / 2;
				App->scene->secondFloor->active = !App->scene->secondFloor->active;
			}
		}
		if (isChangingFloorF2) {
			//currentAnimation = &bigJumpUpDownAnim;

			if (positionBefore.y == position.y && position.y > 95) {
				isChangingFloorF2 = false;
			}

			positionBefore.y = position.y;
		}
		
		collider->SetPos(position.x, position.y - currentAnimation->GetCurrentFrame().h);
		collider->SetSize(currentAnimation->GetCurrentFrame().w, currentAnimation->GetCurrentFrame().h);

		currentAnimation->Update();

		return update_status::UPDATE_CONTINUE;

	}


	/*if (isChangingFloor) {
		frameContador++;
		currentAnimation = &jumpAnim;
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT && !isJumping && !isChangingFloor) {
		//App->scene->secondFloor->active = !App->scene->secondFloor->active;
		currJumpForce = jumpForce * 1.6;
		
		isChangingFloor = true;
		frameContador = 0;
	}
	if (isChangingFloor) {
		if (frameContador >= 30) {
			App->scene->secondFloor->active = !App->scene->secondFloor->active;
		}
		if (frameContador >= 70) {
			isChangingFloor = false;
		}
		
		collider->SetPos(position.x, position.y - currentAnimation->GetCurrentFrame().h);
		collider->SetSize(currentAnimation->GetCurrentFrame().w, currentAnimation->GetCurrentFrame().h); 
		currentAnimation->Update();
		return update_status::UPDATE_CONTINUE;
	}
	*/

	

	if (isAttacking) {
		currentAnimation = &attack_shurikenAnim;
		if (currentAnimation->HasFinished()) {
			isAttacking = false;
			currentAnimation->Reset();
		}
		else {
			collider->SetPos(position.x, position.y - currentAnimation->GetCurrentFrame().h);
			collider->SetSize(currentAnimation->GetCurrentFrame().w, currentAnimation->GetCurrentFrame().h);
			currentAnimation->Update();
			return update_status::UPDATE_CONTINUE;
		}
	}

	if (isCrouchedAttacking) {
		currentAnimation = &crouched_AttackAnim;
		if (currentAnimation->HasFinished()) {
			isCrouchedAttacking = false;
			currentAnimation->Reset();
		}
		else {
			collider->SetPos(position.x, position.y - currentAnimation->GetCurrentFrame().h);
			collider->SetSize(currentAnimation->GetCurrentFrame().w, currentAnimation->GetCurrentFrame().h);
			currentAnimation->Update();
			return update_status::UPDATE_CONTINUE;
		}
	}


	//MOVERSE A LA DERECHA
	if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		currentAnimation = &forwardAnim;
		position.x += speed;
		facingRight = true;
	}

	//MOVERSE A LA IZQUIERDA
	if (App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		currentAnimation = &forwardAnim;
		position.x -= speed;
		facingRight = false;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
		currentAnimation = &crouched_idleAnim;

		if (App->input->keys[SDL_SCANCODE_D] == KEY_REPEAT || App->input->keys[SDL_SCANCODE_A] == KEY_REPEAT) {
			currentAnimation = &crouched_forwardAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_REPEAT) {
		currentAnimation = &watching_UpAnimation;
	}

	//MECANICA DEL SALTO
	if (isJumping) {
		currentAnimation = &jumpAnim;
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping) {
		isJumping = true;
		currJumpForce = jumpForce;
		
		currentAnimation = &jumpAnim;
	}

	


	collider->SetPos(position.x, position.y - currentAnimation->GetCurrentFrame().h);
	collider->SetSize(currentAnimation->GetCurrentFrame().w, currentAnimation->GetCurrentFrame().h);


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
			App->particles->AddParticle(App->particles->shurikenR, position.x + 46, position.y - currentAnimation->GetCurrentFrame().h + 12, Collider::Type::PLAYER_SHOT,0);
			App->audio->PlayFx(ataqueFX);
		}
		else {
			App->particles->AddParticle(App->particles->shurikenL, position.x , position.y - currentAnimation->GetCurrentFrame().h + 12, Collider::Type::PLAYER_SHOT,0);
		}
	}


	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
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
		}
		else {
			//ta abajo
			App->scene->secondFloor->active = false;
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

	if (c1 == collider && c2->type == Collider::ENEMY && destroyed == false)
	{
		destroyed = true;
	}

}