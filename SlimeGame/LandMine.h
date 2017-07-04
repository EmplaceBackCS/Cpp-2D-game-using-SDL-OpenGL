#pragma once
#include "Bullets.h"


class LandMine :public Bullets
{
public:
		LandMine();
		virtual ~LandMine();

		//Non default
		LandMine(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime, int size);

		//Override the parent class
		virtual void draw(CSGengine::SpriteBatch& spriteBatch)override;
		//Just to remove the virtual pure
		virtual void function()override {}
};

