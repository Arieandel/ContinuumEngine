#include "InputManager.h"


namespace ContinuumEngine2D {

	InputManager::InputManager() : _mouseCoords(0.0f, 0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update() {

		for (auto& it : _keyMap) {
			_previouskeyMap[it.first] = it.second;
		}
	}

	void InputManager::pressKey(unsigned int keyID) {

		_keyMap[keyID] = true;

	}

	void InputManager::releaseKey(unsigned int keyID) {

		_keyMap[keyID] = false;

	}

	bool InputManager::isKeyPressed(unsigned int keyID) {

		bool isPressed;
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
			return true;
		}
		return false;
	}

	bool InputManager::isKeyDown(unsigned int keyID) {

		auto mit = _keyMap.find(keyID);
		if (mit != _keyMap.end()) {
			return mit->second;
		}
		else {
			return false;
		}

	}

	bool InputManager::wasKeyDown(unsigned int keyID) {

		auto mit = _previouskeyMap.find(keyID);
		if (mit != _previouskeyMap.end()) {
			return mit->second;
		}
		else {
			return false;
		}

	}

	void InputManager::setMouseCoords(float x, float y) {

		_mouseCoords = glm::vec2(x, y);

	}
}