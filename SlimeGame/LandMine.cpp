#include "LandMine.h"

LandMine::LandMine()
{
}


LandMine::~LandMine()
{
}

//------------------------------------ Non default constructor ---------------------
LandMine::LandMine(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime, int size) :
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
void LandMine::draw(CSGengine::SpriteBatch& spriteBatch)
{
	CSGengine::ColorRGBA8;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	//This was copied and pasted from main game. This is just to test out our class, bad practice to do this!
	static CSGengine::GLTexture texture = CSGengine::ResourceManager::getTexture("Textures/mine_1.png");
	//255, 192, 203
	CSGengine::ColorRGBA8 color;
	color.a = 255;
	color.b = 203;
	color.g = 192;
	color.r = 0;

	glm::vec4 posAndSize = glm::vec4(getPositionX() + 21, getPositionY() + 20, getSize() + 10, getSize() + 10);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}