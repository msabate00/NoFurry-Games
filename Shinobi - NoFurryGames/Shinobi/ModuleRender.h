#ifndef __MODULE_RENDER_H__
#define __MODULE_RENDER_H__

#include "Module.h"
#include "SDL/include/SDL_Rect.h"
#include "SDL/include/SDL_render.h"
#include <vector>
#include <iostream>
struct SDL_Texture;
struct SDL_Renderer;

class ModuleRender : public Module
{
public:
	//Constructor
	ModuleRender(bool startEnabled);

	//Destructor
	~ModuleRender();

	// Called on application start.
	// Creates the rendering context using the program's window.
	bool Init() override;

	// Called at the beginning of the application loop
	// Clears the rendering context to a background color
	update_status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles camera movement
	update_status Update() override;

	// Called at the end of the application loop.
	// Displays a rectangle in the rendering context
	// Updates the screen with the rendered content
	update_status PostUpdate() override;

	// Called on application exit.
	// Destroys the rendering context
	bool CleanUp() override;

	// Prints a texture to the rendering context.
	// Param texture	- A valid SDL Texture, validation checks are not performed
	// Param x,y		- Position x,y in the screen (upper left axis)
	// Param section	- The portion of the texture we want to copy. nullptr for the entire texture
	// Param speed		- The amount of effect that is applied to the sprite depending on the camera
	// Param flip		- Flip te image
	bool Blit(SDL_Texture* texture, int x, int y, SDL_RendererFlip flip, SDL_Rect* section = nullptr, float speed = 1.0f);

	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float speed = 1.0f);

	/*//Print Class
	void printSkillIcon();
	void printHostageIcon(int);
	void printLifeIcon(int);
	void printNum(std::vector<int> num,SDL_Texture* texture);
	void printTime(std::string time, SDL_Texture* texture);


	std::vector<int> getDigits(int number);

	int updateTimer(time_t start_time);
	std::string getTimeString(int elapsed_seconds);

	*/
	//void flipSurface(SDL_Surface *flipped);


public:
	// Rendering context used for any rendering action
	SDL_Renderer* renderer = nullptr;
	/*
	SDL_Texture* SkillIcon = nullptr;
	SDL_Texture* HostageIcon = nullptr;
	SDL_Texture* LifeIcon = nullptr;
	SDL_Texture* LetraNum = nullptr;
	SDL_Texture* SA = nullptr;
	SDL_Texture* VE = nullptr;
	SDL_Texture* Time = nullptr;
	SDL_Texture* dosPunt = nullptr;
	*/
	// A rectangle that represents the camera section
	// Sprites will be rendered to the screen depending on the camera position
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// The speed at which the camera will be moving


	int cameraSpeed = 3;
	/*
	int hostage_num = 3;
	int life_num = 2;
	int texture_num = 123456789;

	int elapsed_time;
	time_t start_time;
	int total_time = 20;
	std::string time_string;
	*/
};

#endif //__MODULE_RENDER_H__
