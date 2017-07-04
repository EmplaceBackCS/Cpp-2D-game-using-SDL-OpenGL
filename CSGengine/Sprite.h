#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>
#include "ResourceManager.h"

namespace CSGengine
{
	class Sprite
	{
	public:
		/*Constructors*/
		Sprite() : _vboID(0) {}
		virtual ~Sprite()
		{
			//Always delete your buffers once you are done with them
			if (_vboID != 0)
			{
				glDeleteBuffers(1, &_vboID);
			}
		}
		/*Drawing the sprite fucntions*/
		void draw();
		void init(float x, float y, float width, float height, std::string texturePath);

	private:
		float _x, _y, _width, _height;
		static unsigned short const _SIZE = 6;
		/*GL, unsigned int. The same as unsined int, but it's 100% that it's a 32bit*/
		GLuint _vboID;
		GLTexture _texture;

	};
}