#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

namespace CSGengine
{
	/*Helper function to see if there is a fatal error*/
	void getFatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		system("pause");
		SDL_Quit();
		exit(1);
	}
}