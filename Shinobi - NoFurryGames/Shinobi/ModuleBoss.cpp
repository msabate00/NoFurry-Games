#include "ModuleBoss.h"
#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level1_SecondFloor_Enemies.h"

#include "Enemy.h"
#include "Enemy_Basic.h"
#include "Hostage.h"
#include "EnemyBrownShield.h"
#include "EnemyPurpleShield.h"

#include <iostream>

using namespace std;


ModuleBoss::ModuleBoss(bool startEnabled) : Module(startEnabled) {

}

ModuleBoss::~ModuleBoss()
{
}

bool ModuleBoss::Start()
{
	return true;
}

update_status ModuleBoss::Update()
{


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBoss::PostUpdate()
{


	return update_status::UPDATE_CONTINUE;
}

bool ModuleBoss::CleanUp()
{


	return true;
}

void ModuleBoss::OnCollision(Collider* c1, Collider* c2)
{
}
