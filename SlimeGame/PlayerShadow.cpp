#include "PlayerShadow.h"

PlayerShadow::PlayerShadow():
	_pos(0),
	_direction(0),
	_speed(1.0f),
	_lifeTime(1)
{
}


PlayerShadow::~PlayerShadow()
{
}

//--------------------------------------- Non default constructor -----------------------
PlayerShadow::PlayerShadow(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime) :
	_pos(pos),
	_direction(direction),
	_speed(speed),
	_lifeTime(lifeTime)
{
}

//Override from the bullet class to create trails of fire
bool PlayerShadow::update()
{
	_pos += _direction / _speed;
	//Make sure every frame we update, we shorten the lifetime
	//of our bullet
	_lifeTime -= 1;

	if (_lifeTime == 0)
	{
		return true;
	}

	//Returns false if life time isn't 0
	return false;
}

//Draw our bullets. Textures and color/size go here
void PlayerShadow::draw(CSGengine::SpriteBatch& spriteBatch)
{
	CSGengine::ColorRGBA8;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	//This was copied and pasted from main game. This is just to test out our class, bad practice to do this!
	static CSGengine::GLTexture texture = CSGengine::ResourceManager::getTexture("Textures/purple-ball.png");

	CSGengine::ColorRGBA8 color;
	color.a = 255;
	color.b = 255;
	color.g = 0;
	color.r = 255;

	glm::vec4 posAndSize = glm::vec4(_pos.x, _pos.y, 60, 60);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}