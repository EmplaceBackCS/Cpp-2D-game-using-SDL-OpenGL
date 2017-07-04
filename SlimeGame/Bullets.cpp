#include "Bullets.h"
#include "Zombie.h"
#include <algorithm>


Bullets::Bullets() :
	_position(0.0f),
	_speed(0.0f),
	_direction(0.0f),
	_lifeTime(1),
	_damage(1.0f),
	_size(20)
{
}

Bullets::~Bullets()
{ 
}

Bullets::Bullets(glm::vec2 pos, glm::vec2 direction, float speed, float lifeTime, int size):
	_position(pos),
	_direction(direction),
	_speed(speed),
	_lifeTime(lifeTime),
	_size(size)
{

}

//----------------------------------------- Draw function ----------------------------------------
void Bullets::draw(CSGengine::SpriteBatch& spriteBatch)
{
	CSGengine::ColorRGBA8;
	const static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	//This was copied and pasted from main game. This is just to test out our class, bad practice to do this!
	static CSGengine::GLTexture texture = CSGengine::ResourceManager::getTexture("Textures/Bullet_000_Left.png");

	CSGengine::ColorRGBA8 color;
	color.a = 255;
	color.b = 255;
	color.g = 255;
	color.r = 255;

	glm::vec4 posAndSize = glm::vec4( _position.x + 21, _position.y + 20, _size, _size);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

//Check if we need to update. If it returns true, it will update the position.
//False will cause it to die out
bool Bullets::update()
{
	_position += (_direction * _speed);
	//Make sure every frame we update, we shorten the lifetime
	//of our bullet
	_lifeTime--;

	if (_lifeTime == 0)
	{
		return true;
	}

	////Returns false if life time isn't 0
	return false;
}

bool Bullets::checkBulletCollision(std::vector<Zombie*> zombie, int& index)
{
	static const float MIN_DISTANCE = 30 + 30;
	static const int BULLET_RADIUS = 30;
	for (unsigned int i = 0; i < zombie.size(); i++)
	{
		//Going to use circular collision
		glm::vec2 centerPosA = _position + glm::vec2(BULLET_RADIUS);
		glm::vec2 centerPosB = zombie[i]->getPos() + glm::vec2(BULLET_RADIUS);

		//Dist vect for distance vector
		glm::vec2 distVect = centerPosA - centerPosB;

		//This will give us the length of both center agents when they collide
		float distance = glm::length(distVect);

		float collisionDepths = MIN_DISTANCE - distance;

		//If our math was right, then when we collide with a bullet
		//Collision depths should be greater then 0!
		if (collisionDepths > 0)
		{
			return index = i;
		}
	}
	return false;
}
//------------------------------ Check bullet collision here -------------------
//Collision needs a bit of help
//Needs update when we can figure out a better formula
bool Bullets::checkBulletCollisionWithWorld(const std::vector<std::string>& levelData)
{
	static const float TILE_WIDTH = 64.0f;
	glm::ivec2 gridPosition;

	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	//Check if any one is outside the world
	if (gridPosition.x < 0 || gridPosition.x >= levelData[0].length() ||
		gridPosition.y < 0 || gridPosition.y >= levelData.size())
	{
		//Return true, meaning delete the bullet
		return true;
	}

	//This is just a bool expression. Will be true whenever it's not a dot
	return (levelData[gridPosition.y][gridPosition.x] != '.');
}

//-----------------------------------------Set functions-----------------------
void Bullets::setPosition(glm::vec2 position)
{
	_position += position;
}

