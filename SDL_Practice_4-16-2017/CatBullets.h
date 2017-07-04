#pragma once
#include "Projectile.h"
class CatBullets :
	public Projectile
{
public:
	//--------------------------- Constructors/desturctors ---------------------------
	CatBullets();
	CatBullets(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime);
	virtual ~CatBullets();

	//------------------------------ Override functiuons --------------------------------
	virtual void draw(CSGengine::SpriteBatch& spriteBatch) override;
};

