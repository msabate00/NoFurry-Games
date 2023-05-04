#include "ModuleScene_Level2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include <string> 
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Hostage.h"


ModuleScene_Level2::ModuleScene_Level2(bool startEnabled) : Module(startEnabled)
{

	// ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 2046;
	ground.h = 350;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;


}

ModuleScene_Level2::~ModuleScene_Level2()
{

}

// Load assets
bool ModuleScene_Level2::Start()
{
	LOG("Loading background assets");

	
	bool ret = true;

	return ret;
}

update_status ModuleScene_Level2::Update()
{

	if (hostage_num <= 0) {
		finalLevel->active = true;
	}

	int elapsed_time = updateTimer(start_time);

	return update_status::UPDATE_CONTINUE;


}

// Update: draw background
update_status ModuleScene_Level2::PostUpdate()
{

	printSkillIcon();
	printHostageIcon(hostage_num);
	printLifeIcon(life_num);



	printNum(getDigits(texture_num), LetraNum);

	printTime(getTimeString(elapsed_time).c_str(), Time);
	printPlayer1();
	return update_status::UPDATE_CONTINUE;


}


bool ModuleScene_Level2::CleanUp()
{
	App->collisions->Disable();
	App->player->Disable();
	App->enemy->Disable();
	App->audio->Disable();
	return true;
}



