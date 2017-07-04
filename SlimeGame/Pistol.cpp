#include "Pistol.h"

static const float _PISTOL_SPEED = 7.5f;

Pistol::Pistol() : Guns()
{
}


Pistol::~Pistol()
{
}

void Pistol::getGun(
	std::vector<Bullets*>& bullets,
	const CSGengine::InputManager* im,
	const  Player* player,
	const CSGengine::Camera2D& camera)
{
	_camera = camera;

	_mouseCoords = im->getMouseCoords();
	/*std::cout << mouseCoords.x << " <--X Y--> " << mouseCoords.y << " \n";*/
	_mouseCoords = _camera.convertScreenCoordsToWorld(_mouseCoords);

	//Find out which side the mouse is on(Right or left of the player)
	if (_mouseCoords.x < player->getPosX())
	{
		//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";

		_direction = _mouseCoords - player->getPos();
		_direction = glm::normalize(_direction);
		/*std::cout << _direction.x << "<-- X Y -->" << " " << _direction.y << std::endl;*/
		//Accepts non default constructor arguments. Gets rid of the middle man
		/*So no need to create a temp object of a class!*/
		bullets.emplace_back(new LeftBullets(player->getPos(), _direction, _PISTOL_SPEED, _LIFE_TIME + _LIFE_TIME, _BULLET_SIZE));
	}
	else
	{
		//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
		_direction = _mouseCoords - player->getPos();
		_direction = glm::normalize(_direction);
		/*std::cout << _direction.x << "<-- X Y -->" << " " << _direction.y << std::endl;*/

		//Accepts non default constructor arguments. Gets rid of the middle man
		//So no need to create a temp object of a class!
		bullets.emplace_back(new RightBullets(player->getPos(), _direction, _PISTOL_SPEED, _LIFE_TIME + _LIFE_TIME, _BULLET_SIZE));
	}

}

//------------------------------------ Arrow key bullets, so they face the right direction -------------------------------

//For the right arrow key, the bullets should face the right way
void Pistol::getGunForRightArrowKey(std::vector<Bullets*>& bullets,
	const Player* player,
	const CSGengine::Camera2D& camera)
{
	_direction.x = 0;
	_direction.y = 0;
	//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
	_direction.x += 1;
	_direction.y += 0;
	_direction = glm::normalize(_direction);

	//Emplace back the new bullet
	bullets.emplace_back(new RightBullets(player->getPos(), _direction, _PISTOL_SPEED, _LIFE_TIME, _BULLET_SIZE));
}

//For the left arrow key, bullets should face the left way
void Pistol::getGunForLeftArrowKey(
	std::vector<Bullets*>& bullets,
	const Player* 
	player,
	const CSGengine::Camera2D& camera)
{
	_direction.x = 0;
	_direction.y = 0;
	//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
	_direction.x -= 1;
	_direction.y += 0;
	_direction = glm::normalize(_direction);

	//Emplace back the new bullet
	bullets.emplace_back(new LeftBullets(player->getPos(), _direction, _PISTOL_SPEED, _LIFE_TIME, _BULLET_SIZE));
}

//For up down arrow key
void Pistol::getGunForDownArrowKey(
	std::vector<Bullets*>& bullets,
	const Player* player,
	const CSGengine::Camera2D& camera)
{
	_direction.x = 0;
	_direction.y = 0;
	//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
	_direction.x -= 0;
	_direction.y += -1;
	_direction = glm::normalize(_direction);

	//Emplace back the new bullet
	bullets.emplace_back(new DownBullets(player->getPos(), _direction, _PISTOL_SPEED, _LIFE_TIME, _BULLET_SIZE));
}

//For up up arrow key
void Pistol::getGunForUpArrowKey(
	std::vector<Bullets*>& bullets,
	const Player* player,
	const CSGengine::Camera2D& camera)
{
	_direction.x = 0;
	_direction.y = 0;
	//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
	_direction.x = 0;
	_direction.y += 1;
	_direction = glm::normalize(_direction);

	//Emplace back the new bullet
	bullets.emplace_back(new UpBullets(player->getPos(), _direction, _PISTOL_SPEED, _LIFE_TIME, _BULLET_SIZE));
}