#pragma once
#include "Agent.h"

class Zombie : public Agent
{
	public:
		//Constructors/destructor
		Zombie();
		virtual ~Zombie();

		//Zombie init function
		virtual void init(float speed, glm::vec2 pos);
		
		//Update the movement of the Zombies. This will handle
		//When should the zombie move towards a player/ that isn't another zombie
		virtual void update(
			const std::vector<std::string>& levelData,
			std::vector<Human*>& humans,
			std::vector<Zombie*>& zombies)override;


	private:
		//This will tell us where the nearest human is
		Human* getNearestHuman(std::vector<Human*>& humans);

		glm::vec2 _direction;
};

