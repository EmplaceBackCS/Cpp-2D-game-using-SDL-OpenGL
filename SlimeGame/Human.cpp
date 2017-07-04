#include "Human.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

//-------------------------------------------------- Constructor ----------------------------------------
Human::Human(): Agent(),
	_frameCounter(0)
{
}

Human::~Human()
{
}

//---------------------------------------- Init the humans ---------------------------------
//Give them a speed and a pos
void Human::init(float speed, glm::vec2 pos)
{
	//Create a random number
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randomDirection(-1.0f, 1.0f);

	_color = CSGengine::ColorRGBA8(0, 255, 255, 255);

	_speed = speed;
	_pos = pos;

	//Use the randomize engine above
	_direction = glm::vec2(randomDirection(randomEngine), randomDirection(randomEngine));
	//Incase they get 0, we should change that
	if (_direction.length() == 0)
	{
		_direction = glm::vec2(1.0f, 0.0f);
	}

	//This makes it unit lenth
	_direction = glm::normalize(_direction);
}

//----------------------------------------- Update Function ----------------------------------
//Update anything that needs to be updated..
void Human::update(
	const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies)
{
	//Create a random number
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randomRotate(-100.0f, 100.0f);

	_pos += _direction * _speed;

	

	//Change direction every so often
	if (_frameCounter == 100)
	{
		_direction = glm::rotate(_direction, glm::radians(randomRotate(randomEngine)));
		_frameCounter = 0;
	}
	else 
	{	
		_frameCounter++;
	}
	//If they hit a wall, change their direction
	if (checkCollision(levelData))
	{
		_direction = glm::rotate(_direction, glm::radians(randomRotate(randomEngine)));
	}

}


