#include "GiantSlowGun.h"

GiantSlowGun::GiantSlowGun() : Guns()
{
}


GiantSlowGun::~GiantSlowGun()
{
}

//---------------------------------------- Was remade to a land mine for a different effect then just shooting -----------------------
//This now just places a bomb/mine at the player and won't move at all
//------------------------------------------------------------------------------------------------------------------------------------

//Bullet changes
//This is a land mine, no need for an if statement like the others
void GiantSlowGun::getGun(
	std::vector<Bullets*>& bullets,
	const CSGengine::InputManager* im,
	const  Player* player,
	const CSGengine::Camera2D& camera)
{
	_camera = camera;

	_mouseCoords = im->getMouseCoords();
	/*std::cout << mouseCoords.x << " <--X Y--> " << mouseCoords.y << " \n";*/
	_mouseCoords = _camera.convertScreenCoordsToWorld(_mouseCoords);

	//std::cout << "X/Y Mouse coordinates: " << mouseCoords.x << " " << mouseCoords.y << " \n";
	glm::vec2 tempPos;
	tempPos.x = player->getPosX() + 0.1f;
	tempPos.y = player->getPosY() + 0.1f;

	_direction = _mouseCoords - player->getPos();
	_direction = glm::normalize(_direction);
	/*std::cout << _direction.x << "<-- X Y -->" << " " << _direction.y << std::endl;*/
	//Accepts non default constructor arguments. Gets rid of the middle man
	/*So no need to create a temp object of a class!*/
	bullets.emplace_back(new LandMine(player->getPos(), _direction, 0.0f, 300, _BULLET_SIZE));
}