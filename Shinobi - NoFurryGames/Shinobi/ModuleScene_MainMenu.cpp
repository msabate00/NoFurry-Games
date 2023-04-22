#include "ModuleScene_MainMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"


ModuleScene_MainMenu::ModuleScene_MainMenu(bool startEnabled) : Module(startEnabled)
{
	
}

ModuleScene_MainMenu::~ModuleScene_MainMenu()
{

}

// Load assets
bool ModuleScene_MainMenu::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_solido.png");
	stageBackgroundTexture = App->textures->Load("Assets/Maps/Level1/Nivel1_fondo.png");

	//Musicadddd
	App->audio->PlayMusic("Assets/Audio/Music/Mission 1-1.ogg", 1.0f);


	return ret;
}

update_status ModuleScene_MainMenu::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene_MainMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(stageBackgroundTexture, 0, 0, SDL_FLIP_NONE, &background, 0.35f); // Edificios del fondo
	App->render->Blit(stageTexture, 0, -125, SDL_FLIP_NONE, &ground, 1.0f); // Suelo y eso

	return update_status::UPDATE_CONTINUE;
}