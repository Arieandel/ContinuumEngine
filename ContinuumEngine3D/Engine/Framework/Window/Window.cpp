#include "Window.h"


namespace ContinuumEngine3D {

	Window::Window() : window(nullptr)
	{
	}


	Window::~Window()
	{
		Shutdown();
	}

	bool Window::Initialize(std::string name, int width, int height_, unsigned int currentFlags) {

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}

		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
			Debug::FatalError("Window failed to SDL", __FILE__, __LINE__);
			return false;
		}
		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}

		this->width = width;
		this->height = height_;
		window = SDL_CreateWindow(name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			flags);
		if (!window) {
			std::cout << "Failed to create window" << std::endl;
			return false;
		}

		context = SDL_GL_CreateContext(window);

		SetAttributes();

		GLenum err = glewInit();
		if (err != GLEW_OK) {
			Debug::FatalError("Window failed to GLEW", __FILE__, __LINE__);
			return false;
		}

		glEnable(GL_DEPTH_TEST);

		glViewport(0, 0, width, height);// recall this function when you update your screen size

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		return true;
	}
	void Window::Shutdown() {
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	int Window::GetWidth() {
		return width;
	}

	int Window::GetHeight() {
		return height;
	}

	SDL_Window* Window::GetWindow() const {
		return window;
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(window);
	}

	void Window::SetAttributes() {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

		SDL_GL_SetSwapInterval(1);

		glewExperimental = GL_TRUE;
	}

}