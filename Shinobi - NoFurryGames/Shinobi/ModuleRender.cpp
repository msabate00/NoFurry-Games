#include "ModuleRender.h"
#include <string> 
#include <iostream>

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"

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
	if ((App->player->position.x * 2 - SCREEN_WIDTH) - 100 > camera.x) {
		camera.x += cameraSpeed;
	}
	if ((App->player->position.x * 2 - SCREEN_WIDTH) + 200 < camera.x) {
		camera.x -= cameraSpeed;
	}

	//Handle positive vertical movement
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT)
		camera.y -= cameraSpeed;

	//Handle negative vertical movement
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT)
		camera.y += cameraSpeed;

	// TODO 1: Handle horizontal movement of the camera
	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_REPEAT)
		camera.x -= cameraSpeed;
	if (camera.x < 0) camera.x = 0;			//LIMITES CAMARA

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT)
		camera.x += cameraSpeed;
	if (camera.x > 3324) camera.x = 3324;	//LIMITES CAMARA

	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) {
		App->godMode = !App->godMode;
	}

	

	

	//cout << "PosiCam: " << camera.x << " PosiPlayer: " << App->player->position.x << endl;



	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
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
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed)
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
	if (SDL_RenderCopyEx(renderer, texture, section, &rect, 0, &center, SDL_FLIP_HORIZONTAL) != 0)

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

/*
void ModuleRender::flipSurface(SDL_Surface *flipped) {
	//Pointer to the soon to be flipped surface
	//SDL_Surface* flipped = NULL;

	
	flipped = SDL_CreateRGBSurface(SDL_SWSURFACE, flipped->w, flipped->h, flipped->format->BitsPerPixel, flipped->format->Rmask, flipped->format->Gmask, flipped->format->Bmask, flipped->format->Amask);
	//Go through columns
	for (int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx--)
	{
		//Go through rows
		for (int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry--)
		{
			//Get pixel
			Uint32 pixel = get_pixel32(flipped, x, y);
			put_pixel32(flipped, rx, y, pixel);
			
		}
	}
	//return flipped;
}

Uint32 get_pixel32(SDL_Surface* surface, int x, int y)
{
	//Convert the pixels to 32 bit
	Uint32* pixels = (Uint32*)surface->pixels;

	//Get the requested pixel
	return pixels[(y * surface->w) + x];
}

void put_pixel32(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
	//Convert the pixels to 32 bit
	Uint32* pixels = (Uint32*)surface->pixels;

	//Set the pixel
	pixels[(y * surface->w) + x] = pixel;
}*/