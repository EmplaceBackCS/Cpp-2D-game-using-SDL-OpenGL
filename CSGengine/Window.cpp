#include "Window.h"

namespace CSGengine
{

	Window::Window() :
		_sdlWindow(nullptr),
		_screenWidth(800),
		_screenHeight(600)
	{
	}


	Window::~Window()
	{
	}

	//----------------------------------- Create the window with our createWindow function -----------------------------

	//This will create a window. Send in the name you want to appear at the top , the screen width, height, and a flag.
	//If you do not know what a flag is, just pass in 0 and it'll be windowded mode
	int Window::createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
		//Bit wise operators
		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BOARDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		//Create the window
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

		//-----------------------------------------Error handling----------------------------------------
		//If for some reason, the pointer we created from the window class is still null, close the program
		//And display an error message
		if (_sdlWindow == nullptr)
		{
			getFatalError("SDL window could not be created, there was an error!");
		}
		
		//If gl context could not be created, display an error message and close the program
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr)
		{
			getFatalError("GL context could not be created, there was an error!");
		}

		//If there are weird crashes, uncomment the line below and use it
		//glewExperimental = true;
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			getFatalError("Could not open GLEW");
		}
		//---------------------------------------End of error handling-----------------------------


		//This is to color the screen. Red, green, blue is the color order, max of 1.0f
		glClearColor(1.0f, 0.0f, 0.5f, 1.0f);

		//Print out the OpenGL version to check what the user is using. 
		std::cout << "*** OpenGL version: " << glGetString(GL_VERSION) << " ***\n";
		/*std::printf("*** OpenGL version: %s ***\n", glGetString(GL_VERSION));*/

		//Vsync. 0 is off, 1 is on
		SDL_GL_SetSwapInterval(0);

		//Enable blending. Normal alpha blending
		//This is so the background picture(Usually the transparent part of the sprite)
		//Will be clear
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Returns 0 as everything is a okay!
		return 0;
	}

	//------------------------------------ Swap the buffer -----------------------------
	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}

	//---------------------------- Get screen width -----------------------------
	int Window::getScreenWidth()const
	{
		return _screenWidth;
	}

	//---------------------------- Get screen hieght -----------------------------
	int Window::getScreenHeight()const
	{
		return _screenHeight;
	}
}