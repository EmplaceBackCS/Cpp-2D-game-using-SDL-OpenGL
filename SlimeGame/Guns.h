#pragma once
#include <vector>
#include <CSGengine/InputManager.h>
#include <CSGengine/Camera2D.h>
#include "Player.h"
#include <glm/glm.hpp>
//All the bullets
#include "Bullets.h"
#include "LeftBullets.h"
#include "RightBullets.h"
#include "DownBullets.h"
#include "LandMine.h"
#include "UpBullets.h"
#include <iostream>
class Guns
{
	public:
		Guns();
		virtual ~Guns();

		//This will be for mouse
		virtual void getGun(std::vector<Bullets*>& bullets, 
							const CSGengine::InputManager* im,
							const  Player* player, 
							const CSGengine::Camera2D& camera) = 0;

		//This will be for arrow keys
		virtual void getGunForRightArrowKey(std::vector<Bullets*>& bullets, const Player* player, const CSGengine::Camera2D& camera) {}
		virtual void getGunForLeftArrowKey(std::vector<Bullets*>& bullets, const Player* player, const CSGengine::Camera2D& camera) {}
		virtual void getGunForDownArrowKey(std::vector<Bullets*>& bullets, const Player* player, const CSGengine::Camera2D& camera) {}
		virtual void getGunForUpArrowKey(std::vector<Bullets*>& bullets, const Player* player, const CSGengine::Camera2D& camera) {}

	protected:
		glm::vec2 _mouseCoords;
		glm::vec2 _direction;
		CSGengine::Camera2D _camera;
		static const int _LIFE_TIME = 100;
		static const int _BULLET_SIZE = 25;//Old size -> 15;
};

