#include "Agent.h"
#include <CSGengine/ResourceManager.h>
#include <algorithm>

const float Agent::AGENT_SIZE = 60.0f;
const float Agent::AGENT_RADIUS = AGENT_SIZE / 2.0f;

//-------------------------------------------------- Constructor ----------------------------------------
Agent::Agent()
{
}

Agent::~Agent()
{
}

//------------------------------- Check collision function --------------------------------
//This will check the collision
bool Agent::checkCollision(const std::vector<std::string>& levelData)
{
	//This will be a vector of all tiles that we can collide with
	std::vector<glm::vec2> collideTilePosition;

	//Check each corner
	//First corner
	checkTilePosition(collideTilePosition,
						_pos.x,
						_pos.y, 
						levelData);
	//Second Corner
	checkTilePosition(collideTilePosition,
						_pos.x + AGENT_SIZE,
						_pos.y, 
						levelData);
	//Third Corner
	checkTilePosition(collideTilePosition,
						_pos.x,
						_pos.y + AGENT_SIZE,
						levelData);

	//Forth corner Corner
	checkTilePosition(collideTilePosition,
						_pos.x + AGENT_SIZE,
						_pos.y + AGENT_SIZE,
						levelData);

	if (collideTilePosition.size() == 0)
	{
		return false;
	}

	//Handle the collision
	for (unsigned int i = 0; i < collideTilePosition.size(); i++)
	{
		collideWithTile(collideTilePosition[i]);
	}

	return true;
}

//------------------------------------- Check collision with another agent -----------------------------------
bool Agent::checkCollisionWithOtherAgent(Agent* agent)
{
	static const float MIN_DISTANCE = AGENT_RADIUS + AGENT_RADIUS;

	//Going to use circular collision(Since all our agents are circles
	glm::vec2 centerPosA = _pos + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPos() + glm::vec2(AGENT_RADIUS);

	//Dist vect for distance vector
	glm::vec2 distVect = centerPosA - centerPosB;

	//This will give us the length of both center agents when they collide
	float distance = glm::length(distVect);

	float collisionDepths = MIN_DISTANCE - distance;

	if (collisionDepths > 0)
	{
		//We need to push them back by the collision depth
		glm::vec2 collisionDepthVec = glm::normalize(distVect) * collisionDepths;

		_pos += collisionDepthVec / 2.0f;
		//We need to now push them back by equal parts.
		//So we'll push them back by half
		agent->_pos -= collisionDepthVec / 2.0f;

		return true;
	}

	return false;
}

//-------------------------------------------------- Draw function ----------------------------------------
void Agent::draw(CSGengine::SpriteBatch& spriteBatch)
{
	static int textureID = CSGengine::ResourceManager::getTexture("Textures/purple-ball.png").id;
	//This won't ever change, so make it a static const. Feeding itinto the draw function
	static const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	//Create a temp destRect to feed it to the function
	glm::vec4 destRect;
	destRect.x = _pos.x;
	destRect.y = _pos.y;
	destRect.z = AGENT_SIZE;
	destRect.w = AGENT_SIZE;


	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}

//------------------------------------ Check tile position -------------------------------
//Check each corner of the tile
void Agent::checkTilePosition(
	std::vector<glm::vec2>& collideTilePosition,
	float x,
	float y,
	const std::vector<std::string>& levelData)
{
	//Check the corners
	//First corner position is just the position
	//We're removing the floating point, just to make it easier.
	//Can come back later and edit it to not do that
	//Floor just rounds down
	glm::vec2 cornerPos = glm::ivec2(
		floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	//Check if any one is outside the world(Which is bad isnce we have nothing there!)
	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size())
	{
		return;
	}

	//Check if the tile is collidable
	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		collideTilePosition.emplace_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

//----------------------------------- Collide With Tile checking ---------------------------------
//AABB collision. A simple collision technique
void Agent::collideWithTile(glm::vec2 tilePos)
{
	//static const float AGENT_RADIUS = AGENT_SIZE / 2.0f;
	static const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	static const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS; // Minium distance between an agent and a tile
	
	//Get the center of the player 
	glm::vec2 centerPlayerPos = _pos + glm::vec2(AGENT_RADIUS);
	//To get the distant vector
	glm::vec2 distVec = centerPlayerPos - tilePos;

	//abs for absolute value
	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	//If this is true, we are colliding
	//Max will return the greater of the two values
	if (xDepth > 0 && yDepth > 0)
	{
		//Check which is greater
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f))
		{
			//We're just going to push out into the x direction
			//But we have to figure out if it's negative or postitve
			if (distVec.x < 0)
			{
				_pos.x -= xDepth;
			}
			else
			{
				_pos.x += xDepth;
			}
		}
		else
		{
			//We're just going to push out into the y direction
			//But we have to figure out if it's negative or postitve
			if (distVec.y < 0)
			{
				_pos.y -= yDepth;
			}
			else
			{
				_pos.y += yDepth;
			}
		}
	}
}