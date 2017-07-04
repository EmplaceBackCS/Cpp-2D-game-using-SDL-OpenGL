#include "ImageLoader.h"
#include "IOManager.h"
#include "picoPNG.h"
#include "Errors.h"

namespace CSGengine
{
	GLTexture ImageLoader::loadPNG(std::string filePath)
	{
		//Since we are initializing a struct, an easy way to make everything equal to 0 is to use = {}; 
		GLTexture texture = {};

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;
		unsigned long width, height;

		//Some error handling
		if (IOManager::ReadFileToBuffer(filePath, in) == false)
		{
			getFatalError("Failed to load PNG file to buffer!");
		}
		//From our picoPNG class. Credits to picopng
		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

		//Just a bi tof error handling. decodePNG always returns 0 when successful, so if something went wrong, it won't be equal to 0
		if (errorCode != 0)
		{
			getFatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		//Generate our texture and fill it with pixel data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//Maginifcation filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		//Bind 0, which means unbind the current texture. Always unbind things we aren't using anymore 
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}
}