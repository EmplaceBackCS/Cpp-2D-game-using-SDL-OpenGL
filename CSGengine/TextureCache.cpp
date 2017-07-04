#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace CSGengine
{

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	//------------------------------ Get texture function. Will crash the game if nothing returns -------------------------------------

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//We are using a string as the key, the GLTexture as the value. The iterator will return us a vlaue, or a 
		// map::end(); if no value is found
		//This first way is a really long decleration, so we can use the keyword auto here and figure out what it is 
		//A long way to do it -> std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);
		//This will look up the texture and see if it's in the map
		auto mit = _textureMap.find(texturePath);

		//Lets error check and see if it's not in the map
		//Like said above, if it can't find what we were looking for, it'll instead return a map::end();
		if (mit == _textureMap.end())
		{
			//If this fails, it's going to call fatal error anyways and we don't need to make one here
			//This will load our texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//Takes in a key and a value. This is another template
			//The newPair is a constructor and we can initilize it here
			//The key will be the file path always for our png(at least for now, currently 4/26/2017
			//The value is the texture
			//std::pair<std::string, GLTexture> newPair(texturePath, newTexture); <-- Exmaple pair1
			//This is one way to do it. Another way is let it create a new pair out of the elements
			//_textureMap.insert(newPair); <--- part of Example pair1
			//To shorten it, we can do this:
			//This will insert our new texture into our map
			_textureMap.insert(make_pair(texturePath, newTexture)); // The makepair function does what was shown above in 'Example pair1'

			//std::cout << "Used cache texture!\n"; //Just to check where it loaded from
			return newTexture;
		}

		//If that mit is not returning a map::end();, then we can return our texture we wanted
		//Mit is a pointer, it has a pair and so we want to return the value, not the key. So we will return second, which is 
		//The value(in our case the texture)
		//std::cout << "Loaded texture!\n";//Just to check where it loaded from
		return mit->second;

	}

}