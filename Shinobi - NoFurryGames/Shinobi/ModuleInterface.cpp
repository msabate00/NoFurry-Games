#include "ModuleInterface.h"

#include "ModuleRender.h"
#include <string> 
#include <iostream>
#include <vector>
#include "Application.h"
#include <chrono>
#include <thread>
#include <stack>

#include "ModuleWindow.h"

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
#include "ModuleBoss.h"
#include "ModuleAudio.h"
#include "Hostage.h"

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

	letraTrailColor[0] = App->textures->Load("Assets/Interface/Letra/LetraColor/Letra1.png");
	letraTrailColor[1] = App->textures->Load("Assets/Interface/Letra/LetraColor/Letra2.png");
	letraTrailColor[2] = App->textures->Load("Assets/Interface/Letra/LetraColor/Letra3.png");
	letraTrailColor[3] = App->textures->Load("Assets/Interface/Letra/LetraColor/Letra4.png");
	letraTrailColor[4] = App->textures->Load("Assets/Interface/Letra/LetraColor/Letra5.png");
	//LV1

	//App->scene_Level1_SecondFloor->Enable();
	SkillIcon = App->textures->Load("Assets/Interface/Color_use/SkillIcon/Rojo.png");
	HostageIcon = App->textures->Load("Assets/Interface/Color_use/Normal_icon/rescate.png");
	LifeIcon = App->textures->Load("Assets/Interface/Color_use/Normal_icon/vida.png");
	save = App->textures->Load("Assets/Interface/Color_use/Yellow/SAVE.png");
	dosPunt = App->textures->Load("Assets/Interface/Color_use/Yellow/dospunto.png");
	goIcon = App->textures->Load("Assets/Interface/go.png");
	skillPoint = App->textures->Load("Assets/Interface/Color_use/Yellow/5000.png");
	gameOverRed = App->textures->Load("Assets/Interface/Color_use/gameOver/gameoverRed.png");
	gameOverWhite = App->textures->Load("Assets/Interface/Color_use/gameOver/gameoverWhite.png");


	start_time = time(nullptr);

	//Boss
	Boss_life = App->textures->Load("Assets/Interface/Color_use/Blue/Boss/Boss_life.png");
	Boss_pow = App->textures->Load("Assets/Interface/Color_use/Blue/Boss/Boss.png");


	monedaFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/coin.wav");

	timerPR = 0;

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


	if (App->input->keys[SDL_SCANCODE_1] == KEY_DOWN) {
		coinNum++;
		App->audio->PlayFx(monedaFX);
	}

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
		printLetra();
		printNom();
		InsertCoin();
		App->render->Blit(LogoMedio, SCREEN_WIDTH - 225, SCREEN_HEIGHT - 50, SDL_FLIP_NONE, nullptr, 10);
	
	}

	if (App->scene_Level1->IsEnabled()) {
		timerPR += App->deltaTime++;
		//INTERFAZ PARA EL NIVEL 1

		if (App->player->haveUlti) {
			printSkillIcon();
		}
		printHostageIcon(hostage_num);
		printLifeIcon(App->life_num);
		printNum(texture_num);
		printPlayer1();


		if (gameover) {
			printgameOver();
		}

		if (gameChange) {
		printTime(getTimeString(elapsed_time).c_str());
		}
		else {
		displayTime(remaining_time--);
		if (remaining_time >= 0) {
			
			texture_num += 30;
		}
		stageClear();
		if (App->interface_module->remaining_time <= 0) {
			App->interface_module->remaining_time = 0;
		}
		}



		if (timerPR <= 1000) {
			player1Ready();
		}
		else {
			if (timerPR > 2000) {
				timerPR = 0;
			}
			else {
				timerPR = 1001;
			}
		}
		
		if (hostage_num == 0 ) {
			if (resetTimeHostage) {
			timerGonext = 0;
			timerGoIcon = 0;
			}
			timerGonext += App->deltaTime++;
			timerGoIcon += App->deltaTime++;
			printGoIcon();
			if (timerGonext <= 2000) {
				printGoNext();
				resetTimeHostage = false;
			}
			else {
				timerGonext = 2001;

			}
		}
		

		
			
	}
	else if (App->scene_Level2->IsEnabled()) {




		
		//INTERFAZ PARA EL NIVEL 2
			//INTERFAZ PARA EL NIVEL 1
		printSkillIcon();
		printHostageIcon(hostage_num);
		printLifeIcon(App->life_num);
		printNum(texture_num);
		printPlayer1();
	
		if (gameChange) {
			printTime(getTimeString(elapsed_time).c_str());
		}
		else {
			displayTime(remaining_time--);
			if (remaining_time >= 0) {

				texture_num += 30;
			}
			stageClear();
			if (App->interface_module->remaining_time <= 0) {
				App->interface_module->remaining_time = 0;
			}
		}
		timerPR += App->deltaTime;
		

		if (timerPR <= 1000) {
			player1Ready();
		}
		else {
			if (timerPR > 2000) {
				timerPR = 0;
			}
			else {
				timerPR = 1001;
			}
		}

		if (hostage_num == 0) {
			if (resetTimeHostage) {
				timerGonext = 0;
				timerGoIcon = 0;
			}
			timerGonext += App->deltaTime;
			timerGoIcon += App->deltaTime;
			printGoIcon();
			if (timerGonext <= 2000) {
				printGoNext();
				resetTimeHostage = false;
			}
			else {
				timerGonext = 999999;
			}
		}


	}
	else if (App->scene_Boss1->IsEnabled()) {
		//INTERFAZ PARA EL JEFE
		printSkillIcon();
		printLifeIcon(App->life_num);
		printNum(texture_num);
		//printTime(getTimeString(elapsed_time).c_str());


		if (gameChange) {
			printTime(getTimeString(elapsed_time).c_str());
		}
		else {
			displayTime(remaining_time--);
			texture_num += 30;
			stageClear();
			if (App->interface_module->remaining_time <= 0) {
				App->interface_module->remaining_time = 0;
			}
		}
		printPlayer1();
		printBossLife();
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
	delete[] letraTrailX;
	delete[] letraTrailY;

	return true;
}

//Main menu

void ModuleInterface::InsertCoin() {
	int IconPosition = 300;
	timer += App->deltaTime;
	
	int bufferSize = snprintf(nullptr, 0, "%d", coinNum) + 1;
	char* pointStr = new char[bufferSize];
	snprintf(pointStr, bufferSize, "%d", coinNum);

	if (NameColor) {
		std::string coinText = "insert coin " + std::string(pointStr);
		App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 80, App->scoreFontWhite, coinText.c_str());
		if (timer >= switchTimeInsertCoin) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}
	
}

void ModuleInterface::player1Ready() {
	int IconPosition = 300;
	App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 115, App->scoreFontWhite, "player 1 ready");
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
		App->render->Blit(LetraNomRed, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 150, SDL_FLIP_NONE, nullptr, 0);
		if (timer >= switchTime) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		App->render->Blit(LetraNomWhite, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 150, SDL_FLIP_NONE, nullptr, 0);
		if (timer >= switchTime) {
			NameColor = true;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}


}

//void ModuleInterface::printLetra() {
//
//	std::string filename = "Assets/Interface/Letra/LetraColor/Letra0.png";
//	Letra = App->textures->Load(filename.c_str());
//
//	App->render->Blit(Letra, letraGetX(), letraGetY(), SDL_FLIP_NONE, nullptr, 0);
//
//}

void ModuleInterface::printLetra() {
	std::string filename = "Assets/Interface/Letra/LetraColor/Letra0.png";
	Letra = App->textures->Load(filename.c_str());

	// 绘制拖尾效果
	for (int i = 0; i < trailLength; i++) {
		double trailX = letraTrailX[i];
		double trailY = letraTrailY[i];
		SDL_Texture* trailColorTexture = letraTrailColor[i];
		SDL_Rect trailRect = { static_cast<int>(trailX), static_cast<int>(trailY), 0, 0 };
		App->render->Blit(trailColorTexture, trailRect.x, trailRect.y, SDL_FLIP_NONE, nullptr, 0);
	}

	// 绘制当前位置
	SDL_Rect currentRect = { static_cast<int>(letraGetX()), static_cast<int>(letraGetY()), 0, 0 };
	App->render->Blit(Letra, currentRect.x, currentRect.y, SDL_FLIP_NONE, nullptr, 0);

	// 更新拖尾位置
	updateTrailPosition();

	// 存储当前位置到拖尾数组
	letraTrailX[0] = currentRect.x;
	letraTrailY[0] = currentRect.y;
}




void ModuleInterface::updateTrailPosition() {
	// 将之前的拖尾位置向后移动一位
	for (int i = trailLength - 1; i > 0; i--) {
		double deltaX = letraTrailX[i - 1] - letraTrailX[i];
		double deltaY = letraTrailY[i - 1] - letraTrailY[i];
		double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

		// 计算每个拖尾之间的距离
		double desiredDistance = 10.0;  // 设置每个拖尾之间的期望距离
		if (distance > desiredDistance) {
			double ratio = desiredDistance / distance;
			letraTrailX[i] = letraTrailX[i - 1] - ratio * deltaX;
			letraTrailY[i] = letraTrailY[i - 1] - ratio * deltaY;
		}
		else {
			letraTrailX[i] = letraTrailX[i - 1];
			letraTrailY[i] = letraTrailY[i - 1];
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

	if (A < 0) {
		// 停止在 (148, 34)
		letraX = 148;
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

	if (B < 0) {
		// 停止在 (148, 34)
		letraY = 34;
	}

	return letraY;
}




//LV1

void ModuleInterface::printPlayer1() {

	int IconPosition = 360;
	timer += App->deltaTime;


	if (NameColor) {
		
			App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, App->scoreFontBlue, "p1");
		
		if (timer >= switchTime) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		
			App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, App->scoreFontWhite, "p1");
		
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

	int IconPosition = 300;


	int bufferSize = snprintf(nullptr, 0, "%d", point) + 1;
	char* pointStr = new char[bufferSize];
	snprintf(pointStr, bufferSize, "%d", point);

	if (NameColor) {
		
		App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, App->scoreFontBlue, pointStr);
		
		if (timer >= switchTime) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		
		App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 220, App->scoreFontWhite, pointStr);
		
		if (timer >= switchTime) {
			NameColor = true;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}

	bufferSize = snprintf(nullptr, 0, "%d", rankingNum) + 1;
	char* rankStr = new char[bufferSize];
	snprintf(rankStr, bufferSize, "%d", rankingNum);
	std::string rankText = "h1 " + std::string(rankStr);
	App->fonts->BlitText(SCREEN_WIDTH - 150, SCREEN_HEIGHT - 220, App->scoreFontRed, rankText.c_str());


}

void ModuleInterface::printGoNext() {

	int IconPosition = 315;

	if (NameColor) {

		App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 130, App->scoreFontYellow, "go to next stage");

		if (timer >= switchTime) {
			NameColor = false;
			timer = 0.0f; // Reset Tiempo Contador
		}
	}
	
}

void ModuleInterface::printGoIcon() {


	//cout << timerGoIcon << endl;
	for (int i = 0; i < 2; i++)
	{	
		App->render->Blit(goIcon, SCREEN_WIDTH - GoIconPosition, SCREEN_HEIGHT - 80, SDL_FLIP_NONE, nullptr, 1);
		if (GoIconPosition <= -1634) {
			
			if (timerGoIcon >= 500) {
				GoIconPosition = -1580;
				timerGoIcon = 0;
			}
		}
		if (timerGoIcon >= 500) {
			GoIconPosition -= 18;
			timerGoIcon = 0;
		}		
	}
	//GoIconPosition = 200;
}

void ModuleInterface::printTime(std::string time_string) {

	int IconPosition = 70;
	int elapsed_time = updateTimer(start_time);
	remaining_time = getRemainingTime();
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

		App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, App->scoreFontYellow, pointStr);//

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

void ModuleInterface::displayTime(int timeInSeconds) {
	int minutes = timeInSeconds / 60;
	int seconds = timeInSeconds % 60;
	std::string timeString = std::to_string(minutes) + ":";

	if (seconds < 10) {
		timeString += "0";
	}

	timeString += std::to_string(seconds);

	std::vector<int> time_vector;
	for (char c : timeString) {
		if (isdigit(c)) {
			time_vector.push_back(c - '0');
		}
	}

	int IconPosition = 70;
	for (int i = 0; i < time_vector.size(); i++) {
		int bufferSize = snprintf(nullptr, 0, "%d", time_vector[i]) + 1;
		char* pointStr = new char[bufferSize];
		snprintf(pointStr, bufferSize, "%d", time_vector[i]);

		App->fonts->BlitText(SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, App->scoreFontYellow, pointStr);

		IconPosition -= 16;
		if (IconPosition == 54) {
			App->render->Blit(dosPunt, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 16, SDL_FLIP_NONE, nullptr, 0);
			IconPosition -= 16;
		}
	}
}


int ModuleInterface::getRemainingTime() {
	int elapsed_time = updateTimer(start_time);
	int remaining_time = total_time - elapsed_time;
	return remaining_time > 0 ? remaining_time : 0;
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

int ModuleInterface::updateTimer(time_t start_time) {
	time_t current_time = time(nullptr);
	int elapsed_seconds = difftime(current_time, start_time);
	return elapsed_seconds;
}

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

	//cout << time_string <<endl;
	
	return time_string;
}

void ModuleInterface::resetTimer() {
	start_time = time(nullptr);
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

//Boss
void ModuleInterface::printBossLife() {
	int IconPosition = 200;
	
	App->render->Blit(Boss_pow, SCREEN_WIDTH - 272, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);

	for (int i = 0; i < App->boss->life; i++)
	{
		App->render->Blit(Boss_life, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 200, SDL_FLIP_NONE, nullptr, 0);
		IconPosition -= 8;
	}


}

void ModuleInterface::stageClear() {

	//App->audio->PlayMusic("Assets/Audio/Music/Stage Clear.ogg");
	
	App->fonts->BlitText(SCREEN_WIDTH - 285, SCREEN_HEIGHT - 130, App->scoreFontWhite, "stage clear");
	
	App->render->Blit(SkillIcon, SCREEN_WIDTH - 250, SCREEN_HEIGHT - 98, SDL_FLIP_NONE, nullptr, 0);
	App->render->Blit(skillPoint, SCREEN_WIDTH - 215, SCREEN_HEIGHT - 98, SDL_FLIP_NONE, nullptr, 0);
	App->fonts->BlitText(SCREEN_WIDTH - 180, SCREEN_HEIGHT - 98, App->scoreFontWhite, "pts");

	App->fonts->BlitText(SCREEN_WIDTH - 370, SCREEN_HEIGHT - 66, App->scoreFontRed, "special bonus 20000pts");
	

}

void ModuleInterface::printgameOver() {
	int IconPosition = 250;
	gameOvertimer += App->deltaTime;

	//App->audio->PlayMusic("Assets/Audio/Music/Game_Over.ogg");
	if (NameColor) {
		App->render->Blit(gameOverRed, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 100, SDL_FLIP_NONE, nullptr, 0);
		if (gameOvertimer >= switchTimeGameOver) {
			NameColor = false;
			gameOvertimer = 0.0f; // Reset Tiempo Contador
		}
	}
	else {
		App->render->Blit(gameOverWhite, SCREEN_WIDTH - IconPosition, SCREEN_HEIGHT - 100, SDL_FLIP_NONE, nullptr, 0);
		if (gameOvertimer >= switchTimeGameOver) {
			NameColor = true;
			gameOvertimer = 0.0f; // Reset Tiempo Contador
		}
	}
	
}