#include "Level.h"

//-------------------------------------------------- Constructor ----------------------------------------
Level::Level()
{
}

//----------------------------------------- Non default constructor ----------------------------
Level::Level(const std::string& fileName)
{
	//Create our ifstream to open our file we pass through the constructor
	std::ifstream file;

	file.open(fileName);

	if (file.fail())
	{
		CSGengine::getFatalError("Failed to open: " + fileName + " \n");
	}

	//Temp string to throw away the first string in the level file
	std::string tempString;

	file >> tempString >> _numOfHumans;

	//Throw away the rest of the first line once we get the number of humans
	std::getline(file, tempString);
	//Reading each line one by one to put the string into our temp string
	while (std::getline(file, tempString))
	{
		//This will create our entire level. Each time this loop excutes
		//It'll push back the vector and add it to our vector of strings
		_levelData.push_back(tempString);
	}

	//This is just to display it in cmd to see if it's being read.
	//for (int i = 0; i < _levelData.size(); i++)
	//{
	//	std::cout << _levelData[i] << std::endl;
	//}

	_spriteBatch.init();
	_spriteBatch.begin();

	//Create our uv rect
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	CSGengine::ColorRGBA8 color;
	
	color.setColor(255, 255, 255, 255);

	//Render our tiles! 
	for (unsigned int y = 0; y < _levelData.size(); y++)
	{
		for (unsigned int x = 0; x < _levelData[y].size(); x++)
		{
			//Grab our tile
			char tile = _levelData[y][x];

			//Get our destanation rectangle
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//Process the tile!
			switch (tile)
			{
				case 'B':
					_spriteBatch.draw(
						destRect, 
						uvRect, 
						CSGengine::ResourceManager::getTexture("Textures/Tile (5).png").id,
						0.0f,
						color);
					break;
				case 'W':
					_spriteBatch.draw(
						destRect,
						uvRect,
						CSGengine::ResourceManager::getTexture("Textures/Acid (2).png").id,
						0.0f,
						color);
					break;
				case 'R':
					_spriteBatch.draw(
						destRect,
						uvRect,
						CSGengine::ResourceManager::getTexture("Textures/Barrel (1).png").id,
						0.0f,
						color);
					break;
					//Grab the player coordinates here
				case 'P':
					//We're setting it = to a ., so when we do collision check, it
					//Was changed from P to a ., which is ignored
					_levelData[y][x] = '.';
					_playerStartingPos.x = x * TILE_WIDTH;
					_playerStartingPos.y = y * TILE_WIDTH;
					break;
					//Grab the zombie coordinates here
				case 'Z':
					//We're setting it = to a ., so when we do collision check, it
					//Was changed from Z to a ., which is ignored
					_levelData[y][x] = '.';
					_zombieStartingPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					// Our blank space is '.', so we'll just give it a blank case/break
					//To make error handling easier
					break;
				case '.':
					break;
				default:
					std::cout << "Unexpected smybol " << tile << " at " << x << " " << y << "\n";
					break;
			}
		}
	}

	_spriteBatch.end();

}

Level::~Level()
{
}

//----------------------------------------------- Draw level function -------------------------------------
//Render the textures here
void Level::renderLevel()
{
	_spriteBatch.renderBatch();
}