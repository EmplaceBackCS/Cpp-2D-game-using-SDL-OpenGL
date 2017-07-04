#include "LeftBullets.h"

LeftBullets::LeftBullets()
{
}


LeftBullets::~LeftBullets()
{
}

//Non default constructor
LeftBullets::LeftBullets(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime, int size) : 
	Bullets(
		pos, 
		direction, 
		speed, 
		lifeTime,
		size)
{
}

//------------------------------------------- Draw function -----------------------------------------
//Draw our bullets. Textures and color/size go here. This is for the left direction bullet
void LeftBullets::draw(CSGengine::SpriteBatch& spriteBatch)
{
	CSGengine::ColorRGBA8;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	//This was copied and pasted from main game. This is just to test out our class, bad practice to do this!
	static CSGengine::GLTexture texture = CSGengine::ResourceManager::getTexture("Textures/Bullet_000_Left.png");

	CSGengine::ColorRGBA8 color;
	color.a = 255;
	color.b = 255;
	color.g = 255;
	color.r = 255;

	glm::vec4 posAndSize = glm::vec4(getPositionX() + 21, getPositionY() + 20, getSize() , getSize());

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}