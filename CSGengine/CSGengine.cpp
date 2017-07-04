#include <SDL/SDL.h>
#include <GL/glew.h>
#include "CSGengine.h"
namespace CSGengine
{
	int init()
	{
		/*Initialize SDL and create the window*/
		SDL_Init(SDL_INIT_EVERYTHING);

		//Tell SDL we want a double buffer, so we don't get any flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}