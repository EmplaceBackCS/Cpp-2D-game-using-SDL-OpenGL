#pragma once
#include "Bullets.h"

class DownBullets : public Bullets
{
	public:
		DownBullets();
		virtual ~DownBullets();
		//Non default constructor
		DownBullets(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime, int size);

		//Overload the virutal pure from our parent class
		virtual void function()override {}

		//draw our bullets
		virtual void draw(CSGengine::SpriteBatch& spriteBatch)override;
};

