#include "ModuleScene_MainMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"


ModuleScene_MainMenu::ModuleScene_MainMenu(bool startEnabled) : Module(startEnabled)
{
	eyesAnimation.PushBack({0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	eyesAnimation.PushBack({0, 231, SCREEN_WIDTH, SCREEN_HEIGHT });
	eyesAnimation.loop = true;
	eyesAnimation.speed = 0.04f;
	background = { 200,200, SCREEN_WIDTH, SCREEN_HEIGHT };


}

ModuleScene_MainMenu::~ModuleScene_MainMenu()
{

}

// Load assets
bool ModuleScene_MainMenu::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	textureBackground = App->textures->Load("Assets/Interface/Menu/fondo.png");

	
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	
	monedaFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/coin.wav");
	//Musicadddd
	//App->audio->PlayMusic("Assets/Audio/Music/Mission 1-1.ogg", 1.0f);

	return ret;
}

update_status ModuleScene_MainMenu::Update()
{

	currentAnimation = &eyesAnimation;
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_Level1, 90);
		App->audio->PlayFx(monedaFX);
	}
	
	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene_MainMenu::PostUpdate()
{


	App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	App->render->Blit(textureBackground, 0, 0, SDL_FLIP_NONE, &currentAnimation->GetCurrentFrame(), 1);
	

	return update_status::UPDATE_CONTINUE;
}


/*SDL_Texture* GetResizedTexture(SDL_Texture* texture, int width, int height)
{
	SDL_Texture* resizedTexture = SDL_CreateTexture(
		App->render->renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width,
		height
	);

	SDL_SetRenderTarget(App->render->renderer, resizedTexture);

	SDL_Rect src = { 0, 0, texture->GetWidth(), texture->GetHeight() };
	SDL_Rect dst = { 0, 0, width, height };

	SDL_RenderCopyEx(App->render->renderer, texture->GetTexture(), &src, &dst, 0, NULL, SDL_FLIP_NONE);

	SDL_SetRenderTarget(App->render->renderer, NULL);

	return resizedTexture;
}*/
