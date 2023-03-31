#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene()
{
	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 2046;
	ground.h = 350;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;


	/*ship.PushBack({0,0, 540, 200});
	ship.PushBack({0,2, 540, 200});
	ship.speed = 0.02;*/

	ship.x = 0;
	ship.y = 0;
	ship.w = 540;
	ship.h = 200;


	girl.PushBack({624, 15, 33, 57});
	girl.PushBack({624, 79, 33, 57});
	girl.PushBack({624, 143, 33, 57});
	girl.PushBack({624, 79, 33, 57 });
	girl.speed = 0.1f;



}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_solido.png");
	stageBackgroundTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_fondo.png");

	return ret;
}

update_status ModuleScene::Update()
{
	flag.Update();
	

	if (shipUp) {
		shipY -= shipSpeed;
		if (shipY <= -28) shipUp = false;
	}
	else {
		shipY += shipSpeed;
		if (shipY >= -25) shipUp = true;
	}
	girl.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(stageBackgroundTexture, 0, 0, &background, 0.75f); // Edificios del fondo
	App->render->Blit(stageTexture, 0, -125, &ground, 1.0f); // Suelo y eso




	//App->render->Blit(stageTexture, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	/*// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	App->render->Blit(stageTexture, -10, shipY, &ship, 0.85);

	// TODO 3: Animate the girl on the ship (see sprite sheet)
	App->render->Blit(stageTexture, 190, shipY + 128, &(girl.GetCurrentFrame()), 0.85);**/


	
	//App->render->Blit(stageTexture, 0, 170, &ground);

	return update_status::UPDATE_CONTINUE;
}