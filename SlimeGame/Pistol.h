#pragma once
#include "Guns.h"
class Pistol :	public Guns
{
	public:
		Pistol();
		virtual ~Pistol();

		//For mouse input
		virtual void getGun(
			std::vector<Bullets*>& bullets, 
			const CSGengine::InputManager* im,
			const  Player* player, 
			const CSGengine::Camera2D& camera)override;

		//For the right arrow key, the bullets should face the right way
		virtual void getGunForRightArrowKey(
			std::vector<Bullets*>& bullets,
			const Player* player, 
			const CSGengine::Camera2D& camera)override;
		//For the left arrow key, bullets should face the left way
		virtual void getGunForLeftArrowKey(
			std::vector<Bullets*>& bullets, 
			const Player* player, 
			const CSGengine::Camera2D& camera)override;
		//For up down arrow key
		virtual void getGunForDownArrowKey(
			std::vector<Bullets*>& bullets,
			const Player* player,
			const CSGengine::Camera2D& camera)override;
		//for up arrow key
		virtual void getGunForUpArrowKey(
			std::vector<Bullets*>& bullets,
			const Player* player,
			const CSGengine::Camera2D& camera)override;

	private:
		
};

