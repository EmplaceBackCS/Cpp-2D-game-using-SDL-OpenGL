#pragma once
#include "Agent.h"
class Human : public Agent
{
	public:
		//Constructors/destructor
		Human();
		virtual ~Human();

		//Update the Ai's position
		virtual void update(
			const std::vector<std::string>& levelData,
			std::vector<Human*>& humans,
			std::vector<Zombie*>& zombies)override;

		virtual void init(float speed, glm::vec2 pos);

	private:
		//This will be used to randomly move the humans around
		//Basically like making them wonder around
		glm::vec2 _direction;
		//This is used to give them a new direction every so often, using
		//Frames to count when we want them to get a new path
		int _frameCounter;
};

