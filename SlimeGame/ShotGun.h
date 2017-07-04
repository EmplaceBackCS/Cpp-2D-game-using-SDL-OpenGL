#pragma once
#include "Guns.h"
class ShotGun :	public Guns
{
	public:
		ShotGun();
		virtual ~ShotGun();

		//Get the gun, this is the override function from the gun class
		virtual void getGun(
			std::vector<Bullets*>& bullets,
			const CSGengine::InputManager* im,
			const  Player* player,
			const CSGengine::Camera2D& camera)override;

};

