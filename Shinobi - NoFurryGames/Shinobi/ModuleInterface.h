#ifndef __MODULE_INTERFACE_H__
#define __MODULE_INTERFACE_H__

#include "Module.h"
#include "SDL/include/SDL_Rect.h"
#include "SDL/include/SDL_render.h"
#include <vector>
#include <iostream>
struct SDL_Texture;
struct SDL_Renderer;

class ModuleInterface : public Module
{
public:
	//Constructor
	ModuleInterface(bool startEnabled);

	//Destructor
	~ModuleInterface();

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


public:
	
};

#endif //__MODULE_RENDER_H__
