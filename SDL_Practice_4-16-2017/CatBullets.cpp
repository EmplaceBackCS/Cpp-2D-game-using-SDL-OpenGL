#include "CatBullets.h"

CatBullets::CatBullets():
	Projectile()
{
}

CatBullets::CatBullets(
	glm::vec2 pos, 
	glm::vec2 direction, 
	float speed, 
	int lifeTime):
		Projectile(pos, direction, speed, lifeTime)
{
}

CatBullets::~CatBullets()
{
}

//-------------------------------- override functions ---------------------------
//draw function from the parent class
void CatBullets::draw(CSGengine::SpriteBatch& spriteBatch)
{
	CSGengine::ColorRGBA8;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	//This was copied and pasted from main game. This is just to test out our class, bad practice to do this!
	static CSGengine::GLTexture texture = CSGengine::ResourceManager::getTexture("Textures/catndog/png/cat/Jump (5).png");

	CSGengine::ColorRGBA8 color;
	color.a = 255;
	color.b = 255;
	color.g = 255;
	color.r = 255;

	glm::vec4 posAndSize = glm::vec4(getPositionX(), getPositionY(), 150, 150);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}