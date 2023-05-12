#include "ParticleBoss.h"
#include "Collider.h"

#include "SDL/include/SDL_timer.h"

ParticleBoss::ParticleBoss()
{
	position.SetToZero();
	speed.SetToZero();
}

ParticleBoss::ParticleBoss(const ParticleBoss& p) : anim(p.anim), position(p.position), speed(p.speed),
frameCount(p.frameCount), lifetime(p.lifetime)
{

}

bool ParticleBoss::Update()
{
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished())
			ret = false;

		// Update the position in the screen
		position.x += speed.x;
		position.y += speed.y;

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);

	}

	return ret;
}