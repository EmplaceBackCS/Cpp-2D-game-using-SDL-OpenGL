#include "Player.h"

//-------------------------------------------------- Constructor ----------------------------------------
Player::Player() :
	Human()
{
}


Player::~Player()
{
}


//-------------------------------------------------- Init the player ----------------------------------------
void Player::init(
	float speed, 
	glm::vec2 pos, 
	CSGengine::InputManager* ipManager, 
	CSGengine::Camera2D* camera)
{
	_speed = speed;
	_pos = pos;
	_ipManager = ipManager;
	_camera = camera;
	_color = CSGengine::ColorRGBA8(255, 0, 255, 255);
}

//-------------------------------------------------- Update the player ----------------------------------------
void Player::update(
	const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies)
{
	//------------------------------------ Movement keys -----------------------------
	//Up
	if (_ipManager->isKeyDown(SDLK_w))
	{
		_pos.y += _speed;
	}
	//Down
	if (_ipManager->isKeyDown(SDLK_s))
	{
		_pos.y -= _speed;
	}
	//Left
	if (_ipManager->isKeyDown(SDLK_a))
	{
		_pos.x -= _speed;
	}
	//Right
	if (_ipManager->isKeyDown(SDLK_d))
	{
		_pos.x += _speed;
	}
	//------------------------------------ End of Movement keys -----------------------------


	//Check collision with the level
	//This will determine if we hit a block or not
	checkCollision(levelData);
}