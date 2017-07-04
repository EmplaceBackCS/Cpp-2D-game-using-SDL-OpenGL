#pragma once
#include "GLTexture.h"
#include <string>
#include <vector>

//Another static class, no need for a constructor/destructor
namespace CSGengine
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}