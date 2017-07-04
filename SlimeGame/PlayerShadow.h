#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <CSGengine/SpriteBatch.h>
#include <CSGengine/ResourceManager.h>
class PlayerShadow 
{
	public:
		PlayerShadow();
		//Using a vector with push back, so we'll use a non default constructor
		PlayerShadow(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime);
		virtual ~PlayerShadow();

		//Overriding from the bullet class
		//To create trails of fire
		bool update();
		//Resize the shadow here
		virtual void draw(CSGengine::SpriteBatch& spriteBatch);

	private:
		glm::vec2 _pos;
		glm::vec2 _direction;
		float _speed;
		int _lifeTime;


};

