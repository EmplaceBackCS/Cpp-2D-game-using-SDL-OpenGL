#pragma once
#include <glm/glm.hpp>
#include <CSGengine/SpriteBatch.h>
//#include <CSGengine/GLTexture.h>
#include <CSGengine/ResourceManager.h>
class Projectile
{
	public:
		Projectile();
		//Life time, number of frames it will be alive for
		Projectile(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime);
		virtual ~Projectile();

		virtual void draw(CSGengine::SpriteBatch& spriteBatch);

		//So we can update the position of our projectile every frame
		//Returns true when we are out of life
		bool update();

		//Get functions
		virtual float getPositionX()const {return _position.x;}
		virtual float getPositionY()const { return _position.y; }
		virtual glm::vec2 getDirection()const { return _direction; }
		virtual int getLifeTime()const { return _lifeTime; }
		virtual float getSpeed()const { return _speed; }

	private:
		//floats
		//Speed of our projectile
		float _speed;

		//ints
		//Life time varaible, to determine how many frames we want the projectile to be
		int _lifeTime;

		//Vector variables
		//Direction we want our projectile to go
		glm::vec2 _direction;
		//The position we want it
		glm::vec2 _position;
};

