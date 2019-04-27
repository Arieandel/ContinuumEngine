#ifndef MOUSEEVENTHANDLER_H
#define MOUSEEVENTHANDLER_H

#include <SDL/SDL.h>
#include <OpenGL/glm/glm.hpp>

namespace ContinuumEngine3D {

	class ContinuumEngine;

	class MouseEventListener
	{
	public:
		MouseEventListener() = delete;
		MouseEventListener(const MouseEventListener&) = delete;
		MouseEventListener(MouseEventListener&&) = delete;
		MouseEventListener& operator=(const MouseEventListener&) = delete;
		MouseEventListener& operator=(MouseEventListener&&) = delete;
		~MouseEventListener();
		static void RegisterEngineObject(ContinuumEngine* engine_);
		static void Update(SDL_Event e_);
		static void NotifyOfMousePressed(int buttonType_);
		static void NotifyOfMouseReleased(int buttonType_);
		static void NotifyOfMouseMove();
		static void NotifyOfMouseScroll(int y_);
		static glm::vec2 GetPreviousMousePosition();
		static glm::vec2 GetMousePosition();
		static glm::vec2 GetMouseOffset();

	private:
		static ContinuumEngine * engineInstance;
		static int mouseX, mouseY, prevMouseX, prevMouseY;
		static bool firstUpdate;
		static void UpdateMousePosition();
	};

}

#endif