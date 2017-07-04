#include "MainGame.h"
#include <random>
#include <ctime>
#include <CSGengine/Errors.h>
//------------------------------------------- Constructors --------------------------------
MainGame::MainGame() :
	_screenWidth(1366),
	_screenHeight(760),
	_currentGameState(GameState::PLAY),
	_time(0.01f),
	_speedOfTime(0.005f),
	_fps(1.00f),
	_maxFPS(60.0f),
	_currentLevel(0),
	_player(nullptr),
	_direction(0),
	//These two should be 25
	_cooldownCounter(25),
	//These two should be 50
	_cooldownTime(50),
	_bulletChoice(0),
	_cooldown(false),
	_zombieIndex(-1),
	_zombiesKilled(0),
	_weaponCooldown(false),
	_weaponCooldownCounter(10)
{
	//_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
	//Our vectors are pointers, so we need to delete each one we create
	for (unsigned int i = 0; i < _levels.size(); i++)
	{
		delete _levels[i];
	}
	for (unsigned int i = 0; i < _humans.size(); i++)
	{
		delete _humans[i];
	}
	for (unsigned int i = 0; i < _zombies.size(); i++)
	{
		delete _zombies[i];
	}
	for (unsigned int i = 0; i < _trailingShadow.size(); i++)
	{
		delete _trailingShadow[i];
	}
	for (unsigned int i = 0; i < _bullets.size(); i++)
	{
		delete _bullets[i];
	}
	//Delete the guns
	for (int i = 0; i < _MAX_NUMBER_OF_GUN; i++)
	{
		delete _guns[i];
	}
	//Free our memory from our vectors
	_levels.erase(_levels.begin(), _levels.end());
	_humans.erase(_humans.begin(), _humans.end());
	_zombies.erase(_zombies.begin(), _zombies.end());
	_trailingShadow.erase(_trailingShadow.begin(), _trailingShadow.end());
	_bullets.erase(_bullets.begin(), _bullets.end());
}

//Run the main game in the .cpp file
void MainGame::run()
{
	//Init SDL, our window, and compile our shaders
	initSystems();

	//Init the level
	initLevel();

	//Main game loop
	gameLoop();
}


//---------------------------------------------------- Initiate the system --------------------------------------------
void MainGame::initSystems()
{
	//Initilize all the SDL things we need from our game engine
	CSGengine::init();

	//Create the window with our function from our game engine
	_window.createWindow("Run away from the red dots!", _screenWidth, _screenHeight, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Compile shaders
	initShaders();

	_camera.init(_screenWidth, _screenHeight);
	_agentSpriteBatch.init();
	_shadowSpriteBatch.init();
	//Limit the fps
	_fpsLimiter.init(_maxFPS);
	
}

//-----------------------------------------Init our level --------------------------------------------
void MainGame::initLevel()
{
	//Create our starting level. In this case, level 1
	_levels.push_back(new Level("Levels/Level_1.txt"));
	_currentLevel = 0;

	//Set our player up
	_player = new Player();
	_player->init(_PLAYER_SPEED, _levels[_currentLevel]->getPlayerStartingPos(), &_inputManager, &_camera);
	//Push back our vector and put the player in subscript 0
	_humans.push_back(_player);
	//Create a random number
	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	//2 because that's the starting number we want. From 2 - width/hieght
	std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

	//Add all the random humans to our world!
	for (int i = 0; i < _levels[_currentLevel]->getNumberOfHumans(); i++)
	{
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.push_back(new Human);
		_humans.back()->init(HUMAN_SPEED, pos);
	}
	//Spawn zombies
	const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartingPos();

	for (unsigned int i = 0; i < zombiePositions.size(); i++)
	{
		_zombies.push_back(new Zombie());
		_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	//Init the guns
	_guns[0] = new Pistol();
	_guns[1] = new ShotGun();
	_guns[2] = new GiantSlowGun();
}

//----------------------------------------- Iniaiate the shaders ----------------------------------------------------------
//Init the shaders
void MainGame::initShaders()
{
	//File path names
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	//The variables from the files
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	//Linking the shades from the SLGL class
	_colorProgram.linkShaders();

}

//-------------------------------------------------------- Game loop ---------------------------------------------------
//Loop function to keep the window open
void MainGame::gameLoop()
{
	/*Game loop to keep the window open*/
	while (_currentGameState != GameState::EXIT)
	{
		_fpsLimiter.begin();

		//Get the user input using SDL poll event
		processInput();

		_inputManager.update();
		//Update agent's position
		updateAgents();

		//Update bullets
		updateBullets();
		
		//Uppdate the camera position to always be on the character
		_camera.setPosition(_player->getPos());
		//Change out camera before we draw our game
		_camera.updateCamera();
		//Draw our sprites

		//Update our Shadow like effects
		//This will clear each Shadow when the life time reachs 0
		upDateTrailingShadow(_trailingShadow);

		//Check for bullet collision
		checkBulletWorldCollision();

		//Draw the game
		drawGame();

		//Cooldown timer
		checkCooldown();
		//Check weapon cooldown
		checkWeaponSwapCooldown();
		//Calculate the fps
		_fps = _fpsLimiter.end();

		getFPS_OnConsole();

		checkWinCondition();
	}
}

void MainGame::updateAgents()
{
	//Update the humans
	//Player counts as a human too, through polymorphism!
	for (unsigned int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(
							_levels[_currentLevel]->getLevelData(),
							_humans,
							_zombies);
	}
	//Update the zombies
	for (unsigned int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(
			_levels[_currentLevel]->getLevelData(),
			_humans,
			_zombies);
	}

	//Update collisions for Zombies
	for (unsigned int i = 0; i < _zombies.size(); i++)
	{
		//This way lets us check fewer humans.
		//If we started at 0, we'd have redundant checking
		for (unsigned int c = i + 1; c < _zombies.size(); c++)
		{
			_zombies[i]->checkCollisionWithOtherAgent(_zombies[c]);
		}

		//Collide with humans
		//We start at 1 for c here, because subscript 0 is the player
		//We don't want to delete the player!
		for (unsigned int c = 1; c < _humans.size(); c++)
		{
			if (_zombies[i]->checkCollisionWithOtherAgent(_humans[c]))
			{
				//Add a new zombie since he touched a human
				_zombies.push_back(new Zombie());
				_zombies.back()->init(ZOMBIE_SPEED, _humans[c]->getPos());
				//Delete the human, since we are adding a zombie in his place
				delete _humans[c];
				_humans[c] = _humans.back();
				_humans.pop_back();
			}
		}
		//Check collision against the player, so we can tell them
		//Game over if a zombie hits them
		if (_zombies[i]->checkCollisionWithOtherAgent(_player))
		{
			//Temp way, just to check if the collision works
			CSGengine::getFatalError("A Red dot hit you and you lost!\n");
		}
	}


	//Update collisions for humans
	for (unsigned int i = 0; i < _humans.size(); i++)
	{
		//This way lets us check fewer humans.
		//If we started at 0, we'd have redundant checking
		//We're checking if colloliding with other humans is true
		for (unsigned int c = i + 1; c < _humans.size(); c++)
		{
			_humans[i]->checkCollisionWithOtherAgent(_humans[c]);
		}
	}


	//Do collision with the bullets
	if (_zombies.size() != 0)
	{
		//Here we'll check which index the bullet touched from the zombies
		for (unsigned int i = 0; i < _bullets.size(); i++)
		{
			if (_bullets[i]->checkBulletCollision(_zombies, _zombieIndex))
			{
				//Delete the zombie since we shot him!
				delete _zombies[_zombieIndex];
				_zombies[_zombieIndex] = _zombies.back();
				_zombies.pop_back();

				//Delete the bullet that hit the zombie. No piercing!
				delete _bullets[i];
				_bullets[i] = _bullets.back();
				_bullets.pop_back();

				//Un comment if you want pircing
				//Let the player gain pircing shots after a certain amount of skills
				//Works
				//if (_zombiesKilled < 10)
				//{
				//	//Delete the bullet that hit the zombie. No piercing!
				//	delete _bullets[i];
				//	_bullets[i] = _bullets.back();
				//	_bullets.pop_back();
				//}
				//Incrase the zombie killed size
				_zombiesKilled++;
			}
		}
		//This is temp. Since the method I am using to 
		//See which index the bullet touched for zombies returns false at index 0
		//I needed another if statement
		if (_zombieIndex == 0)
		{
			//delete The zombie
			delete _zombies[0];
			_zombies[0] = _zombies.back();
			_zombies.pop_back();
			//This is so it won't just keep deleting all the subscript 0 zombies
			_zombieIndex = -50;
			//Incrase the zombie killed size
			_zombiesKilled++;
		}
	}

}

//--------------------------------------------------------Update the bullets ---------------------------------------
//This will delete the bullets position
void MainGame::updateBullets()
{
	for (unsigned int i = 0; i < _bullets.size();)
	{
		if (_bullets[i]->update())
		{
			//A way to remove a vector, when you don't care about the order
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else
		{
			//Only incrase i if we didn't delete a bullet
			i++;
		}
	}
}

//-------------------------------------------------- Clear the effects of the Shadow class ----------------------------------
//This is the shadow like/trail like effect of the player
void MainGame::upDateTrailingShadow(std::vector<PlayerShadow*>& trailingShadow)
{
	//Clear the Shadow
	for (unsigned int i = 0; i < trailingShadow.size();)
	{
		if (trailingShadow[i]->update())
		{
			//A way to remove a vector, when you don't care about the order
			trailingShadow[i] = trailingShadow.back();
			trailingShadow.pop_back();
		}
		else
		{
			//Only incrase i if we didn't delete a Shadow
			i++;
		}
	}

}

//------------------------- Process handler using SDL poll event ------------------------------
//Get the input from the user
void MainGame::processInput()
{
	SDL_Event gameEvent;
	/*Getting the user input and allowing the window to be interactive with the input from the user*/
	while (SDL_PollEvent(&gameEvent))
	{
		switch (gameEvent.type)
		{
			case SDL_QUIT:
				_currentGameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				//Just to check the x/y location from debugging. Comment out of not needed anymore
				//std::cout << "X motion: " << gameEvent.motion.x << " \nY motion: " << gameEvent.motion.y << std::endl;
				//Set the mouse coords with sdl motion
				_inputManager.setMouseCoords((float)gameEvent.motion.x, (float)gameEvent.motion.y);	
				break;
				//This is for when a key is hit on the keyboard, another switch case is 
			case SDL_KEYDOWN:	
				_inputManager.checkForPressedKey(gameEvent.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.checkReleasedKey(gameEvent.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.checkForPressedKey(gameEvent.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.checkReleasedKey(gameEvent.button.button);
				break;
		}
	}

	//Have another way to exit the game with esc key
	if (_inputManager.isKeyDown(SDLK_ESCAPE))
	{
		_currentGameState = GameState::EXIT;

	}

	//Have our inut manger update the key pressed accordingly
	if (_inputManager.isKeyDown(SDLK_r))
	{		
		if (_weaponCooldown == false)
		{
			//Incrase the gun choice to change guns
			_bulletChoice++;

			if (_bulletChoice > _MAX_NUMBER_OF_GUN - 1)
			{
				_bulletChoice = 0;
			}
			//Give it a cooldown so it won't change so fast that it skips over the next weapon
			//Give it a countdown 
			_weaponCooldownCounter = 10;
			_weaponCooldown = true;
		}
	}

	if (_inputManager.isKeyDown(SDLK_UP))
	{
	}

	if (_inputManager.isKeyDown(SDLK_w))
	{
		//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
		_direction.x = 0.0f;
		_direction.y = 0.0f;

		//Accepts non default constructor arguments. Gets rid of the middle man
		//So no need to create a temp object of a class!
		_trailingShadow.emplace_back(new PlayerShadow(_player->getPos(), _direction, 10.0f, 10));
	}

	if (_inputManager.isKeyDown(SDLK_s))
	{

		//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
		_direction.x = 0.0f;
		_direction.y = 0.0f;

		//Accepts non default constructor arguments. Gets rid of the middle man
		//So no need to create a temp object of a class!
		_trailingShadow.emplace_back(new PlayerShadow(_player->getPos(), _direction, 10.0f, 10));
	}

	if (_inputManager.isKeyDown(SDLK_a))
	{
		//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
		_direction.x = 0.0f;
		_direction.y = 0.0f;

		//Accepts non default constructor arguments. Gets rid of the middle man
		//So no need to create a temp object of a class!
		_trailingShadow.emplace_back(new PlayerShadow(_player->getPos(), _direction, 10.0f, 10));
	}

	if (_inputManager.isKeyDown(SDLK_d))
	{
		//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
		_direction.x = 0.0f;
		_direction.y = 0.0f;

		//Accepts non default constructor arguments. Gets rid of the middle man
		//So no need to create a temp object of a class!
		_trailingShadow.emplace_back(new PlayerShadow(_player->getPos(), _direction, 10.0f, 10));
	}

	//Right arrow key
	if (_inputManager.isKeyDown(SDLK_RIGHT))
	{
		if (_cooldown == false)
		{
			checkBulletChoiceForKeyArrowKey();
		}
	}

	//Left arrow key
	if (_inputManager.isKeyDown(SDLK_LEFT))
	{
		if (_cooldown == false)
		{
			checkBulletChoiceForKeyArrowKey();
		}
	}

	//Up arrow key
	if (_inputManager.isKeyDown(SDLK_UP))
	{
		if (_cooldown == false)
		{
			checkBulletChoiceForKeyArrowKey();
		}
	}

	//Down arrow key
	if (_inputManager.isKeyDown(SDLK_DOWN))
	{
		if (_cooldown == false)
		{
			checkBulletChoiceForKeyArrowKey();
		}
	}
	
	//F key
	if (_inputManager.isKeyDown(SDLK_f))
	{
		_camera.setScale(_camera.getScale() + _SCALE_SPEED);
	}

	//G key
	if (_inputManager.isKeyDown(SDLK_g))
	{
		_camera.setScale(_camera.getScale() - _SCALE_SPEED);
	}

	//Left mouse button
	if (_inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		if (_cooldown == false)
		{
			//Check the gun choice/bullet choice they have
			checkBulletChoice();
		}
	}

	//Right mouse button
	//To doo, for now empty
	if (_inputManager.isKeyDown(SDL_BUTTON_RIGHT))
	{
		if (_cooldown == false)
		{
			//empty for now
		}
	}
}

//----------------------------------- Draw the game! -----------------------------------
//Draw what you want in the window
void MainGame::drawGame()
{
	/*Clear the screen*/
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	//Optional
	glActiveTexture(GL_TEXTURE0);

	//Ensure that the shader uses texture 0
	GLuint textureUniform = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	//Grab our camera matrix
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLuint pUniform = _colorProgram.getUniformLocation("p");
	
	glUniformMatrix4fv(
		pUniform, 
		1, 
		GL_FALSE, 
		&projectionMatrix[0][0]);
	//Now draw our level
	_levels[_currentLevel]->renderLevel();

	//Start drawing agents
	_agentSpriteBatch.begin();

	//Draw the humans
	for (unsigned int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_agentSpriteBatch);
	}

	//Draw the Zombies
	for (unsigned int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_agentSpriteBatch);
	}

	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();

	//Shadow like sprites
	_shadowSpriteBatch.begin();

	//Draw the shadows
	for (unsigned int i = 0; i < _trailingShadow.size(); i++)
	{
		_trailingShadow[i]->draw(_shadowSpriteBatch);
	}

	//Draw our bullets
	for (unsigned int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->draw(_shadowSpriteBatch);
	}
	_shadowSpriteBatch.end();
	_shadowSpriteBatch.renderBatch();


	_colorProgram.unUse();

	/*Swap to the other frame so that it looks smooth, rather then flickering*/
	_window.swapBuffer();

}

//------------------------------------- Calculate the FPS function here ------------------------------------------
//This will use console to print out the fps
void MainGame::getFPS_OnConsole()
{
	static int frameCount = 0;
	frameCount++;
	//This is just so it won't print out the fps constantly. 
	if (frameCount == 50)
	{
		std::cout << "FPS: " << _fps << std::endl;
		frameCount = 0;
	}
}

//--------------------------------------- Check cooldown -----------------------------
//Check if cooldown is true, for the weapons. If it is, it'll have a count down per frame
//Set the cooldown to false after the number _cooldownCounter is 0
void MainGame::checkCooldown()
{
	//If the cooldown is true
	if (_cooldown)
	{
		//We'll subtract from the cooldown timer
		_cooldownCounter--;

		if (_cooldownCounter <= 0)
		{
			//And set it to false so they can shoot again once the timer is 0
			_cooldown = false;
		}
	}
}

//----------------------------------------- Check weapon swap cooldown -----------------------
//Gave weapon swap a mini cooldown so it wouldn't swap so fast
void MainGame::checkWeaponSwapCooldown()
{
	//If the cooldown is true
	if (_weaponCooldown)
	{
		//We'll subtract from the cooldown timer
		_weaponCooldownCounter--;

		if (_weaponCooldownCounter <= 0)
		{
			//And set it to false so they can swap weapons again after the timer is 0
			_weaponCooldown = false;
		}
	}
}

//------------------------------------- Check win condition ---------------------
//For now, if there are no zombies in the world, we'll just spawn them again
//Giving it an endless mode
void MainGame::checkWinCondition()
{
	//--------------------------- zombies -----------------------
	//For now it's endless mode
	//Need to figure out how to create level 2
	if (_zombies.size() == 0)
	{
		const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombieStartingPos();

		for (unsigned int i = 0; i < zombiePositions.size(); i++)
		{
			_zombies.push_back(new Zombie());
			_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
		}
	}

	//--------------------------- Humans -----------------------
	//Since it's endless mode, we'll just do the same for humans like we did for zombies

	//Human size 1, because the player is a human and 1 means that the player is the only one left
	if (_humans.size() == 1 && _zombies.size() < 250)
	{
		//Create a random number
		std::mt19937 randomEngine;
		randomEngine.seed(time(nullptr));
		//2 because that's the starting number we want. From 2 - width/hieght
		std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
		std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

		//Add all the random humans to our world!
		for (int i = 0; i < _levels[_currentLevel]->getNumberOfHumans(); i++)
		{
			glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
			_humans.push_back(new Human);
			_humans.back()->init(HUMAN_SPEED, pos);
		}
	}
}

//-------------------- Check bullet choice -----------------
//Switch case to call the proper gun
//This is using the mouse for coordinates
void MainGame::checkBulletChoice()
{
	switch (_bulletChoice)
	{
		//Normal bullets
		case 0:
			normalBullets();
			break;
		//Spread bullets
		case 1:
			spreadBullets();
			break;
		//Big bullets
		case 2:
			giantSlowGun();
			break;	
		default:
			break;
	}
}

//------------------------------- With arrow keys ----------------------
//Check the weapon choice with the arrow keys, since 
//We can't use the mouse x/y coordinates
void MainGame::checkBulletChoiceForKeyArrowKey()
{
	switch (_bulletChoice)
	{
		//Normal bullets
	case 0:
		normalArrowKeyBullets();
		break;
		//Spread bullets
	case 1:
		normalArrowKeyBullets();
		break;
		//Big bullets
	case 2:
		giantSlowGun();
		break;
	default:
		break;
	}
}
//------------------------------------ Normal bullets ----------------------------------
//Normal bullets for the mouse
void MainGame::normalBullets()
{
	//Get our gun
	_guns[_bulletChoice]->getGun(_bullets, &_inputManager, _player, _camera);
	_cooldownCounter = _PISTOL_COOLDOWN_TIME;
	_cooldown = true;
}

//----------------------------- Normal bullets(Pistol)---------------
//This will determine the direction the bullets will face
//Cooldown for this should be 15-25 frames
void MainGame::normalArrowKeyBullets()
{
	if (_inputManager.isKeyDown(SDLK_RIGHT))
	{
		_guns[_bulletChoice]->getGunForRightArrowKey(_bullets, _player, _camera);
		_cooldownCounter = _PISTOL_COOLDOWN_TIME;
		_cooldown = true;
	}
	else if (_inputManager.isKeyDown(SDLK_LEFT))
	{
		_guns[_bulletChoice]->getGunForLeftArrowKey(_bullets, _player, _camera);
		_cooldownCounter = _PISTOL_COOLDOWN_TIME;
		_cooldown = true;
	}
	else if (_inputManager.isKeyDown(SDLK_UP))
	{
		_guns[_bulletChoice]->getGunForUpArrowKey(_bullets, _player, _camera);
		_cooldownCounter = _PISTOL_COOLDOWN_TIME;
		_cooldown = true;
	}
	else
	{
		_guns[_bulletChoice]->getGunForDownArrowKey(_bullets, _player, _camera);
		_cooldownCounter = _PISTOL_COOLDOWN_TIME;
		_cooldown = true;
	}
}
//------------------------------------------------- Spread bullets -------------------------------
//Shot gun, spread bullets, but close rage. Keep cooldown counter
//Around 30-40
void MainGame::spreadBullets()
{
	//Get our gun/bullet
	_guns[_bulletChoice]->getGun(_bullets, &_inputManager, _player, _camera);
	//Give it a cooldown
	_cooldownCounter = _SPREAD_GUN_COOLDOWN_TIME;
	_cooldown = true;
	
}

//Spread bullets right arrow key
void MainGame::spreadBulletsRightArrowKey()
{
	//Get our gun/bullet
	_guns[_bulletChoice]->getGunForRightArrowKey(_bullets, _player, _camera);
	//Give it a cooldown
	_cooldownCounter = _SPREAD_GUN_COOLDOWN_TIME;
	_cooldown = true;

}
//----------------------------------------- Giant bullets -----------------------------
//This was for giant bullets, but changed it to have a unique effect
//A bomb, that the player can place
void MainGame::giantSlowGun()
{
	_guns[_bulletChoice]->getGun(_bullets, &_inputManager, _player, _camera);
	_cooldownCounter = _BOMB_COOLDOWN_TIME;
	_cooldown = true;
}
//---------------------------------- Check world collision with bullets -------------------------
void MainGame::checkBulletWorldCollision()
{
	//Check every bullet to see if it collided with the world
	for (unsigned int i = 0; i < _bullets.size();)
	{
		if(_bullets[i]->checkBulletCollisionWithWorld(_levels[_currentLevel]->getLevelData()))
		{
			//Delete them if it's true
			delete _bullets[i];
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else
		{
			//i++ should only happen if one didnt' collide with the world!
			//This is so it can check the next one, otherwise it'll delete the wrong one
			i++;
		}

	}
}
//void MainGame::destroyAll()
//{
//	//Our vectors are pointers, so we need to delete each one we create
//	for (int i = 0; i < _levels.size(); i++)
//	{
//		delete _levels[i];
//	}
//	for (int i = 0; i < _humans.size(); i++)
//	{
//		delete _humans[i];
//	}
//	for (int i = 0; i < _zombies.size(); i++)
//	{
//		delete _zombies[i];
//	}
//	for (int i = 0; i < _trailingShadow.size(); i++)
//	{
//		delete _trailingShadow[i];
//	}
//	for (int i = 0; i < _bullets.size(); i++)
//	{
//		delete _bullets[i];
//	}
//	//Free our memory from our vectors
//	_levels.erase(_levels.begin(), _levels.end());
//	_humans.erase(_humans.begin(), _humans.end());
//	_zombies.erase(_zombies.begin(), _zombies.end());
//	_trailingShadow.erase(_trailingShadow.begin(), _trailingShadow.end());
//	_bullets.erase(_bullets.begin(), _bullets.end());
//}