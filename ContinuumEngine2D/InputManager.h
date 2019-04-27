#pragma once
#include <unordered_map>
#include <OpenGL/glm/glm.hpp>

namespace ContinuumEngine2D {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		//using this for now, better implementation would be to create an enum class to wrap all desired sdl keys
		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		void setMouseCoords(float x, float y);

		//returns true if key was held down
		bool isKeyDown(unsigned int keyID);
		//returns true if key was just pressed
		bool isKeyPressed(unsigned int keyID);

		//getters
		glm::vec2 getMouseCoords() const { return _mouseCoords; }

	private:
		bool wasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previouskeyMap;
		glm::vec2 _mouseCoords;

	};

}