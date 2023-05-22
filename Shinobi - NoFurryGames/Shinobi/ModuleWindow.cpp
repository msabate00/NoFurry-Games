#include "ModuleWindow.h"

#include "Application.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"


ModuleWindow::ModuleWindow(bool startEnabled) : Module(startEnabled)
{}

ModuleWindow::~ModuleWindow()
{}

bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		Uint32 flags = SDL_WINDOW_SHOWN;

		if (WIN_FULLSCREEN == true)
			flags |= SDL_WINDOW_FULLSCREEN;

		if (WIN_BORDERLESS == true)
			flags |= SDL_WINDOW_BORDERLESS;

		if (WIN_RESIZABLE == true)
			flags |= SDL_WINDOW_RESIZABLE;

		if (WIN_FULLSCREEN_DESKTOP == true)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow("Shinobi - NoFurryGames", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, flags);
		SDL_Surface* surface = IMG_Load("Assets/Misc/icon.png");
		SDL_SetWindowIcon(window, surface);

		if (window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}


void ModuleWindow::changeWindowMode() {
	fullscreen = !fullscreen;
	
	Uint32 flags = SDL_WINDOW_SHOWN;

	if (WIN_FULLSCREEN == true)
		flags |= SDL_WINDOW_FULLSCREEN;

	if (WIN_BORDERLESS == true)
		flags |= SDL_WINDOW_BORDERLESS;

	if (WIN_RESIZABLE == true)
		flags |= SDL_WINDOW_RESIZABLE;

	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		//flags |= SDL_WINDOW_FULLSCREEN;
	}
	
	SDL_SetWindowFullscreen(window, flags);
	
	

	
	


}


bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (window != nullptr)
		SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return true;
}




