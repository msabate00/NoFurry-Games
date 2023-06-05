#include "ModuleAudio.h"

#include "Application.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_FX; ++i)
		soundFx[i] = nullptr;
}

ModuleAudio::~ModuleAudio()
{

}

bool ModuleAudio::Init()
{
	LOG("Loading Audio Mixer");
	bool ret = true;

	//Initialize audio subsystem
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//Load support for OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}
	App->audio->SetMusicVolume(40);
	saltarFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Jump.wav");
	saltarPlataformaFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Plataform_Jump.wav");
	efectoSaltoPlataformaFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Efecto_SaltoPlataforma.wav");
	ataqueFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Attack.wav");
	shurikenAtaqueFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Shuriken_Attack.wav");
	morirFX = App->audio->LoadFx("Assets/Audio/Effects/main character/Die.wav");
	StageClearFX = App->audio->LoadFx("Assets/Audio/Music/Stage Clear.ogg");
	GameOverFX = App->audio->LoadFx("Assets/Audio/Music/Game_Over.ogg");
	ULTIFX = App->audio->LoadFx("Assets/Audio/Effects/main character/ULTIFX.wav");
	SalvadoFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/Rescue.wav");
	RecieveDamageFX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Get_Shooted(right area).wav");
	FuegoFX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Fire_Boss.wav");
	RecieveDamage_2FX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Get_Shooted.wav");
	Boss_DieFX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Boss_Die.wav");
	BoladeFuegoFX = App->audio->LoadFx("Assets/Audio/Effects/Boss/Fire_Boss.wav");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/EnemiesDie.wav");
	scoreboardFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/ScoreboardFX.wav");
	scoreboardFX2 = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/ScoreboardFX2.wav");
	Music_scoreboardFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/Musica_Scoreboard.wav");
	monedaFX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/coin.wav");
	Mission1FX = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Mission/MISSION-1(intro).wav");
	//hostageDestroyedFx = App->audio->LoadFx("Assets/Audio/Effects/Generic Sounds/Generic/EnemiesDie.wav");

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	for (uint i = 0; i < MAX_FX; ++i)
	{
		if (soundFx[i] != nullptr)
			Mix_FreeChunk(soundFx[i]);
	}

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			// Warning: This call blocks the execution until fade out is done
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

uint ModuleAudio::LoadFx(const char* path)
{
	uint ret = MAX_FX; // Valor especial para indicar un error
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		for (ret = 0; ret < MAX_FX; ++ret)
		{
			if (soundFx[ret] == nullptr)
			{
				soundFx[ret] = chunk;
				break;
			}
		}

		if (ret == MAX_FX)
		{
			LOG("Cannot load more sound effects. Maximum reached.");
			Mix_FreeChunk(chunk); // Liberar el chunk cargado si no hay espacio
		}
	}

	return ret;
}

bool ModuleAudio::PlayFx(uint index, int repeat)
{
	if (index >= MAX_FX || soundFx[index] == nullptr)
	{
		LOG("Invalid sound effect index");
		return false;
	}

	Mix_PlayChannel(-1, soundFx[index], repeat);
	return true;
}

void ModuleAudio::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}
/*
bool ModuleAudio::ReleaseAudio()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	for (uint i = 0; i < MAX_FX; ++i)
	{
		if (soundFx[i] != nullptr)
			Mix_FreeChunk(soundFx[i]);
	}
	return true;
}
*/