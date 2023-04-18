#include "ModuleRender.h"
#include <string> 
#include <iostream>
#include <vector>

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"


#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"

using namespace std;

ModuleRender::ModuleRender() : Module()
{

}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//SkillIcon = App->textures->Load("Assets/Sprites/Player/Player.png");
	SkillIcon = App->textures->Load("Assets/Interface/Rojo.png");
	HostageIcon = App->textures->Load("Assets/Interface/rescate.png");
	LifeIcon = App->textures->Load("Assets/Interface/vida.png");


	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 115, 66, 148, 255);

	//Clear rendering target
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{

	//Automover la camara

	if ((App->player->position.x * SCREEN_SIZE) + 
		App->player->currentAnimation->GetCurrentFrame().w / 2 >= camera.x + SCREEN_WIDTH / 2 * SCREEN_SIZE) {
		camera.x += cameraSpeed;
	}
	if ((App->player->position.x * SCREEN_SIZE) +
		App->player->currentAnimation->GetCurrentFrame().w / 2 <= camera.x + SCREEN_WIDTH / 4 * SCREEN_SIZE) {
		camera.x -= cameraSpeed;
	}
	
	if (App->godMode) {
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT)
		camera.y -= cameraSpeed;

	
		if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT)
			camera.y += cameraSpeed;


		if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_REPEAT)
			camera.x -= cameraSpeed;


		if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT)
			camera.x += cameraSpeed;
	}
	else {

		if (camera.x > (2046*SCREEN_SIZE)-(SCREEN_WIDTH*SCREEN_SIZE)) camera.x = (2046 * SCREEN_SIZE) - (SCREEN_WIDTH * SCREEN_SIZE);	//LIMITES CAMARA
		if (camera.x < 0) camera.x = 0;			//LIMITES CAMARA
	}
	
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) {
		App->godMode = !App->godMode;
	}
	
	
	

	//cout << "PosiCam: " << camera.x << " PosiPlayer: " << App->player->position.x << endl;



	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{


	//PrintaIcon
	printSkillIcon();
	printHostageIcon(hostage_num);
	printLifeIcon(life_num);

	printNum(Texture_num,LetraNum);

	//Update the screen
	SDL_RenderPresent(renderer);


	return update_status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy the rendering context
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_RendererFlip flip, SDL_Rect* section, float speed)
{
	bool ret = true;

	SDL_Rect rect{
		(int)(-camera.x * speed) + x * SCREEN_SIZE,
		(int)(-camera.y * speed) + y * SCREEN_SIZE,
		0, 0 };

	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		//Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	//Para el flip
	SDL_Point center{ rect.w / 2, rect.h / 2 };
	if (SDL_RenderCopyEx(renderer, texture, section, &rect, 0, &center, flip) != 0)

	//Sin el flip
	//if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}
	if (App->godMode) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &rect);
	}

	

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect dstRect{
		(int)(-camera.x * speed) + rect.x * SCREEN_SIZE,
		(int)(-camera.y * speed) + rect.y * SCREEN_SIZE,
		rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::printSkillIcon() {
	SDL_Rect rect = { 168,59,17,14 };

	bool sur = App->render->Blit(SkillIcon, SCREEN_WIDTH - 100, SCREEN_HEIGHT-16, SDL_FLIP_NONE, nullptr, 0);
	if (!sur) {
		cout << "error" << endl;
	}


}

void ModuleRender::printHostageIcon(int hostage) {

	//App->render->Blit(SkillIcon, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
	int IconPosition = 340;

	for (int i = 0; i < hostage; i++)
	{
		App->render->Blit(HostageIcon, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 8;
	}

}
void ModuleRender::printLifeIcon(int life) {
	

	int IconPosition = 350;
	for (int i = 0; i < life; i++)
	{
		App->render->Blit(LifeIcon, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 8;
	}

}


void ModuleRender::printNum(int number, SDL_Texture* LetraNum) {

	std::vector<int> digits;

	if (number == 0) {
		digits.push_back(0);
	}

	while (number != 0) {
		int digit = number % 10;
		digits.push_back(digit);
		number /= 10;
	}
	std::reverse(digits.begin(), digits.end());

	int IconPosition = 250;
	for (int i = 0; i < digits.size(); i++)
	{
		std::string filename = "Assets/Interface/Red/Rojo_Numeros/Rojo_" + std::to_string(digits[i]) + ".png";
		SDL_Texture* LetraNum = App->textures->Load(filename.c_str());

		App->render->Blit(LetraNum, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 16;
	}

}


/*std::vector<int> ModuleRender::getDigits(int number) {
	std::vector<int> digits;

	// 处理特殊情况
	if (number == 0) {
		digits.push_back(0);
		return digits;
	}

	// 分解数字
	while (number != 0) {
		int digit = number % 10;
		digits.push_back(digit);
		number /= 10;
	}

	// 反转数字，使得各位数字的顺序正确
	std::reverse(digits.begin(), digits.end());

	return digits;
}*/