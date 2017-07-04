#pragma once

namespace CSGengine
{
	class FpsLimiter
	{
		public:
			//Constructors/destructors
			FpsLimiter();
			virtual ~FpsLimiter();

			void init(float maxFPS);

			//Frame rate limiter
			void setMaxFPS(float maxFPS);
			//This will store the SDL current ticks to calculate the fps for end
			void begin();
			//End will return the current FPS
			float end();

		private:
			//private functions
			void calculateFPS();
			
			//floats
			float _maxFPS;
			float _fps;
			float _frameTime;
			//unsinged ints
			unsigned int _startTicks;
	};

}
