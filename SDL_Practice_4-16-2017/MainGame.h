#pragma once
#include<Windows.h>
#include<SDL/SDL.h>
#include<GL/glew.h>
#include <vector>
/*For debugging and pausing when needed*/
#include<iostream>
#include<string>
/*Header files for the gameEngine made by Cesar Saucedo*/
#include <CSGengine/CSGengine.h>
#include <CSGengine/Sprite.h>
#include <CSGengine/Errors.h>
#include <CSGengine/GLSLProgram.h>
#include <CSGengine/GLTexture.h>
#include <CSGengine/Window.h>
#include <CSGengine/Camera2D.h>
#include <CSGengine/SpriteBatch.h>
#include <CSGengine/ResourceManager.h>
#include <CSGengine/InputManager.h>
#include <CSGengine/Timing.h>
//Header files from the game file, not the engine
#include "Projectile.h"
#include "CatBullets.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
	public:
		/*Constructors*/
		MainGame();
		virtual ~MainGame();
		/*Run the Game*/
		void run();

	private:
		//--------------------------------------- Functions ---------------------------------------
		/*Initilize the systems*/
		void initSystems();
		void initShaders();
		/*Get input from mouse/keybored/etc...Using SDL*/
		void processInput();
		/*Game Functions*/
		void gameLoop();
		void drawGame();
		//FPS related functions
		void getFPS_OnConsole();

		//---------------------------------- Variables ------------------------------------
		/*Window variables*/
		CSGengine::Window _window;
		/*Int variables*/
		int _screenWidth;
		int _screenHeight;
		/*Game state variables(From Enum)*/
		GameState _currentGameState;
		//Floats
		float _time;
		float _speedOfTime;
		float _fps;
		float _maxFPS;
		//Temp float for camera speed/scale/zoom
		const float _CAMERA_SPEED = 10.0f;
		const float _SCALE_SPEED = 0.1f;
		//Camera variables
		CSGengine::Camera2D _camera;
		//Sprite variables
		//Sprite _testSprite;
		//We'll have a vector of sprite pointers so that each time we push back
		//We won't lose our old sprites and can print out as many as we want
		//We're switching out of the sprite vector and using our new class
		//SpriteBatch
		//std::vector<CSGengine::Sprite*> _sprites;
		//GLSL variables
		CSGengine::GLSLProgram _colorProgram;
		//Sprite batch variables
		CSGengine::SpriteBatch _spriteBatch;

		//Input manger variables(Keyboard hits and mouse movement)
		CSGengine::InputManager _inputManager;

		//Timing virables
		//Fps limiter
		CSGengine::FpsLimiter _fpsLimiter;

		//Projectile class object
		std::vector<Projectile> _bullets;
		std::vector<CatBullets> _catBullets;
		//GLTexture variables
		//This is just temp to test our loader
		//We are removing _playerTexture as we are going to use a tree now/bionary search for images.
		//It was mostly a test to see if our picoPNg and our imageloader class worked
		//GLTexture _playerTexture;
};

