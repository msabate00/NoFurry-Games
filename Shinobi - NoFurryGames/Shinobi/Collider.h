#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		HOSTAGE,
		CHANGE_LEVEL,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	SDL_Rect GetRect();


	void SetSize(int w, int h);

	bool Intersects(const SDL_Rect& r) const;

	void SetActive(bool active);
	bool GetActive();

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	bool active = true;
	Type type;
	Module* listener = nullptr;
};


#endif // !__COLLIDER_H__

