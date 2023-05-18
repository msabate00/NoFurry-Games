#pragma once
#ifndef __MODULE_SCENE_Ranking_H__
#define __MODULE_SCENE_Ranking_H__

#include "Module.h"
#include "Animation.h"
#include <vector>
#include <iostream>
#include <string> 

struct SDL_Texture;

class ModuleRanking : public Module
{
public:
	//Constructor
	ModuleRanking(bool startEnabled);

	//Destructor
	~ModuleRanking();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate();


	void prinIcon();
	void printTitle();
	void printrRanking();
	void insert_rank(int new_score, int new_coin, const std::string& new_name);

public:

	// The scene sprite sheet loaded into an SDL_Texture



	SDL_Texture* dosComa = nullptr;
	SDL_Texture* textureBackground = nullptr;


	SDL_Texture** iconType = new SDL_Texture * [2];
	SDL_Texture* ranking = nullptr;

	SDL_Rect background;
	Animation* currentAnimation = nullptr;
	Animation backgroundAnim;

	struct rankDate {
		std::string rank;
		int score;
		int coin;
		std::string name;
	};

	rankDate leaderboard[10];
	

	float timerIconChange = 0.0f;
	float timerColorChange = 0.0f;



};

#endif