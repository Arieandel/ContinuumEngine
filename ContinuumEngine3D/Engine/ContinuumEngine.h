#ifndef CONTINUUMENGINE_H
#define CONTINUUMENGINE_H

#include "Framework/Window/Window.h"
#include "GlobalElements/Timer.h"
#include "GameInterface.h"
//#include "../Rendering/3D/Triangle.h"
//#include "../Rendering/3D/Square.h"
//#include "../Rendering/3D/Cube.h"
#include "Renderer/Graphics/ShaderHandler.h"
#include "Renderer/Graphics/TextureHandler.h"
#include "Camera/Camera.h"
#include "Renderer/GameObject/GameObject.h"
#include "Framework/EventListener/EventListener.h"
#include "Renderer/Graphics/ParallaxBackground.h"
#include "GlobalElements/Audio/AudioHandler.h"
#include <reactPhysics/reactphysics3d.h>
#include <reactPhysics/collision/ContactManifold.h>
#include <reactPhysics/collision/CollisionCallback.h>
#include <reactPhysics/engine/ContactSolver.h>
#include <reactPhysics/constraint/ContactPoint.h>


#include <memory>

namespace ContinuumEngine3D {

	struct Color {

	public:

		// -------------------- Attributes -------------------- //

		// RGBA color components
		float r, g, b, a;

		// -------------------- Methods -------------------- //

		// Constructor
		Color() : r(1), g(1), b(1), a(1) {}

		// Constructor
		Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		// Copy-constructor
		Color(const Color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

		// Destructor
		~Color() {}

		// Return the black color
		static Color black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }

		// Return the white color
		static Color white() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }

		// Return the red color
		static Color red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }

		// Return the green color
		static Color green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }

		// Return the blue color
		static Color blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }

		// = operator
		Color& operator=(const Color& color) {
			if (&color != this) {
				r = color.r;
				g = color.g;
				b = color.b;
				a = color.a;
			}
			return *this;
		}
	};

	struct ContactPoint {

	public:
		rp3d::Vector3 point;
		rp3d::Vector3 normal;
		Color color;

		/// Constructor
		ContactPoint(const rp3d::Vector3& pointWorld, const rp3d::Vector3& normalWorld, const Color colorPoint)
			: point(pointWorld), normal(normalWorld), color(colorPoint) {

		}
	};

	// Contact manager
	class ContactManager : public rp3d::CollisionCallback {

	private:

		/// All the visual contact points
		std::vector<ContactPoint*> mContactPoints;

		/// Contact point mesh folder path
		std::string mMeshFolderPath;
	public:

		ContactManager() {

		}

		/// This method will be called for each reported contact point
		virtual void notifyContact(const CollisionCallbackInfo& collisionCallbackInfo) override;

		void resetPoints() {

			mContactPoints.clear();
		}

		std::vector<ContactPoint*> getContactPoints() const {
			return mContactPoints;
		}

		//control locking
		float k_ = 0.1f;
		float moveSpeed_ = 0.15f;


	};



	class ContinuumEngine {
	public:
		ContinuumEngine(const ContinuumEngine&) = delete;
		ContinuumEngine(ContinuumEngine&&) = delete;
		ContinuumEngine& operator=(const ContinuumEngine&) = delete;
		ContinuumEngine& operator=(ContinuumEngine&&) = delete;


		//Physics World
		rp3d::WorldSettings worldSettings;
		rp3d::CollisionWorld* world;
		ContactManager* mContactManager;
		rp3d::bodyindex collidingBody1 = 10000;
		rp3d::bodyindex collidingBody2 = 10000;

		void setCollidingBodies(rp3d::bodyindex index1_, rp3d::bodyindex index2_);

		bool Initialize(std::string name_, int width_, int height_, unsigned int flag_);
		void Run();
		bool GetIsRunning();
		void SetGameInterface(GameInterface* gameInterface_);

		static ContinuumEngine* GetInstance();
		glm::vec2 GetScreenSize() const;
		Timer timer;
		unsigned int hdrFBO;
		unsigned int colorBuffers[5];
		unsigned int rboDepth;
		//unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		unsigned int attachments[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4};
		unsigned int pingpongFBO[2];
		unsigned int pingpongColorbuffers[2];
		bool bloom = false;
		float exposure = 1.1f;

		glm::vec2 keyMap[15] = { glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f),
									glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), };

		void renderQuad();
		void renderFrame();

		float Randomize(float min_, float max_);


		void NotifyOfMousePressed(int x_, int y_);
		void NotifyOfMouseReleased(int x_, int y_, int buttonType_);
		void NotifyOfMouseMove(int x_, int y_);
		void NotifyOfMouseScroll(int y_);
		void NotifyOfKeyDown(SDL_Event e_);
		void NotifyOfKeyHold(SDL_Event e_);
		void NotifyOfKeyReleased(SDL_Event e_);
		void NotifyOfAxisEvents(SDL_Event e_);
		void NotifyOfButtonPressed(SDL_Event e_);
		void NotifyOfButtonReleased(SDL_Event e_);
		void NotifyOfControllerConnected(SDL_Event e_, int controllerIndex_);
		void NotifyOfControllerDisconnected(SDL_Event e_, int controllerIndex);

		glm::vec3 ConvertrpV3_to_glmV3(rp3d::Vector3 vector_);
		rp3d::Vector3 ConvertglmV3_to_rpV3(glm::vec3 vector_);
		GameInterface* gameInterface;

		Window* window;
		void ExitGame();
	private:
		ContinuumEngine();
		~ContinuumEngine();

		static std::unique_ptr<ContinuumEngine> engineInstance;
		friend std::default_delete<ContinuumEngine>;

		void Update(const float deltaTime_);
		void Render();
		void Shutdown();




		bool isRunning;
		unsigned int fps;
		std::vector<std::pair<SDL_GameController*, SDL_JoystickID>> gameControllers;
		int numGameControllers = 0;

		SDL_GameController* gGameController = NULL;

		SDL_GameController * controller;
		SDL_Joystick* joystick;
		SDL_JoystickID joyID;
		AudioHandler* audioHandler;

	};

}
#endif 