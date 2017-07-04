#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <CSGengine/Errors.h>
#include <iostream>
#include <CSGengine/SpriteBatch.h>
#include <CSGengine/ResourceManager.h>

class Level
{
	public:
		//Constructors/destructor
		Level();
		//Non default. So that we can just use a pointer for our level
		//We'll make it a const and give it the adress so that
		//It won't have to read the entire file and make a copy of it
		Level(const std::string& fileName);
		virtual ~Level();

		void renderLevel();

		//---------------------- Get functions --------------------
		glm::vec2 getPlayerStartingPos()const { return _playerStartingPos; }
		 //Get our level data
		const std::vector<std::string>& getLevelData()const { return _levelData; }

		//Get the number of humans
		int getNumberOfHumans()const { return _numOfHumans; }

		virtual int getWidth()const { return _levelData[0].size(); }
		virtual int getHeight()const { return _levelData.size(); }

		//Look into this later. It'll return the vector, but no one should be able to change it
		//Make it a const for this
		const std::vector<glm::vec2>& getZombieStartingPos()const { return _zombieStartingPos; }
	private:
		//Our tile width
		static const int TILE_WIDTH = 64;

		//This will read the .txt file from our level folder
		std::vector<std::string> _levelData;

		//This will store the number of humans
		int _numOfHumans;

		CSGengine::SpriteBatch _spriteBatch;

		//Save the player location. 
		glm::vec2 _playerStartingPos;

		//Zombie needs a vec, while our player doesn't becuase
		//There can only be one human, but many zombies
		std::vector<glm::vec2> _zombieStartingPos;
};

