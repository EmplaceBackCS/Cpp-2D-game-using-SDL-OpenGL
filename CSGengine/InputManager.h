#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace CSGengine
{
	class InputManager
	{
		public:
			InputManager();
			virtual ~InputManager();

			//Update function
			void update();

			//Use this function to tell the manager that we have pressed a key
			void checkForPressedKey(unsigned int keyID);

			//Check when the key was released
			void checkReleasedKey(unsigned int keyID);

			//Set the mouse coordinates
			void setMouseCoords(float x, float y);

			//If a key is held down, this should return true
			bool isKeyDown(unsigned int keyID);

			//Returns true if the key was just pressed
			bool isKeyPressed(unsigned int keyID);

			//----------------- Get functions ---------------------------
			glm::vec2 getMouseCoords()const { return _mouseCoords; }
			

		private:

			//If a key a key was pressed last frame
			bool wasKeyDown(unsigned int keyID);


			//We don't care if it's in order or not
			//Key is an unsigned int and the value we want is a bool(Is it pressed?)
			std::unordered_map<unsigned int, bool> _keyMap; //Current key
			std::unordered_map<unsigned int, bool> _prevKeyMap; // Previous key map

			//GLM variables
			//Mouse x/y coordinates
			glm::vec2 _mouseCoords;
	};
}

