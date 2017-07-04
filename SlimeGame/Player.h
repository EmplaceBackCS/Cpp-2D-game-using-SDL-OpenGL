#pragma once
#include "Human.h"
#include <CSGengine/InputManager.h>
#include <CSGengine/Camera2D.h>
#include "Bullets.h"

//Humans derive from the human class, rather than being it's own child, because
//Zombies will chase the humans and the player adopting all human features, will cause
//The zombies to chase the player this way

class Player : public Human
{
	public:
		//Constructors/destructor
		Player();
		virtual ~Player();

		//Initilize the player
		void init(
			float speed, 
			glm::vec2 pos, 
			CSGengine::InputManager* ipManager,
			CSGengine::Camera2D* camera);


		//Update the location
		virtual void update(
			const std::vector<std::string>& levelData,
			std::vector<Human*>& humans,
			std::vector<Zombie*>& zombies)override;

	private:
		CSGengine::InputManager* _ipManager;
		//Camera
		CSGengine::Camera2D* _camera;
};

