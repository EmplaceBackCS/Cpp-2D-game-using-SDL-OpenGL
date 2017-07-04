#include "Projectile.h"

//---------------------------------- Constructor/destructors --------------------------------
Projectile::Projectile() :
	_position(0.0f),
	_speed(0.0f),
	_direction(0.0f),
	_lifeTime(1)
{
}

Projectile::Projectile(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime):
	_position(pos),
	_direction(direction),
	_speed(speed),
	_lifeTime(lifeTime)
{}


Projectile::~Projectile()
{
}

//--------------------------------------------- Initilize ----------------------------------
//This function has just been moved to the constructor. Might use this later, commented out for now
// Start everything that we need to start drawing the projectile 
//void Projectile::init(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime)
//{
//	_lifeTime = lifeTime;
//	_position = pos;
//	_direction = direction;
//	_speed = speed;
//}

//------------------------------------ Draw the projectile ----------------------------
//Currently going to use the spritebatch class. Might change this in the future
void Projectile::draw(CSGengine::SpriteBatch& spriteBatch)
{
	CSGengine::ColorRGBA8;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	//This was copied and pasted from main game. This is just to test out our class, bad practice to do this!
	static CSGengine::GLTexture texture = CSGengine::ResourceManager::getTexture("Textures/robotfree/png/Objects/Bullet_004.png");

	CSGengine::ColorRGBA8 color;
	color.a = 255;
	color.b = 255;
	color.g = 255;
	color.r = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 250, 250);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool Projectile::update()
{
	_position += (_direction * _speed);
	//Make sure every frame we update, we shorten the lifetime
	//of our bullet
	_lifeTime--;

	if (_lifeTime == 0)
	{
		return true;
	}

	//Returns false if life time isn't 0
	return false;
}
