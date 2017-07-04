#pragma once
#include "Guns.h"

//---------------------------------------- Was remade to a land mine for a different effect then just shooting------------------------
//----------------------------------------This now just places a bomb/mine at the player and won't move at all------------------------
//------------------------------------------------------------------------------------------------------------------------------------

class GiantSlowGun :
	public Guns
{
	public:
		GiantSlowGun();
		virtual ~GiantSlowGun();

		//Override function to give it it's own texture/effect
		virtual void getGun(
			std::vector<Bullets*>& bullets,
			const CSGengine::InputManager* im,
			const  Player* player,
			const CSGengine::Camera2D& camera)override;
};

