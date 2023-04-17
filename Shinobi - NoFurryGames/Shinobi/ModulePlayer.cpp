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

	collider = App->collisions->AddCollider({ 0,0,39,60 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	//Aplica la gravedad a su altura
	//position.y += GRAVITY;
	currJumpForce += -0.25f * GRAVITY;
	float grav = GRAVITY;
	if (currJumpForce < -0.25f * grav) {
		isJumping = true;
	}

	//cout << currJumpForce << endl;

	position.y -= currJumpForce;
	



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
		currentAnimation = &forwardAnim;
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
	/*if (isJumping) {
		position.y -= currJumpForce;
		currJumpForce -= 0.25f * GRAVITY;

	}*/

	collider->SetPos(position.x, position.y - currentAnimation->GetCurrentFrame().h);
	collider->SetSize(currentAnimation->GetCurrentFrame().w, currentAnimation->GetCurrentFrame().h);


	//ATAQUE SHURIKEN
	if (App->input->keys[SDL_SCANCODE_J] == KEY_DOWN) {

		if (facingRight) {
			App->particles->AddParticle(App->particles->shurikenR, position.x + currentAnimation->GetCurrentFrame().w / 2, position.y - currentAnimation->GetCurrentFrame().h / 2, Collider::Type::PLAYER_SHOT,0);
		}
		else {
			App->particles->AddParticle(App->particles->shurikenL, position.x + currentAnimation->GetCurrentFrame().w / 2, position.y - currentAnimation->GetCurrentFrame().h / 2, Collider::Type::PLAYER_SHOT,0);
		}
	}


	currentAnimation->Update();

	//SI LLEGA AL NIVEL DEL SUELO, PONE SU ALTURA A ESE NIVEL, Y LE PERMITE VOLVER A SALTAR

	/*if (position.y >= FLOOR_LEVEL) {
		position.y = FLOOR_LEVEL;
		isJumping = false;
	}*/

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

	
	if (c1 == collider && c2->type == Collider::WALL)
	{

		//cout << " Caja x: " << c2->GetRect().x << " Caja y: " << c2->GetRect().y << " Caja w: " << c2->GetRect().h << " Posi x: " << position.x << " Posi y: " << position.y << " CurrJump: " << currJumpForce << endl;

		
		if (c2->GetRect().x >= position.x && c2->GetRect().y+2 <= position.y) {
			//NO SE PUEDE MOVER PARA LA DERECHA
			position.x -= speed;
		}
		if (c2->GetRect().x + c2->GetRect().w-1 <= position.x && c2->GetRect().y+2 <= position.y) {
			//NO SE PUEDE MOVER PARA LA IZQUIERDA
			position.x += speed;
		}
		if (c2->GetRect().y+1 >= position.y + currJumpForce && currJumpForce<=0){ //COLISION DEBAJO
			position.y = c2->GetRect().y+1;
			currJumpForce = 0;
			isJumping = false;
		}
		


		//App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		//App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		//App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		//App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		//App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		//App->audio->PlayFx(explosionFx);

		
	}

}