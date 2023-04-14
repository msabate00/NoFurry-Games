#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_render.h"

#include <iostream>

using namespace std;

// Street Fighter reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = FLOOR_LEVEL;

	// idle animation (arcade sprite sheet)
	idleAnim.PushBack({ 220, 112, 39, 60 });

	idleAnim.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	forwardAnim.PushBack({ 10, 112, 39, 60 });
	forwardAnim.PushBack({ 52, 112, 39, 60 });
	forwardAnim.PushBack({ 94, 112, 39, 60 });
	forwardAnim.PushBack({ 136, 112, 39, 60 });
	forwardAnim.PushBack({ 178, 112, 39, 60 });
	forwardAnim.PushBack({ 220, 112, 39, 60 });



	forwardAnim.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	backwardAnim.PushBack({ 10, 112, 39, 60 });
	backwardAnim.PushBack({ 52, 112, 39, 60 });
	backwardAnim.PushBack({ 94, 112, 39, 60 });
	backwardAnim.PushBack({ 136, 112, 39, 60 });
	backwardAnim.PushBack({ 178, 112, 39, 60 });
	backwardAnim.PushBack({ 220, 112, 39, 60 });

	//backwardAnim.PushBack({ 80, 114, 33, 58 });

	/*backwardAnim.PushBack({352, 128, 54, 91});
	backwardAnim.PushBack({ 259, 128, 63, 90 });
	backwardAnim.PushBack({ 162, 128, 64, 92 });
	backwardAnim.PushBack({ 78, 131, 60, 88 });
	backwardAnim.PushBack({ 9, 136, 53, 83 });*/
	backwardAnim.speed = 0.1f;


	crouched_idleAnim.PushBack({ 16, 212, 34, 33 });

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/Player/Player.png"); // arcade version

	collider = App->collisions->AddCollider({ 0,0,39,60 }, Collider::Type::PLAYER);

	return ret;
}

update_status ModulePlayer::Update()
{
	//Aplica la gravedad a su altura
	position.y += GRAVITY;




	//Reset the currentAnimation back to idle before updating the logic
	currentAnimation = &idleAnim;

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
		currentAnimation = &backwardAnim;
		position.x -= speed;
		facingRight = false;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_REPEAT) {
		currentAnimation = &crouched_idleAnim;
	}


	//MECANICA DEL SALTO
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN && !isJumping) {

		isJumping = true;
		currJumpForce = jumpForce;
	}
	if (isJumping) {
		position.y -= currJumpForce;
		currJumpForce -= 0.25f * GRAVITY;

	}

	collider->SetPos(position.x, position.y - currentAnimation->GetCurrentFrame().h);
	collider->SetSize(currentAnimation->GetCurrentFrame().w, currentAnimation->GetCurrentFrame().h);


	//ATAQUE SHURIKEN
	if (App->input->keys[SDL_SCANCODE_J] == KEY_DOWN) {

		if (facingRight) {
			App->particles->AddParticle(App->particles->shurikenR, position.x + currentAnimation->GetCurrentFrame().w / 2, position.y - currentAnimation->GetCurrentFrame().h / 2, 0);
		}
		else {
			App->particles->AddParticle(App->particles->shurikenL, position.x + currentAnimation->GetCurrentFrame().w / 2, position.y - currentAnimation->GetCurrentFrame().h / 2, 0);
		}
	}


	currentAnimation->Update();

	//SI LLEGA AL NIVEL DEL SUELO, PONE SU ALTURA A ESE NIVEL, Y LE PERMITE VOLVER A SALTAR
	if (position.y >= FLOOR_LEVEL) {
		position.y = FLOOR_LEVEL;
		isJumping = false;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if(facingRight) {
		App->render->Blit(texture, position.x, position.y - rect.h, &rect);
		
	}
	else {
		App->render->Blit(texture, position.x, position.y - rect.h, &rect, SDL_FLIP_HORIZONTAL);
	}

	
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Detect collision with a wall. If so, destroy the player.

}