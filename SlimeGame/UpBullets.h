#pragma once
#include "Bullets.h"
class UpBullets : public Bullets
{
	public:
		UpBullets();
		virtual ~UpBullets();
		//Non default constructor
		//Needed for the emplace back vector function in main game
		UpBullets(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime, int size);

		//Override our parent class
		virtual void function()override {}

		//Draw our bullets in the corret way
		virtual void draw(CSGengine::SpriteBatch& spriteBatch)override;
};

