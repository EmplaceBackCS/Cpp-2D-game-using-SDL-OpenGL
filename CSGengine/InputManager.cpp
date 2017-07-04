#include "InputManager.h"
#include <iostream>
namespace CSGengine
{

	InputManager::InputManager():
		_mouseCoords(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	//------------------------------------- Update Function ------------------------------
	void InputManager::update()
	{
		//Loop through our keymap, and copy it to the previous keymap
		for (auto& it : _keyMap) // It, iterator
		{
			_prevKeyMap[it.first] = it.second; 

		}
	}



	//---------------------------------- check if a key was hit on the keyboard ----------------------------------
	void InputManager::checkForPressedKey(unsigned int keyID)
	{
		//This will check if the key ID is even in the map.
		//If it's not on the map, it'll create it, then set it to true
		//Almost like .insert(make_pair)
		_keyMap[keyID] = true;
	}

	//------------------------------------- Check if the key is released ---------------------------------------
	void InputManager::checkReleasedKey(unsigned int keyID)
	{
		//Once we release the key, set it to false so it's no longer true that it's being pressed
		_keyMap[keyID] = false;
	}

	//------------------------------------ Set mouse coordinates -----------------------------------
	void InputManager::setMouseCoords(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	//---------------------------------- Check if the key is held down ---------------------------------
	bool InputManager::isKeyDown(unsigned int keyID)
	{
		//Just using the auto keyword so we don't have to declare it with that long data type.
		//We don't have to use associated array method here, because
		//We don't want to create a key if it doesn't exsit, so we'll
		//Manually do it
		auto it = _keyMap.find(keyID);

		//If a key was pressed, then it would never return _keyMap.end, since it will return a real value
		if (it != _keyMap.end())
		{
			//Getting here means we found a key
			return it->second;
		}

		//We'll return if nothing was pressed
		return false;
	}

	//---------------------------------- Check is key pressed -------------------------------------------
	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		//Check if a key was pressed this frame and isn't the same as last frame
		return isKeyDown(keyID) == true && wasKeyDown(keyID) == false ? true : false;
	}

	//---------------------------------- Was key down ---------------------------------------
	//Was a key pressed last frame
	bool InputManager::wasKeyDown(unsigned int keyID)
	{
		//Just using the auto keyword so we don't have to declare it with that long data type.
		//We don't have to use associated array method here, because
		//We don't want to create a key if it doesn't exsit, so we'll
		//Manually do it
		auto it = _prevKeyMap.find(keyID);

		//If a key was pressed, then it would never return _keyMap.end, since it will return a real value
		if (it != _prevKeyMap.end())
		{
			//Getting here means we found a key
			return it->second;
		}

		//We'll return if nothing was pressed
		return false;
	}

}





