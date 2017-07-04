#pragma once
#include <glm/glm.hpp>
#include <CSGengine/SpriteBatch.h>
#include <SDL/SDL.h>
#include <vector>
#include "Level.h"
#include "Bullets.h"
//This is so we don't have to #include "Humans" and "Zombies"
//Since that would be a circular include. Not good!
class Zombie;
class Human;

class Agent
{
	public:
		//Constructors/destructor
		Agent();
		virtual ~Agent();


		//Update their position
		//Virtual pure for our parent class
		virtual void update(
			const std::vector<std::string>& levelData,
			std::vector<Human*>& humans,
			std::vector<Zombie*>& zombies) = 0;

		//Check collision function
		virtual bool checkCollision(const std::vector<std::string>& levelData);

		//Check collision with other Agents
		virtual bool checkCollisionWithOtherAgent(Agent* agent);

		//Draw our agents
		virtual void draw(CSGengine::SpriteBatch& spriteBatch);



		//Get functions
		//Get both x and y positions
		virtual glm::vec2 getPos()const { return _pos; }
		//Get x pos
		virtual float getPosX()const { return _pos.x; }
		//Get y pos
		virtual float getPosY()const { return _pos.y; }
		//Set functions
		//Set the color
		virtual void setColor(int r, int b, int g) {
			_color.setColor(r, b, g, 255);
		}

		//Get the x/y pos with a vec2
		virtual void setPos(glm::vec2 newPos) { newPos = _pos; }

	protected:
		//--------------------------------------------------------------
		//MAKE SURE THIS IS THE SAME SIZE AS THE TILE_WIDTH FROM LEVEL.H
		static const int TILE_WIDTH = 64;
		//MAKE SURE THIS IS THE SAME SIZE AS THE TILE_WIDTH FROM LEVEL.H
		//--------------------------------------------------------------
		static const float AGENT_RADIUS;

		glm::vec2 _pos; //Position
		float _speed; // Speed of the Agents
		CSGengine::ColorRGBA8 _color; //To color our sprites

		//Check the position of the tile
		virtual void checkTilePosition(std::vector<glm::vec2>& collideTilePosition,
								float x,
								float y,
								const std::vector<std::string>& levelData);
		//This is to check the tiles
		virtual void collideWithTile(glm::vec2 tilePos);

		 //Size of our Agents
		static const float AGENT_SIZE;
};

