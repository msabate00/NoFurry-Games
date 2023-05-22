#include "ModuleFadeToBlack.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_render.h"

#include <iostream>

using namespace std;

ModuleFadeToBlack::ModuleFadeToBlack(bool startEnabled) : Module(startEnabled)
{
	screenRect = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };



	fadeIn.PushBack({0, 0, 320, 242});
	fadeIn.PushBack({0,	242, 320, 242 });
	fadeIn.PushBack({0, 484, 320, 242 });
	fadeIn.PushBack({0, 726, 320, 242 });
	fadeIn.PushBack({0, 726, 320, 242 });
	fadeIn.speed = 0.3f;
	fadeIn.loop = false;

	fadeOut.PushBack({ 0, 726, 320, 242 });
	fadeOut.PushBack({ 0, 484, 320, 242 });
	fadeOut.PushBack({ 0,242, 320, 242 });
	fadeOut.PushBack({ 0, 0, 320, 242 });	
	fadeOut.PushBack({ 0, 0, 0, 0 });	
	fadeOut.speed = 0.3f;
	fadeOut.loop = false;



}

ModuleFadeToBlack::~ModuleFadeToBlack()
{

}

bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");

	fadeInOut_texture = App->textures->Load("Assets/Interface/Menu/fade.png");

	// Enable blending mode for transparency
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

update_status ModuleFadeToBlack::Update()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return update_status::UPDATE_CONTINUE;

	if (currentStep == Fade_Step::TO_BLACK)
	{
		fadeOut.Reset();
		currentAnimation = &fadeIn;
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			// TODO 1: Enable / disable the modules received when FadeToBlacks() gets called
			moduleToDisable->Disable();
			moduleToEnable->Enable();

			currentStep = Fade_Step::FROM_BLACK;
		}
	}
	else
	{
		fadeIn.Reset();
		currentAnimation = &fadeOut;
		--frameCount;
		if (frameCount <= 0)
		{
			currentStep = Fade_Step::NONE;
		}
	}

	

	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleFadeToBlack::PostUpdate()
{

	
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return update_status::UPDATE_CONTINUE;

	float fadeRatio = (float)frameCount / (float)maxFadeFrames;

	

	// Render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screenRect);

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	
	if (currentStep == Fade_Step::TO_BLACK) {
	
		App->render->Blit(fadeInOut_texture, App->render->camera.x/SCREEN_SIZE - 320, 0, SDL_FLIP_NONE, &rect);
		App->render->Blit(fadeInOut_texture, App->render->camera.x / SCREEN_SIZE, 0, SDL_FLIP_NONE, &rect);
		App->render->Blit(fadeInOut_texture, App->render->camera.x / SCREEN_SIZE + 320, 0, SDL_FLIP_NONE, &rect);
	}
	else {
	
		App->render->Blit(fadeInOut_texture, App->render->camera.x / SCREEN_SIZE - 320, 0, SDL_FLIP_NONE, &rect);
		App->render->Blit(fadeInOut_texture, App->render->camera.x / SCREEN_SIZE, 0, SDL_FLIP_NONE, &rect);
		App->render->Blit(fadeInOut_texture, App->render->camera.x / SCREEN_SIZE + 320, 0, SDL_FLIP_NONE, &rect);
	}
	

	return update_status::UPDATE_CONTINUE;
}

bool ModuleFadeToBlack::FadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames)
{
	bool ret = false;

	// If we are already in a fade process, ignore this call
	if (currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		// TODO 1: We need to keep track of the modules received in FadeToBlack(...)
		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;
		App->activeModule = moduleToEnable;

		ret = true;
	}

	return ret;
}