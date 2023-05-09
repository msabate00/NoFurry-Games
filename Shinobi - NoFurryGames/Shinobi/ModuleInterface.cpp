#include "ModuleRender.h"
#include <string> 
#include <iostream>
#include <vector>
#include "Application.h"
#include <chrono>
#include <thread>
#include <stack>

#include "ModuleWindow.h"
#include "ModuleInterface.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleScene_Level1.h"
#include "ModuleScene_Level2.h"
#include "ModuleScene_Boss1.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include "ModuleScene_MainMenu.h"

#include <string> 
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "Hostage.h"
#include "SDL/include/SDL_scancode.h"


#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"





using namespace std;

ModuleInterface::ModuleInterface(bool startEnabled) : Module(startEnabled)
{

}

ModuleInterface::~ModuleInterface()
{

}

bool ModuleInterface::Start()
{
	bool ret = true;


	//MainMenu
	LogoMedio = App->textures->Load("Assets/Interface/Color_use/White/Sega.png");
	LetraNomRed = App->textures->Load("Assets/Interface/Color_use/Red/Shinobi/SHINOBI.png");
	LetraNomWhite = App->textures->Load("Assets/Interface/Color_use/White/Shinobi/SHINOBI.png");
	LetraIconC = App->textures->Load("Assets/Interface/Color_use/White/Icon/Sega.png");
	LetraYear = App->textures->Load("Assets/Interface/Color_use/White/Icon/1987.png");

	//LV1

	//App->scene_Level1_SecondFloor->Enable();
	SkillIcon = App->textures->Load("Assets/Interface/Color_use/SkillIcon/Rojo.png");
	HostageIcon = App->textures->Load("Assets/Interface/Color_use/Normal_icon/rescate.png");
	LifeIcon = App->textures->Load("Assets/Interface/Color_use/Normal_icon/vida.png");
	save = App->textures->Load("Assets/Interface/Color_use/Yellow/SAVE.png");
	dosPunt = App->textures->Load("Assets/Interface/Color_use/Yellow/dospunto.png");
	start_time = time(nullptr);
	return ret;
}

// Called every draw update
update_status ModuleInterface::PreUpdate()
{
	

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleInterface::Update()
{

	int elapsed_time = updateTimer(start_time);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleInterface::PostUpdate()
{

	//INTERFAZ COMUN PARA TODO EL JUEGO

	if (App->scene_Level1->IsEnabled() || App->scene_Level2->IsEnabled() || App->scene_Boss1->IsEnabled()) {
		//INTERFAZ PARA TODOS LOS NIVELES JUGABLES
	
	}
	if (App->scene_MainMenu->IsEnabled()) {




		printYear();
		printIconC();
		printNom();
		printLetra();
		InsertCoin();
		App->render->Blit(LogoMedio, SCREEN_WIDTH - 225, SCREEN_HEIGHT - 50, SDL_FLIP_NONE, nullptr, 10);
	
	}

	if (App->scene_Level1->IsEnabled()) {

	
		//INTERFAZ PARA EL NIVEL 1
		printSkillIcon();
		printHostageIcon(hostage_num);
		printLifeIcon(App->life_num);
		printNum(texture_num);
		printTime(getTimeString(elapsed_time).c_str(), Time);
		printPlayer1();


	}
	else if (App->scene_Level2->IsEnabled()) {
		//INTERFAZ PARA EL NIVEL 2


	}
	else if (App->scene_Boss1->IsEnabled()) {
		//INTERFAZ PARA EL JEFE
	
	
	
	}


	//INTERFAZ DEL GODMODE
	if (App->debugMode && App->showDebug) {
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 240);
		SDL_Rect dstRect{
		(int)(-App->render->camera.x * 0) + 0 * SCREEN_SIZE,
		(int)(-App->render->camera.y * 0) + 0 * SCREEN_SIZE,
		144 * SCREEN_SIZE, 97 * SCREEN_SIZE };

		SDL_RenderFillRect(App->render->renderer, &dstRect);
		App->fonts->BlitText(0, 0, App->debugFontWhite, "f1 - t0ggle debugm0de");
		App->fonts->BlitText(0, 8, App->debugFontWhite, "f2 - weap0n switcher");
		if (App->godMode) {
			App->fonts->BlitText(0, 16, App->debugFontWhite, "f3 - t00gle g0dm0de -0n");
		}
		else {
			App->fonts->BlitText(0, 16, App->debugFontWhite, "f3 - t00gle g0dm0de -0ff");
		}
		App->fonts->BlitText(0, 24, App->debugFontWhite, "f4 - t00gle sh0wrect");
		App->fonts->BlitText(0, 32, App->debugFontWhite, "f5 - l0ad mainmenu");
		App->fonts->BlitText(0, 40, App->debugFontWhite, "f6 - hide debugmenu");
		App->fonts->BlitText(0, 48, App->debugFontWhite, "f7 - xxxxxxx");
		App->fonts->BlitText(0, 56, App->debugFontWhite, "f8 - xxxxxxx");
		App->fonts->BlitText(0, 64, App->debugFontWhite, "--- in main menu ---");
		App->fonts->BlitText(0, 72, App->debugFontWhite, "f9 - l0ad level1");
		App->fonts->BlitText(0, 80, App->debugFontWhite, "f10 - l0ad level2");
		App->fonts->BlitText(0, 88, App->debugFontWhite, "f11 - l0ad level_b0ss");
	}
	else if (App->debugMode && !App->showDebug) {
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 240);
		SDL_Rect dstRect{
		(int)(-App->render->camera.x * 0) + 0 * SCREEN_SIZE,
		(int)(-App->render->camera.y * 0) + 0 * SCREEN_SIZE,
		120 * SCREEN_SIZE, 12 * SCREEN_SIZE };
		SDL_RenderFillRect(App->render->renderer, &dstRect);
		App->fonts->BlitText(0, 0, App->debugFontWhite, "f6 - sh0w debugmenu");
	}


	return update_status::UPDATE_CONTINUE;
}

bool ModuleInterface::CleanUp()
{


	return true;
}

//Main menu

void ModuleInterface::InsertCoin() {
	int IconPosition = 280;
	timer += App->deltaTime;
	
	if (NameColor) {
		App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 80, App->scoreFontWhite, "insert coin");
		if (timer >= switchTimeInsertCoin) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}
	
}


void ModuleInterface::printLetra() {

	std::string filename = "Assets/Interface/Letra/LetraColor/Letra0.png";
	Letra = App->textures->Load(filename.c_str());

	App->render->Blit(Letra, letraGetX(), letraGetY(), SDL_FLIP_NONE, nullptr, 0);

}

void ModuleInterface::printYear() {
	int IconPosition = 50;


	//App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, scoreFont, "1987");

	App->render->Blit(LetraYear, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);



}

void ModuleInterface::printIconC() {

	int IconPosition = 100;
	for (int i = 0; i < 5; i++)

		App->render->Blit(LetraIconC, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
}

void ModuleInterface::printNom() {


	int IconPosition = 250;
	timer += App->deltaTime;


	if (NameColor) {
		App->render->Blit(LetraNomRed, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
		if (timer >= switchTime) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		App->render->Blit(LetraNomWhite, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
		if (timer >= switchTime) {
			NameColor = true;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}


}




double ModuleInterface::letraGetX() {
	if (letraY > 32 && letraY < 36 && letraX > 146 && letraX < 150) {
		//cout << "X yes" << endl;
		letraX = 148;
	}
	else {
		letraX = CENTER_X + A * sin(angle * M_PI / 270.0);
		angle += ROTATION_SPEED;
		A = A - 0.7;
		//cout << "X: " << letraX << endl;
	}
	return letraX;
}
double ModuleInterface::letraGetY() {
	if (letraY > 32 && letraY < 36 && letraX > 146 && letraX < 150) {
		//cout << "Y yes" << endl;
		letraY = 34;
	}
	else {
		letraY = CENTER_Y + B * cos(angle * M_PI / 270.0);
		angle += ROTATION_SPEED;
		B = B - 0.6, 5;
		//cout << "Y: " << letraY << endl;
	}

	return letraY;
}




//LV1

void ModuleInterface::printPlayer1() {

	int IconPosition = 360;
	timer += App->deltaTime;





	if (NameColor) {
		for (int i = 0; i < 2; i++)
		{
			App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, App->scoreFontBlue, "p1");
		}
		if (timer >= switchTime) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, App->scoreFontWhite, "p1");
		}
		if (timer >= switchTime) {
			NameColor = true;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}

}



void ModuleInterface::printSkillIcon() {

	bool sur = App->render->Blit(SkillIcon, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
	if (!sur) {
		//cout << "error" << endl;
	}


}

void ModuleInterface::printHostageIcon(int hostage) {

	//App->render->Blit(SkillIcon, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
	int IconPosition = 340;

	for (int i = 0; i < hostage; i++)
	{
		App->render->Blit(HostageIcon, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 8;
	}

	App->render->Blit(save, SCREEN_WIDTH - 356, SCREEN_HEIGHT - 15, SDL_FLIP_NONE, nullptr, 0);

}
void ModuleInterface::printLifeIcon(int life) {


	int IconPosition = 350;
	for (int i = 0; i < life; i++)
	{
		App->render->Blit(LifeIcon, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 8;
	}

}


void ModuleInterface::printNum(int point) {

	int IconPosition = 250;

	int bufferSize = snprintf(nullptr, 0, "%d", point) + 1;
	char* pointStr = new char[bufferSize];
	snprintf(pointStr, bufferSize, "%d", point);

	App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, App->scoreFontRed, pointStr);

	/*
		for (int i = 0; i < number.size(); i++)
		{
			std::string filename = "Assets/Interface/Color_use/Red/Rojo_Numeros/Rojo_" + std::to_string(number[i]) + ".png";
			LetraNum = App->textures->Load(filename.c_str());

			App->render->Blit(LetraNum, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, SDL_FLIP_NONE, nullptr, 0);
			IconPosition -= 16;
		}
		*/
}

void ModuleInterface::printTime(std::string time_string, SDL_Texture* Time) {

	int IconPosition = 70;
	int elapsed_time = updateTimer(start_time);
	time_string = getTimeString(elapsed_time);

	std::vector<int> time_vector;
	for (char c : time_string) {
		if (isdigit(c)) {
			time_vector.push_back(c - '0');
		}
	}
	//App->render->Blit(dosPunt, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 150, SDL_FLIP_NONE, nullptr, 0);

	for (int i = 0; i < time_vector.size(); i++)
	{

		int bufferSize = snprintf(nullptr, 0, "%d", time_vector[i]) + 1;
		char* pointStr = new char[bufferSize];
		snprintf(pointStr, bufferSize, "%d", time_vector[i]);

		App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, App->scoreFontYellow, pointStr);

		/*	std::string filename = "Assets/Interface/Color_use/Yellow/Yellow_Numeros/Yellow_" + std::to_string(time_vector[i]) + ".png";
			SDL_Texture* Time = App->textures->Load(filename.c_str());
			App->render->Blit(Time, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);*/
		IconPosition -= 16;
		if (IconPosition == 54) {
			App->render->Blit(dosPunt, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
			IconPosition -= 16;
		}

		string time_string = getTimeString(elapsed_time);
		//cout << "Remaining time: " << time_string << endl;

		//cout << IconPosition << endl;
	}
	//App->render->Blit(Time, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 150, SDL_FLIP_NONE, nullptr, 0);

}

int ModuleInterface::updateTimer(time_t start_time) {
	time_t current_time = time(nullptr);
	int elapsed_seconds = difftime(current_time, start_time);
	return elapsed_seconds;
}
//Suma tiempo
/*
std::string ModuleRender::getTimeString(int elapsed_time) {
	int minutes = elapsed_time / 60;
	int seconds = elapsed_time % 60;
	std::string time_string = std::to_string(minutes) + ":";

	if (seconds < 10) {
		time_string += "0";
	}
	time_string += std::to_string(seconds);

	return time_string;
}*/

//Resta tiempo , int total_time
std::string ModuleInterface::getTimeString(int elapsed_time) {
	int remaining_seconds = total_time - elapsed_time;
	if (remaining_seconds < 0) {
		remaining_seconds = 0;
	}
	int minutes = remaining_seconds / 60;
	int seconds = remaining_seconds % 60;
	std::string time_string = std::to_string(minutes) + ":";

	if (seconds < 10) {
		time_string += "0";
	}
	time_string += std::to_string(seconds);

	return time_string;
}



std::vector<int> ModuleInterface::getDigits(int number) {
	std::vector<int> digits;

	if (number == 0) {
		digits.push_back(0);
		return digits;
	}

	while (number != 0) {
		int digit = number % 10;
		digits.push_back(digit);
		number /= 10;
	}

	std::reverse(digits.begin(), digits.end());

	return digits;

}


