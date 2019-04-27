#include "GameControllerListener.h"
#include "../../ContinuumEngine.h"
#include <stdio.h>


namespace ContinuumEngine3D {

	ContinuumEngine* GameControllerListener::engineInstance = nullptr;

	GameControllerListener::~GameControllerListener() {
		engineInstance = nullptr;
	}

	void GameControllerListener::RegisterEngineObject(ContinuumEngine* engine_) {
		engineInstance = engine_;
	}

	void GameControllerListener::Update(SDL_Event e_)
	{
		int controllerIndex = e_.cdevice.which;


		//SDL_GameController * controller;
		//if (e_.type == SDL_CONTROLLERDEVICEADDED) // Adding controller during runtime without turning off the game
		//{
		//	if (SDL_IsGameController(controllerIndex)) {
		//		controller = SDL_GameControllerOpen(controllerIndex);
		//		SDL_Joystick* joystick = SDL_GameControllerGetJoystick(controller);
		//		SDL_JoystickID joyID = SDL_JoystickInstanceID(joystick);
		//		printf("hehehe");
		//	}
		//}
		//if (e_.type == SDL_CONTROLLERDEVICEREMOVED) {
		//	controller = SDL_GameControllerOpen(controllerIndex);
		//	int myInstance = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
		//	printf("Hay");
		//}
		if (e_.type == SDL_CONTROLLERDEVICEADDED)
			onControllerConnected(e_, controllerIndex);
		if (e_.type == SDL_CONTROLLERDEVICEREMOVED)
			onControllerDisconnected(e_, controllerIndex);
		if (e_.type == SDL_CONTROLLERAXISMOTION)
			onAxisEvents(e_);
		if (e_.type == SDL_CONTROLLERBUTTONDOWN)
			onButtonPressed(e_);
		else if (e_.type == SDL_CONTROLLERBUTTONUP)
			onButtonReleased(e_);
	}

	void GameControllerListener::onAxisEvents(SDL_Event e_)
	{
		engineInstance->NotifyOfAxisEvents(e_);
	}

	void GameControllerListener::onButtonPressed(SDL_Event e_)
	{
		engineInstance->NotifyOfButtonPressed(e_);
	}

	void GameControllerListener::onButtonReleased(SDL_Event e_)
	{
		engineInstance->NotifyOfButtonReleased(e_);
	}

	void GameControllerListener::onControllerConnected(SDL_Event e_, int controllerIndex_)
	{
		engineInstance->NotifyOfControllerConnected(e_, controllerIndex_);
	}

	void GameControllerListener::onControllerDisconnected(SDL_Event e_, int controllerIndex_)
	{
		engineInstance->NotifyOfControllerDisconnected(e_, controllerIndex_);
	}

}