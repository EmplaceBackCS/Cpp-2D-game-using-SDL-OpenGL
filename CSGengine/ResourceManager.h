#pragma once
#include "TextureCache.h"
#include "GLTexture.h"
#include <string>

namespace CSGengine
{
	//This will be a static class, so no need for a destructor/constructor
	class ResourceManager
	{
	public:
		//wrapper, literally does nothing but call getTexture, but they can be very useful. 
		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;


	};
}
