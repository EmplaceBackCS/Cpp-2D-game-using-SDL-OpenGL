#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include "Errors.h"


namespace CSGengine
{
	//Our window flags in an enum
	//0x1 is the hexi demical. 0x1 is the 1 bit
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BOARDERLESS = 0x4 };

	class Window
	{
	public:
		//Constructor/destructor. Defined in the .cpp file
		Window();
		virtual ~Window();

		//This will create a window. Send in the name you want to appear at the top , the screen width, height, and a flag.
		//If you do not know what a flag is, just pass in 0 and it'll be windowded mode
		int createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		//Swap the window, so it doesn't flicker
		void swapBuffer();

		//Get functions
		int getScreenWidth()const;
		int getScreenHeight()const;

	private:
		//This pointer will be used to create the window
		SDL_Window* _sdlWindow;

		//These will be used in the init function to get the screen width/height from the user
		int _screenWidth;
		int _screenHeight;
	};
}
