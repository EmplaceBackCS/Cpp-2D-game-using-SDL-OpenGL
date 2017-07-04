#include "ShotGun.h"
#include <cstdlib>
#include <ctime>
#include <random>
ShotGun::ShotGun() : Guns()
{
}


ShotGun::~ShotGun()
{
}

//Shot gun bullets with the mouse as the coordinates
void ShotGun::getGun(
	std::vector<Bullets*>& bullets,
	const CSGengine::InputManager* im,
	const  Player* player,
	const CSGengine::Camera2D& camera)
{
	static const float SPEED = 15.0f;
	static const int LIFETIME = 25;
	static const float SPREAD = 0.5f;
	static const int SIZE = 10;

	//Set the camera up
	_camera = camera;

	_mouseCoords = im->getMouseCoords();
	/*std::cout << mouseCoords.x << " <--X Y--> " << mouseCoords.y << " \n";*/
	_mouseCoords = _camera.convertScreenCoordsToWorld(_mouseCoords);

	//Left facing bullets
	if (_mouseCoords.x < player->getPosX())
	{
		//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";

		_direction = _mouseCoords - player->getPos();
		_direction = glm::normalize(_direction);
		/*std::cout << _direction.x << "<-- X Y -->" << " " << _direction.y << std::endl;*/
		//Accepts non default constructor arguments. Gets rid of the middle man
		/*So no need to create a temp object of a class!*/
		_direction.x -= SPREAD;
		_direction.y += SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's randomized, set the first set bullet
		bullets.emplace_back(new LeftBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
		//Redo the bullet x/y again slightly
		_direction.x -= SPREAD;
		_direction.y += SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new LeftBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
		//Redo the bullet x/y again slightly
		_direction.x += SPREAD;
		_direction.y -= SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new LeftBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));

		//Second batch of bullets
		//Reset the positon and go the opposite way
		_direction = _mouseCoords - player->getPos();
		_direction = glm::normalize(_direction);
		//Redo them again
		_direction.x += SPREAD;
		_direction.y -= SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new LeftBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
		//Redo the bullet x/y again slightly
		_direction.x += SPREAD;
		_direction.y -= SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new LeftBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
		//Redo the bullet x/y again slightly
		_direction.x -= SPREAD;
		_direction.y += SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new LeftBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
	}
	else
	{
		//Right facing bullets 
		
		//Set up the spread bullets
		_direction.x -= SPREAD;
		_direction.y += SPREAD;
		_direction = glm::normalize(_direction);
		bullets.emplace_back(new RightBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
		//Redo the bullet x/y again slightly
		_direction.x -= SPREAD;
		_direction.y += SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new RightBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
		//Redo the bullet x/y again slightly
		_direction.x += SPREAD;
		_direction.y -= SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new RightBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));

		//Second batch of bullets
		//Reset the positon and go the opposite way
		_direction = _mouseCoords - player->getPos();
		_direction = glm::normalize(_direction);
		//Redo them again
		_direction.x += SPREAD;
		_direction.y -= SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new RightBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
		//Redo the bullet x/y again slightly
		_direction.x += SPREAD;
		_direction.y -= SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new RightBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
		//Redo the bullet x/y again slightly
		_direction.x -= SPREAD;
		_direction.y += SPREAD;
		_direction = glm::normalize(_direction);
		//Once it's moved slightly, emplace back a new bullet
		bullets.emplace_back(new RightBullets(player->getPos(), _direction, SPEED, LIFETIME, _BULLET_SIZE - SIZE));
	}
}

