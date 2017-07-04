#pragma once
#include <glm/glm.hpp>
#include <CSGengine/SpriteBatch.h>
#include <CSGengine/ResourceManager.h>
#include <vector>
#include <string>

class Human;
class Zombie;

class Bullets
{
	public:
		Bullets();
		~Bullets();

		//To draw bullets the old way
		Bullets(glm::vec2 pos, glm::vec2 direction, float speed, float lifeTime, int size);

		/*Bullets(glm::vec2 pos, glm::vec2 direction, float speed, float damage);*/

		virtual void draw(CSGengine::SpriteBatch& spriteBatch);

		virtual void function() = 0;
		//So we can update the position of our projectile every frame
		//Returns true when we are out of life
		virtual bool update();

		virtual bool checkBulletCollision(std::vector<Zombie*> zombie, int& index);

		//Check collision with the world!
		virtual bool checkBulletCollisionWithWorld(const std::vector<std::string>& levelData);

		//Get functions
		virtual float getPositionX()const { return _position.x; }
		virtual float getPositionY()const { return _position.y; }
		virtual glm::vec2 getDirection()const { return _direction; }
		virtual int getLifeTime()const { return _lifeTime; }
		virtual float getSpeed()const { return _speed; }
		virtual glm::vec2 getPosition()const { return _position;}
		virtual int getSize()const { return _size; }

		//Set functions
		virtual void setPosition(glm::vec2 position);
		virtual void setLifeTime(int lifeTime) { _lifeTime += lifeTime; }

	private:

		//------------This should be the same tile width as level.h---------
		//------------------------------------------------------------------
		
		//------------This should be the same tile width as level.h---------
		//------------------------------------------------------------------
		//floats
		//Speed of our projectile/Velocity
		float _speed;
		float _damage;

		//ints
		//Life time varaible, to determine how many frames we want the projectile to be
		int _lifeTime;

		int _size;

		//Vector variables
		//Direction we want our projectile to go
		glm::vec2 _direction;
		//The position we want it
		glm::vec2 _position;
};

