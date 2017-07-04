#include "Timing.h"
#include <SDL/SDL.h>
namespace CSGengine
{
	//---------------------------------- Constructors/Destructors --------------------------------
	FpsLimiter::FpsLimiter() :
		_maxFPS(60.0f),
		_startTicks(0),
		_fps(0.0f),
		_frameTime(0.0f)
	{
	}
	FpsLimiter::~FpsLimiter()
	{
	}

	//---------------------------------- Initilize what we need ------------------------------------
	void FpsLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	//---------------------------------- Begin function will start the calculation ---------------------------
	//This will store the SDL current ticks to calculate the fps for end
	void FpsLimiter::begin()
	{
		_startTicks = SDL_GetTicks();
	}
	//---------------------------------- End function will display the current FPS ------------------------
	//End will return the current FPS
	float FpsLimiter::end()
	{
		calculateFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;
		//Limit fps to the max fps we want
		if (1000.f / _maxFPS > frameTicks)
		{
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}

		return _fps;

	}

	//------------------------------- Set target FPS, frame rate limiter -------------------------
	void FpsLimiter::setMaxFPS(float maxFPS)
	{
		_maxFPS = maxFPS;
	}

	void FpsLimiter::calculateFPS()
	{
		//Making these statis so they are only made once
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		//We want to keep track of all our ticks, we this will be a static also
		static float prevTicks = SDL_GetTicks();
		float currentTicks;

		currentTicks = SDL_GetTicks();

		_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

		//We need to reset it, or else our fps counter is wrong and the number gets smaller and smaller
		//Meaning the prev ticks are always going to be from the start of the program, which is completely wrong
		prevTicks = currentTicks;

		int count;

		currentFrame++;
		if (currentFrame < NUM_SAMPLES)
		{
			count = currentFrame;
		}
		else
		{
			count = NUM_SAMPLES;
		}

		float frameTimeAverage = 0;
		//i < count because we only want to average our total frames
		for (int i = 0; i < count; i++)
		{
			frameTimeAverage += frameTimes[i];
		}

		frameTimeAverage /= count;

		if (frameTimeAverage > 0)
		{
			_fps = 1000.0f / frameTimeAverage;
		}
		else
		{
			_fps = 600.0f;
		}
	}
}