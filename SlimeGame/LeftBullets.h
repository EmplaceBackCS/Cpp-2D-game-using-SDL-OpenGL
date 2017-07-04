#pragma once
#include "Bullets.h"
class LeftBullets : public Bullets
{
public:
	LeftBullets();
	virtual ~LeftBullets();

	//Life time, number of frames it will be alive for
	//Non default constructor
	LeftBullets(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime, int size);

	//Override from the bullet class. 
	virtual void function()override {}

	//This will draw bullets pointing to the left side
	virtual void draw(CSGengine::SpriteBatch& spriteBatch)override;
};

