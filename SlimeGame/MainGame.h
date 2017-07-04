#pragma once
//Engine files 
#include <CSGengine/CSGengine.h>
#include <CSGengine/GLSLProgram.h>
#include <CSGengine/Window.h>
#include <CSGengine/Camera2D.h>
#include <CSGengine/InputManager.h>
#include <CSGengine/Timing.h>
#include <CSGengine/SpriteBatch.h>
//Files made in this project
#include "Level.h"
#include "Player.h"
#include "Zombie.h"
#include "PlayerShadow.h"
#include "LeftBullets.h"
#include "Zombie.h"
#include "RightBullets.h"
#include "UpBullets.h"
#include "DownBullets.h"
#include "Bullets.h"
#include "Pistol.h"
#include "ShotGun.h"
#include "GiantSlowGun.h"
//Normal headers
#include <cstdlib>
#include <time.h>
#include <glm/glm.hpp>

enum class GameState {PLAY, EXIT};

class Zombie;

class MainGame
{
	public:
		/*Constructors*/
		MainGame();
		virtual ~MainGame();
		/*Run the Game*/
		void run();

	private:
		//--------------------------------------- Private Functions ---------------------------------------
		/*Initilize the systems*/
		void initSystems();
		void initShaders();

		//Init our level and sets up everything
		void initLevel();

		/*Get input from mouse/keybored/etc...Using SDL*/
		void processInput();
		/*Game Functions*/
		void gameLoop();
		//Update Shadow effect
		void upDateTrailingShadow(std::vector<PlayerShadow*>& _trailingShadow);
		//Updates all agents
		void updateAgents();
		//Update bullets
		void updateBullets();
		void drawGame();
		//FPS related functions
		void getFPS_OnConsole();
		//Cooldown
		void checkCooldown();
		void checkWeaponSwapCooldown();

		//Check if the player won
		void checkWinCondition();

		//Check fire method/current gun
		void checkBulletChoice();
		void checkBulletChoiceForKeyArrowKey();

		//Change bullets
		void normalBullets();
		void normalArrowKeyBullets();
		//Spread bullets
		void spreadBullets();
		void spreadBulletsRightArrowKey();

		//GiantSlowGun
		void giantSlowGun();

		//Check collision with the world for bullets
		void checkBulletWorldCollision();
		//Delete our pointers/vectors
		//void destroyLevel_1();

		//---------------------------------- Variables ------------------------------------
		/*Window variables*/
		CSGengine::Window _window;
		/*Int variables*/
		//-------------------------------------------------------------------- 
		//THIS SHOULD ALWAYS BE THE SAME AS THE TILE WIDTH IN THE LEVEL.H FILE
		static const int TILE_WIDTH = 64;
		//THIS SHOULD ALWAYS BE THE SAME AS THE TILE WIDTH IN THE LEVEL.H FILE
		//--------------------------------------------------------------------  
		int _screenWidth;
		int _screenHeight;
		int _currentLevel;
		int _cooldownCounter;
		int _cooldownTime;
		int _zombieIndex;
		short _zombiesKilled;
		int _bulletChoice;

		bool _cooldown;
		bool _weaponCooldown;
		int _weaponCooldownCounter;
		/*Game state variables(From Enum)*/
		GameState _currentGameState;
		//Floats
		float _time;
		float _speedOfTime;
		float _fps;
		float _maxFPS;

		//Glm stuff
		glm::vec2 _direction;
		//Our levels in a vector to grow it each time we level
		std::vector<Level*> _levels;
		//Vector for our humans
		std::vector<Human*> _humans;
		//Vector for our zombies
		std::vector<Zombie*> _zombies;
		Player* _player;
		//Temp float for camera speed/scale/zoom
		//---------------------------- Const/static variables ------------------------------------
		const float _SCALE_SPEED = 0.05f;
		//Player speed should be Should be 3.223f
		const float _PLAYER_SPEED = 4.223f;
		//Zombie speed
		const float ZOMBIE_SPEED = 3.462f;
		//AI human speed
		const float HUMAN_SPEED = 3.52f;
		//-------------Consts-------------------------
		static const int SIZE = 26;
		static const int LIFE_TIME = 100;
		const float _SPEED = 7.0f;
		static const int _PISTOL_COOLDOWN_TIME = 20;
		static const int _SPREAD_GUN_COOLDOWN_TIME = 40;
		static const int _BOMB_COOLDOWN_TIME = 15;
		static const int _MAX_NUMBER_OF_GUN = 3;
		//-------------End Consts-------------------------
		//Our camera
		CSGengine::Camera2D _camera;

		CSGengine::SpriteBatch _agentSpriteBatch; //Draw all agents
		CSGengine::SpriteBatch _shadowSpriteBatch; //Draw our shadow

		//Color the program using our shader
		CSGengine::GLSLProgram _colorProgram;
		//Input manger variables(Keyboard hits and mouse movement)
		CSGengine::InputManager _inputManager;
		//Fps limiter
		CSGengine::FpsLimiter _fpsLimiter;

		//Shadow effect
		std::vector<PlayerShadow*> _trailingShadow;
		//Bullet vector
		std::vector<Bullets*> _bullets;

		//Gun object
		Guns* _guns[_MAX_NUMBER_OF_GUN];
};

