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

#include "SDL/include/SDL.h"
#include <string> 
#include <vector>
#include <iostream>
#include <cmath>

ModuleScene_MainMenu::ModuleScene_MainMenu(bool startEnabled) : Module(startEnabled)
{
	eyesAnimation.PushBack({ 0, 448, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	eyesAnimation.PushBack({ 0, 896, SCREEN_WIDTH, SCREEN_HEIGHT }); //izquierda
	eyesAnimation.PushBack({ 0, 448, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	eyesAnimation.PushBack({ 0, 672, SCREEN_WIDTH, SCREEN_HEIGHT }); //derecha
	eyesAnimation.PushBack({ 0, 448, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	eyesAnimation.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Brilli
	eyesAnimation.PushBack({ 0, 224, SCREEN_WIDTH, SCREEN_HEIGHT }); //Brilli2
	
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
	//textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	textureBackground = App->textures->Load("Assets/Interface/Menu/background.png");

	
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	
	monedaFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/coin.wav");
	//Musicadddd
	//App->audio->PlayMusic("Assets/Audio/Music/Mission 1-1.ogg", 1.0f);


	
	LogoMedio = App->textures->Load("Assets/Interface/Color_use/White/Sega.png");

	LetraNomRed = App->textures->Load("Assets/Interface/Color_use/Red/Shinobi/SHINOBI.png");
	LetraNomWhite = App->textures->Load("Assets/Interface/Color_use/White/Shinobi/SHINOBI.png");
	LetraIconC = App->textures->Load("Assets/Interface/Color_use/White/Icon/Sega.png");
	LetraYear = App->textures->Load("Assets/Interface/Color_use/White/Icon/1987.png");

	return ret;
}

update_status ModuleScene_MainMenu::Update()
{
	
	currentAnimation = &eyesAnimation;
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_Level1, 20);
		App->audio->PlayFx(monedaFX);
	}
	
	currentAnimation->Update();
	


	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene_MainMenu::PostUpdate()
{


	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	App->render->Blit(textureBackground, 0, 0, SDL_FLIP_NONE, &currentAnimation->GetCurrentFrame(), 1);

	printYear();
	printIconC();
	printNom();
	printLetra();
	


	App->render->Blit(LogoMedio, SCREEN_WIDTH - 225, SCREEN_HEIGHT - 50, SDL_FLIP_NONE, nullptr, 10);
	return update_status::UPDATE_CONTINUE;
}



void ModuleScene_MainMenu::printLetra() {

	std::string filename = "Assets/Interface/Letra/LetraColor/Letra0.png";
	Letra = App->textures->Load(filename.c_str());
	
	App->render->Blit(Letra, letraGetX(), letraGetY(), SDL_FLIP_NONE, nullptr, 0);

}







void ModuleScene_MainMenu::printYear() {
	int IconPosition = 50;

	App->render->Blit(LetraYear, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
}

void ModuleScene_MainMenu::printIconC() {

	int IconPosition = 100;
	for (int i = 0; i < 5; i++)
	
	App->render->Blit(LetraIconC, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
}

void ModuleScene_MainMenu::printNom() {


	int IconPosition = 250;
	timer += App->deltaTime;

	
		if (NameColor) {
			/*
			for (int i = 0; i < 7; i++) {
				std::string filename = "Assets/Interface/Color_use/Red/Shinobi/Rojo_" + std::to_string(i) + ".png";
				LetraNom = App->textures->Load(filename.c_str());
				App->render->Blit(LetraNom, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
				IconPosition -= 16;
			}*/
			
			App->render->Blit(LetraNomRed, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
			if (timer >= switchTime) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
			}
		}
		else {
			/*
			for (int i = 0; i < 7; i++) {
				std::string filename = "Assets/Interface/Color_use/White/Shinobi/White_" + std::to_string(i) + ".png";
				LetraNom = App->textures->Load(filename.c_str());
				App->render->Blit(LetraNom, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
				IconPosition -= 16;
			}*/

			App->render->Blit(LetraNomWhite, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
			if (timer >= switchTime) {
				NameColor = true;
				timer = 0.0f; // Reset Tiempo Contador
			}
		}
		
	
}




double ModuleScene_MainMenu::letraGetX(){
	if (letraY > 32 && letraY < 36 && letraX > 146 && letraX < 150) {
		//cout << "X yes" << endl;
		letraX = 148;
	}else{
	letraX = CENTER_X + A * sin(angle * M_PI / 270.0);
	angle += ROTATION_SPEED;
	A = A - 0.7;
	//cout << "X: " << letraX << endl;
	}
	return letraX;
}
double ModuleScene_MainMenu::letraGetY() {
	if (letraY > 32 && letraY < 36 && letraX > 146 && letraX < 150) {
		//cout << "Y yes" << endl;
		letraY = 34;
	}
	else {
	letraY = CENTER_Y + B * cos(angle * M_PI / 270.0);
	angle += ROTATION_SPEED;
	B = B - 0.6,5;
	//cout << "Y: " << letraY << endl;
	}
	
	return letraY;
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
