#include "MainGame.h"

//------------------------------------------- Constructors --------------------------------//Part of test maingame
MainGame::MainGame() :
	_screenWidth(1176),
	_screenHeight(644),
	_currentGameState(GameState::PLAY),
	_time(0.00f),
	_speedOfTime(0.005f),
	_fps(1.00f),
	_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
	_bullets.erase(_bullets.begin(), _bullets.end());
	_catBullets.erase(_catBullets.begin(), _catBullets.end());
}

//Run the main game in the .cpp file
void MainGame::run()
{
	initSystems();
	//Using vectors to incrase the number of sprites we want with pushback function
	//Bottom left
	//_sprites.push_back(new CSGengine::Sprite());
	//_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/robotfree/png/Idle (1).png");
	//_sprites.push_back(new CSGengine::Sprite());
	//_sprites.back()->init(0.0f, 0.0f, _screenWidth / 2, _screenWidth / 2, "Textures/robotfree/png/Idle (1).png");
	//Top left
	////_sprites.push_back(new CSGengine::Sprite());
	////_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/robotfree/png/Jump (8).png");
	//_sprites.push_back(new CSGengine::Sprite());
	//_sprites.back()->init(_screenWidth / 2, 0.0f, _screenWidth / 2, _screenWidth / 2, "Textures/robotfree/png/Idle (1).png");
	//Bottom Right corner
	//_sprites.push_back(new CSGengine::Sprite());
	//_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "Textures/robotfree/png/Jump (3).png");
	////Top right
	//_sprites.push_back(new CSGengine::Sprite());
	//_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "Textures/robotfree/png/JumpMelee (5).png");
	//_testSprite.init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/ninjagirlnew/png/Idle__001.png"); <-- was just a test sprite, now we moved to vectors
	//We are removing _playerTexture as we are going to use a tree now/bionary search for images.
	//It was mostly a test to see if our picoPNg and our imageloader class worked
	//_playerTexture = ImageLoader::loadPNG("Textures/ninjagirlnew/png/Idle__001.png");
	gameLoop();
}


//---------------------------------------------------- Initiate the system --------------------------------------------
void MainGame::initSystems()
{
	//Initilize all the SDL things we need from our game engine
	CSGengine::init();

	//Create the window with our function from our game engine
	_window.createWindow("Robots Attack!", _screenWidth, _screenHeight, 0);

	//Only make the shaders after you have init openGL!
	initShaders();

	//Set up the spritebatch class
	_spriteBatch.init();

	_fpsLimiter.init(_maxFPS);
	
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
		//Controls the speed of the colors
		_time += _speedOfTime;
		//Change out camera before we draw our game
		_camera.updateCamera();

		//Draw the bullets. This is temp, for testing
		//Will update bullets
		for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].update())
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

		for (int i = 0; i < _catBullets.size();)
		{
			if (_catBullets[i].update())
			{
				//A way to remove a vector, when you don't care about the order
				_catBullets[i] = _catBullets.back();
				_catBullets.pop_back();
			}
			else
			{
				//Only incrase i if we didn't delete a bullet
				i++;
			}
		}

		//Draw our sprites
		drawGame();
		//Calculate the fps
		_fps = _fpsLimiter.end();

		getFPS_OnConsole();
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
				_inputManager.setMouseCoords(gameEvent.motion.x, gameEvent.motion.y);	
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

	//Currently time is disabled since we don't use it.
	//It was to give it a colorful effect, like mario when he has a star buff
	//if (_inputManager.checkIsKeyPressed(SDLK_UP))
	//{
	//	_speedOfTime += 0.01f;
	//	std::cout << "Speed of time: " << _speedOfTime << "\n";
	//}

	//if (_inputManager.checkIsKeyPressed(SDLK_DOWN))
	//{
	//	_speedOfTime -= 0.01f;
	//	std::cout << "Speed of time: " << _speedOfTime << "\n";
	//}

	if (_inputManager.isKeyDown(SDLK_r))
	{
		/*_speedOfTime = 0.00f;*/
		//Create a temp variable to reset our position when R is pressed
		glm::vec2 position;
		//Set the x/y of our vec2
		position.x = 0.0f;
		position.y = 0.0f;
		//Move the camera to 0,0 coordinates
		_camera.setPosition(position);
	}

	if (_inputManager.isKeyDown(SDLK_w))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -_CAMERA_SPEED));
	}

	if (_inputManager.isKeyDown(SDLK_s))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, _CAMERA_SPEED));
	}

	if (_inputManager.isKeyDown(SDLK_a))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(_CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.isKeyDown(SDLK_d))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(-_CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.isKeyDown(SDLK_f))
	{
		_camera.setScale(_camera.getScale() + _SCALE_SPEED);
	}

	if (_inputManager.isKeyDown(SDLK_g))
	{
		_camera.setScale(_camera.getScale() - _SCALE_SPEED);
	}

	if (_inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenCoordsToWorld(mouseCoords);

		//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";

		glm::vec2 playerPosition;
		playerPosition.x = 70.0f;
		playerPosition.y = 60.0f;
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		//Accepts non default constructor arguments. Gets rid of the middle man
		//So no need to create a temp object of a class!
		_bullets.emplace_back(playerPosition, direction, 10.0f, 500);
	}

	if (_inputManager.isKeyDown(SDL_BUTTON_RIGHT))
	{
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenCoordsToWorld(mouseCoords);

		//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";

		glm::vec2 playerPosition;
		playerPosition.x = 70.0f;
		playerPosition.y = 60.0f;
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		//Accepts non default constructor arguments. Gets rid of the middle man
		//So no need to create a temp object of a class!
		_catBullets.emplace_back(playerPosition, direction, 10.0f, 500);
	}
}

//----------------------------------- Draw the game! -----------------------------------
//Draw what you want in the window
void MainGame::drawGame()
{

	/*Clear the screen*/
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Use the shader
	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);
	//Bind the texture
	//glBindTexture(GL_TEXTURE_2D, _playerTexture.id);

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");

	glUniform1i(textureLocation, 0);

	//Find our variable in our shader files
	//Set the time variable
	//GLint timeLocation = _colorProgram.getUniformLocation("time");
	//1f for 1 float
	//glUniform1f(timeLocation, _time);

	//Set the camera matrix
	GLint pLocation = _colorProgram.getUniformLocation("p");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	//[0][0], becuase it's a 2dim array and it requires a pointer to our camera, so we'll just give it the adress operator
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();

	/*glm::vec4 pos(-175.0f, -100.0f, 350.0f, 350.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);*/

	//Texture path test: "Textures/robotfree/png/Idle (1).png"
	/*static CSGengine::GLTexture texture = CSGengine::ResourceManager::getTexture("Textures/robotfree/png/JumpShoot (5).png");
	CSGengine::Color color;
	color.a = 255;
	color.b = 255;
	color.g = 255;
	color.r = 255;

	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);*/

	for (int i = 0; i < _bullets.size(); i++)
	{
			_bullets[i].draw(_spriteBatch);	
	}

	for (int i = 0; i < _catBullets.size(); i++)
	{
		_catBullets[i].draw(_spriteBatch);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	//No longer using sprite class, switching to SpriteBatch
	//Draw the srpite. This is a temp one just for testing
	//_testSprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
	//Updated from the test sprite to our new vectors now
	//for (int i = 0; i < _sprites.size(); i++)
	//{
	//	_sprites[i]->draw();
	//}

	glBindTexture(GL_TEXTURE_2D, 0);

	//Unuse the shader
	_colorProgram.unUse();


	/*Immediate mode. Don't use it, it's bad, discontuined, but it was used to test and just to see how it works. 
	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(-1, -1);
	glVertex2f(0, -1);
	glVertex2f(0, 0);
	glEnd();
	*/
	/*Swap to the other frame so that it looks smooth, rather then flickering*/
	_window.swapBuffer();

}

//------------------------------------- Calculate the FPS function here ------------------------------------------

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