#include "ModuleInputName.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleMapa1.h"
#include "ModuleScene_Level1.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL_scancode.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include <string> 
#include <vector>
#include <iostream>
#include <cmath>


ModuleInputName::ModuleInputName(bool startEnabled) : Module(startEnabled)
{

}

ModuleInputName::~ModuleInputName()
{

}




// Load assets
bool ModuleInputName::Start()
{

	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	SDL_SetRenderDrawColor(App->render->renderer, 128, 128, 128, 255);
	SDL_RenderClear(App->render->renderer);

	iconType[0] = App->textures->Load("Assets/Interface/Color_use/SkillIcon/Rojo.png");
	iconType[1] = App->textures->Load("Assets/Interface/Color_use/SkillIcon/Verde.png");
	iconType[2] = App->textures->Load("Assets/Interface/Color_use/SkillIcon/Azul.png");

	ranking = App->textures->Load("Assets/Interface/Color_use/SkillIcon/rank.png");
	currentAnimation = &backgroundAnim;

	dardosWhite = App->textures->Load("Assets/Interface/Color_use/SkillIcon/dardosWhite.png");
	dardosRed = App->textures->Load("Assets/Interface/Color_use/SkillIcon/dardosRed.png");
	ED = App->textures->Load("Assets/Interface/Color_use/SkillIcon/ED.png");

	return ret;
}

update_status ModuleInputName::Update()
{


	if (currentAnimation->HasFinished() || App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN) {

		App->fade->FadeToBlack(this, (Module*)App->mapa1, 20);
	}
	currentAnimation->Update();

	if (App->input->keys[SDL_SCANCODE_F9] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Level1, 20);
	}

	if (App->input->keys[SDL_SCANCODE_F10] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Level2, 20);
	}

	if (App->input->keys[SDL_SCANCODE_F11] == KEY_DOWN) {
		App->fade->FadeToBlack(this, (Module*)App->scene_Boss1, 20);
	}




	if (App->input->keys[SDL_SCANCODE_W] == KEY_DOWN) {

		if (dardosPositionY < 185) {
			dardosPositionY += 30;
		}
		cout << "dardosPositionX: " << dardosPositionX << endl;
		cout << "dardosPositionY: " << dardosPositionY << endl;
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_DOWN) {
		if (dardosPositionX == 215 && dardosPositionY == 65) {
			dardosPositionY -= 30;
		}
		else {
			if (dardosPositionY > 65) {
				dardosPositionY -= 30;
			}
		}
		cout << "dardosPositionX: " << dardosPositionX << endl;
		cout << "dardosPositionY: " << dardosPositionY << endl;
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_DOWN) {
		if (dardosPositionX == 215 && dardosPositionY == 35) {}
		else {
			if (dardosPositionX < 335 ) {
				dardosPositionX += 40;
			}
		}
		cout << "dardosPositionX: " << dardosPositionX << endl;
		cout << "dardosPositionY: " << dardosPositionY << endl;
	}
	if (App->input->keys[SDL_SCANCODE_D] == KEY_DOWN) {
		if (dardosPositionX == 215 && dardosPositionY == 35) {}
		else {
			if (dardosPositionX > 95) {
				dardosPositionX -= 40;
			}
		}
		cout << "dardosPositionX: " << dardosPositionX << endl;
		cout << "dardosPositionY: " << dardosPositionY << endl;
	}

	if (App->input->keys[SDL_SCANCODE_J] == KEY_DOWN) {
		printNomSelect(dardosPositionX, dardosPositionY);
	}


	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleInputName::PostUpdate()
{
	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	prinIcon();
	printTitle();
	printInput();
	printdardos();
	printNom();
	return update_status::UPDATE_CONTINUE;
}

void ModuleInputName::prinIcon() {

	int IconPosition1 = 20;
	int IconPosition2 = 20;
	timerIconChange += App->deltaTime;


	for (int i = 0; i < 9; i++) {
		for (int j = i - 1; j <= i + 1; j++) {
			int index = (j + i + 1) % 3;

			App->render->Blit(iconType[index], SCREEN_WIDTH - 370, SCREEN_HEIGHT - IconPosition1, SDL_FLIP_NONE, nullptr, 1);
		}
		IconPosition1 += 25;

		if (timerIconChange >= 1000) {
			SDL_Texture* temp = iconType[0];
			iconType[0] = iconType[1];
			iconType[1] = iconType[2];
			iconType[2] = temp;
			timerIconChange = 0;
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = i - 1; j <= i + 1; j++) {
			int index = (j + i + 1) % 3;

			App->render->Blit(iconType[index], SCREEN_WIDTH - 30, SCREEN_HEIGHT - IconPosition2, SDL_FLIP_NONE, nullptr, 1);
		}
		IconPosition2 += 25;

		if (timerIconChange >= 1000) {
			SDL_Texture* temp = iconType[0];
			iconType[0] = iconType[1];
			iconType[1] = iconType[2];
			iconType[2] = temp;
			timerIconChange = 0;
		}
	}

}

void ModuleInputName::printTitle() {
	int IconPositionY = 220;
	int IconPositionY2 = 200;

	App->fonts->BlitText(SCREEN_WIDTH - 318, SCREEN_HEIGHT - 220, App->scoreFontWhite, "your score");
	App->fonts->BlitText(SCREEN_WIDTH - 318, SCREEN_HEIGHT - 200, App->scoreFontWhite, "your name");
	//App->fonts->BlitText(SCREEN_WIDTH - 230, SCREEN_HEIGHT - 180, App->scoreFontWhite, "time");
	App->fonts->BlitText(SCREEN_WIDTH - 130, SCREEN_HEIGHT - 220, App->scoreFontWhite, std::to_string(App->interface_module->texture_num).c_str() );	
}


void ModuleInputName::printInput() {
	int InputPositionX = 320;
	int InputPositionY = 170;

	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 7; col++)
		{
			char character[2] = { input_array[row][col], '\0' };
			App->fonts->BlitText(SCREEN_WIDTH - InputPositionX, SCREEN_HEIGHT - InputPositionY, App->scoreFontWhite, character);

			InputPositionX -= 40;
		}

		InputPositionY -= 30;
		InputPositionX = 320;
	}
	App->render->Blit(ED, SCREEN_WIDTH - 199, SCREEN_HEIGHT - 20, SDL_FLIP_NONE, nullptr, 1);
}


void ModuleInputName::printdardos() {
	App->interface_module->timer += App->deltaTime;

	if (App->interface_module->NameColor) {

		App->render->Blit(dardosRed, SCREEN_WIDTH - dardosPositionX, SCREEN_HEIGHT - dardosPositionY, SDL_FLIP_NONE, nullptr, 1);
		if (App->interface_module->timer >= App->interface_module->switchTime) {
			App->interface_module->NameColor = false;
			App->interface_module->timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {

		App->render->Blit(dardosWhite, SCREEN_WIDTH - dardosPositionX, SCREEN_HEIGHT - dardosPositionY, SDL_FLIP_NONE, nullptr, 1);
		if (App->interface_module->timer >= App->interface_module->switchTime) {
			App->interface_module->NameColor = true;
			App->interface_module->timer = 0.0f; // Reset Tiempo Contador
		}
	}

	//X是 -40，Y是-30
}

void ModuleInputName::printNomSelect(int nameposX, int nameposY) {

	switch (nameposX) {
	case 335:
		letraposX = 0;
		break;
	case 295:
		letraposX = 1;
		break;
	case 255:
		letraposX = 2;
		break;
	case 215:
		letraposX = 3;
		break;
	case 175:
		letraposX = 4;
		break;
	case 135:
		letraposX = 5;
		break;
	case 95:
		letraposX = 6;
		break;
	default:
		letraposX = -1; // 如果输入的x值不在列表中，则设置为-1表示无效
		break;
	}
	switch (nameposY) {
	case 185:
		letraposY = 0;
		break;
	case 155:
		letraposY = 1;
		break;
	case 125:
		letraposY = 2;
		break;
	case 95:
		letraposY = 3;
		break;
	case 65:
		letraposY = 4;
		break;
	default:
		letraposY = -1; // 如果输入的y值不在列表中，则设置为-1表示无效
		break;
	}

	cout << input_array[letraposY][letraposX] << endl;
	cout << myNamelist << endl;
	

	switch (myNamelist) {
	case 0:
		myName[0] = input_array[letraposY][letraposX];
		break;
	case 1:
		myName[1] = input_array[letraposY][letraposX];
		break;
	case 2:
		myName[2] = input_array[letraposY][letraposX];
		break;
	default:
		letraposY = -1; // 如果输入的y值不在列表中，则设置为-1表示无效
		break;
	}


	if (myNamelist == 3) {
		myNamelist = 3;
	}
	else {
	myNamelist += 1;
	}
}

void ModuleInputName::printNom() {


	int NamePositionX = 150;

	for (int i = 0; i < myNamelist; i++)
	{
		char namecharacter[2] = { myName[i], '\0' };
		App->fonts->BlitText(SCREEN_WIDTH - NamePositionX, SCREEN_HEIGHT - 200, App->scoreFontWhite, namecharacter);
		NamePositionX -= 16;
	}
}
