#include "ModuleScene_MainMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"

#include <string> 
#include <vector>
#include <iostream>


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


	Letra = App->textures->Load("Assets/Interface/Letra/Letra.png");
	LogoMedio = App->textures->Load("Assets/Interface/Color_use/White/Sega.png");

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

	//printLetra(App->scene_Level1->getDigits(texture_Year), LetraYear);
	//printIconC();
	//printNom();
	App->render->Blit(Letra, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 100, SDL_FLIP_NONE, nullptr, 10);
	//App->render->Blit(LogoMedio, SCREEN_WIDTH - 250, SCREEN_HEIGHT - 100, SDL_FLIP_NONE, nullptr, 10);
	return update_status::UPDATE_CONTINUE;
}


void ModuleScene_MainMenu::printLetra(std::vector<int> number, SDL_Texture* LetraNum) {

	int IconPosition = 70;
	for (int i = 0; i < number.size(); i++)
	{
		std::string filename = "Assets/Interface/Color_use/White/White_Numeros/White_" + std::to_string(number[i]) + ".png";
		LetraNum = App->textures->Load(filename.c_str());

		App->render->Blit(LetraNum, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 16;
	}
	
}

void ModuleScene_MainMenu::printIconC() {

	int IconPosition = 150;
	for (int i = 0; i < 5; i++)
	{
		std::string filename = "Assets/Interface/Color_use/White/Icon/White_" + std::to_string(i) + ".png";
		LetraIconC = App->textures->Load(filename.c_str());

		App->render->Blit(LetraIconC, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 16;
	}

}

void ModuleScene_MainMenu::printNom() {
	
	int IconPosition = 250;
	
		if (NameColor) {
			for (int i = 0; i < 7; i++)
			{
			std::string filename = "Assets/Interface/Color_use/Red/Shinobi/Rojo_" + std::to_string(i) + ".png";
			LetraNom = App->textures->Load(filename.c_str());
			App->render->Blit(LetraNom, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
			IconPosition -= 16;
			}
			NameColor = false;
		}else{
			for (int i = 0; i < 7; i++)
			{
			std::string filename = "Assets/Interface/Color_use/White/Shinobi/White_" + std::to_string(i) + ".png";
			LetraNom = App->textures->Load(filename.c_str());
			App->render->Blit(LetraNom, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
			IconPosition -= 16;
			}
			NameColor = true;
		}
		SDL_Delay(500);
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
