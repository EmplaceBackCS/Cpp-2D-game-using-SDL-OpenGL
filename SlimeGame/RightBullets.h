#pragma once
#include "Bullets.h"
class RightBullets : public Bullets
{
	public:
		RightBullets();
		virtual ~RightBullets();
		//Non default constructor
		//Needed for the emplace back vector function in main game
		RightBullets(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime, int size);

		//Overrite the virtual pure function from the parnet
		virtual void function()override {}

		//Draw our sprite
		virtual void draw(CSGengine::SpriteBatch& spriteBatch)override;

	private:
};

