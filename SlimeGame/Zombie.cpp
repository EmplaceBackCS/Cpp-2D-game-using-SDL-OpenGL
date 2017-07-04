#include "Zombie.h"
#include "Human.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>
//-------------------------------------------------- Constructor ----------------------------------------
Zombie::Zombie() : Agent()
{
}


Zombie::~Zombie()
{
}

//----------------------------------------- Update function -----------------------------
//This should make the zombie chase the nearest human
void Zombie::update(
	const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies)
{
	//Find the cloest human
	Human* cloestHuman = getNearestHuman(humans);

	//If we didn't return a null ptr, we should move in that direction
	//Since we did find a human
	if (cloestHuman != nullptr)
	{
		glm::vec2 direction = glm::normalize(cloestHuman->getPos() - _pos);
		//Move the zombie that direction once we find the cloest one
		_pos += direction * _speed;
	}



	//If they hit a wall, change their direction
	if (checkCollision(levelData))
	{
		//To doo..
	}
}

//-------------------------------------- Get the nearest human's coordinates --------------------------------
Human* Zombie::getNearestHuman(std::vector<Human*>& humans)
{
	//We'll return this once we find the cloest human
	Human* cloestHumman = nullptr;
	//Temp float to see who is the cloest
	float smallestDistance = 50000000000.0f;

	for (unsigned int i = 0; i < humans.size(); i++)
	{
		//Distance vector
		//It'll be the current subscript of the human, 
		//Minus the zombie that is calling it
		//This is how we determine who is the cloest
		glm::vec2 distVec = humans[i]->getPos() - _pos;

		float distance = glm::length(distVec);

		//Update our distance
		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			cloestHumman = humans[i];
		}
	}

	return cloestHumman;
}
//---------------------------------------- Init the Zombies ---------------------------------
//Give them a speed and a pos
void Zombie::init(float speed, glm::vec2 pos)
{
	//Create a random number
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randomDirection(-1.0f, 1.0f);

	_color = CSGengine::ColorRGBA8(255, 0, 0, 255);

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
