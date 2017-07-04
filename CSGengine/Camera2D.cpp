#include "Camera2D.h"


namespace CSGengine
{
	//--------------------------- Constructors/destructors ---------------------------------
	Camera2D::Camera2D():
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(true),
		_screenWidth(500),
		_screenHeight(500)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	//
	void Camera2D::init(int screenWdith, int screenHeight)
	{
		_screenWidth = screenWdith;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	//--------------------------------- Update the camera -------------------------------
	void Camera2D::updateCamera()
	{
		//If we need to move the camera, we should update it with the new positions
		//If we are moving the camera to the right, everything should move to the left
		//And vice versa
		if (_needsMatrixUpdate)
		{
			//Camera translation!
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//Fix the camera scale
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
			//And then just set it to false so if there's no movement/change, it won't update
			_needsMatrixUpdate = false;
		}
	}

	//-------------------------------- Set position ---------------------------------
	void Camera2D::setPosition(const glm::vec2& newPosition)
	{
		_position = newPosition;
		//Whenever we change the position, or the position is moved, the camera will need an update so we will
		//Set it to true
		_needsMatrixUpdate = true;
	}

	//------------------------------- Set the scale/zoom ------------------------------
	void Camera2D::setScale(float newScale)
	{
		_scale = newScale;
		//Whenever we set the scale/zoom, we'll have to update the camera again
		//So we'll set it to true
		_needsMatrixUpdate = true;
	}


	//----------------------------- Get the position -------------------------------
	glm::vec2 Camera2D::getPosition()const
	{
		return _position;
	}

	//------------------------------ Get scale/zoom ----------------------------------
	float Camera2D::getScale()const
	{
		return _scale;
	}

	//------------------------------------ Get Ortho matrix -----------------------------
	glm::mat4 Camera2D::getCameraMatrix()const
	{
		return _cameraMatrix;
	}

	//------------------------------------ Get screen coordinates ---------------------
	glm::vec2 Camera2D::convertScreenCoordsToWorld(glm::vec2 screenCoords)
	{
		//Invert the Y coordiante, since OpenGL is a bit weird and has backwards coordinates
		screenCoords.y = _screenHeight - screenCoords.y;
		//We're changing the coordinate system. Instead of setting 0,0 at the top left corner
		//Of the screen, we're making it so the center of our screen is 0,0 coordinates(x,y)
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);

		//We're doing the same as we did with x,y, but this time with zoom
		screenCoords /= _scale;

		//Translate with the camera position now that we fixed our world coordinates
		screenCoords += _position;

		return screenCoords;
	}
}

