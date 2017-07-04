#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace CSGengine
{
	class Camera2D
	{
		public:
			Camera2D();
			virtual ~Camera2D();

			void init(int screenWdith, int screenHeight);
			//Update our camera
			void updateCamera();

			//Set functions
			void setPosition(const glm::vec2& newPosition);
			void setScale(float newScale);

			//Get functions
			glm::vec2 getPosition()const;
			float getScale()const;
			glm::mat4 getCameraMatrix()const;

			//This function will get screen coordinates and turn them into world coordinates
			//Not const becuase it'll convert the screen coordinates to world coordinates
			glm::vec2 convertScreenCoordsToWorld(glm::vec2 screenCoords);

		private:
			//GLM variables
			glm::vec2 _position;
			glm::mat4 _cameraMatrix;
			glm::mat4 _orthoMatrix;
			//Flaots
			float _scale;
			//Booleans
			bool _needsMatrixUpdate;
			//ints
			int _screenWidth;
			int _screenHeight;
	};
}
