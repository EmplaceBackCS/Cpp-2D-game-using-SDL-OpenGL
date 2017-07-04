#pragma once
#include <map>
#include <string>
#include "GLTexture.h"

namespace CSGengine
{
	class TextureCache
	{
	public:
		TextureCache();
		virtual ~TextureCache();

		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}
