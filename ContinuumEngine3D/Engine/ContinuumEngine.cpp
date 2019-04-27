#include "ContinuumEngine.h"
namespace ContinuumEngine3D {

	std::unique_ptr<ContinuumEngine> ContinuumEngine::engineInstance = nullptr;


	void ContactManager::notifyContact(const CollisionCallbackInfo& collisionCallbackInfo) {

		// For each contact manifold
		rp3d::ContactManifoldListElement* manifoldElement = collisionCallbackInfo.contactManifoldElements;
		while (manifoldElement != nullptr) {

			// Get the contact manifold
			rp3d::ContactManifold* contactManifold = manifoldElement->getContactManifold();

			// For each contact point
			rp3d::ContactPoint* contactPoint = contactManifold->getContactPoints();
			while (contactPoint != nullptr) {

				// Contact normal
				rp3d::Vector3 normal = contactPoint->getNormal();
				//openglframework::Vector3 contactNormal(normal.x, normal.y, normal.z);

				rp3d::Vector3 point1 = contactPoint->getLocalPointOnShape1();
				point1 = collisionCallbackInfo.proxyShape1->getLocalToWorldTransform() * point1;

				//openglframework::Vector3 position1(point1.x, point1.y, point1.z);
				mContactPoints.push_back(&ContactPoint(point1, normal, Color::red()));

				rp3d::Vector3 point2 = contactPoint->getLocalPointOnShape2();
				point2 = collisionCallbackInfo.proxyShape2->getLocalToWorldTransform() * point2;
				//openglframework::Vector3 position2(point2.x, point2.y, point2.z);
				mContactPoints.push_back(&ContactPoint(point2, normal, Color::blue()));
				//std::cout << "collision!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
				//k_ = 0.0f;
				//moveSpeed_ = 0.0f;
				contactPoint = contactPoint->getNext();
			}

			ContinuumEngine::GetInstance()->setCollidingBodies(manifoldElement->getContactManifold()->getBody1()->getId(), manifoldElement->getContactManifold()->getBody2()->getId());
			//std::cout << ContinuumEngine::GetInstance()->collidingBody1 << std::endl;
			//std::cout << ContinuumEngine::GetInstance()->collidingBody2 << std::endl;
			manifoldElement = manifoldElement->getNext();
			if (ContinuumEngine::GetInstance()->gameInterface) {
				ContinuumEngine::GetInstance()->gameInterface->onCollision();

			}
		}
	}



	ContinuumEngine::ContinuumEngine() : window(nullptr), isRunning(false), fps(60) {
	}


	ContinuumEngine::~ContinuumEngine() {
		Shutdown();
	}

	ContinuumEngine* ContinuumEngine::GetInstance() {
		if (engineInstance.get() == nullptr) {
			engineInstance.reset(new ContinuumEngine);
		}
		return engineInstance.get();
	}

	bool ContinuumEngine::Initialize(std::string name_, int width_, int height_, unsigned int flag_) {
		Debug::DebugInit();
		Debug::SetSeverity(MessageType::TYPE_INFO);

		window = new Window();

		if (!window->Initialize(name_, width_, height_, flag_)) {
			Debug::FatalError("Window failed to initialize", __FILE__, __LINE__);
			//Shutdown();
			return isRunning = false;
		}

		SDL_Init(SDL_INIT_GAMECONTROLLER);
		SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
		MouseEventListener::RegisterEngineObject(this);
		KeyboardEventListener::RegisterEngineObject(this);
		GameControllerListener::RegisterEngineObject(this);
		//"colourShader"
		ShaderHandler::GetInstance()->CreateProgram("colourShader", "../Resources/Shaders/ColourVertexShader.glsl", "../Resources/Shaders/ColourFragmentShader.glsl");
		//"baseShader"
		ShaderHandler::GetInstance()->CreateProgram("baseShader", "../Resources/Shaders/VertexShader.glsl", "../Resources/Shaders/FragmentShader.glsl");
		//"cubeShader"											   
		ShaderHandler::GetInstance()->CreateProgram("cubeShader", "../Resources/Shaders/cubeVertexShader.glsl", "../Resources/Shaders/cubeFragmentShader.glsl");
		//"quadShader"											   
		ShaderHandler::GetInstance()->CreateProgram("quadShader", "../Resources/Shaders/quadVertexShader.glsl", "../Resources/Shaders/quadFragmentShader.glsl");
		//"frameShader"
		ShaderHandler::GetInstance()->CreateProgram("frameShader", "../Resources/Shaders/FrameVertexShader.glsl", "../Resources/Shaders/FrameFragmentShader.glsl");

		//Shaders for glow("glowShader")
		ShaderHandler::GetInstance()->CreateProgram("bloomShader", "../Resources/Shaders/VertexShader.glsl", "../Resources/Shaders/BloomFragmentShader.glsl");
		ShaderHandler::GetInstance()->CreateProgram("bloomLightShader", "../Resources/Shaders/VertexShader.glsl", "../Resources/Shaders/BloomLightFragmanetShader.glsl");
		ShaderHandler::GetInstance()->CreateProgram("blurShader", "../Resources/Shaders/BlurVertexShader.glsl", "../Resources/Shaders/BlurFragmentShader.glsl");
		ShaderHandler::GetInstance()->CreateProgram("bloomFinalShader", "../Resources/Shaders/BlurVertexShader.glsl", "../Resources/Shaders/BloomFinalFragmentShader.glsl");

		//"SkyboxShader"
		ShaderHandler::GetInstance()->CreateProgram("SkyboxShader", "../Resources/Shaders/SkyboxVertexShader.glsl", "../Resources/Shaders/SkyboxFragmentShader.glsl");

		//"ParallaxShader"
		ShaderHandler::GetInstance()->CreateProgram("ParallaxShader", "../Resources/Shaders/VertexShader.glsl", "../Resources/Shaders/ParallaxFragmentShader.glsl");





		glEnable(GL_DEPTH_TEST);


		glGenFramebuffers(1, &hdrFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
		// create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values)

		glGenTextures(5, colorBuffers);
		for (unsigned int i = 0; i < 5; i++)
		{
			glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width_, height_, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			// attach texture to framebuffer
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
		}


		// create and attach depth buffer (renderbuffer)
		glGenRenderbuffers(1, &rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
		// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 

		glDrawBuffers(5, attachments);
		// finally check if framebuffer is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);





		// ping-pong-framebuffer for blurring

		glGenFramebuffers(2, pingpongFBO);
		glGenTextures(2, pingpongColorbuffers);
		for (unsigned int i = 0; i < 2; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
			glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width_, height_, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
			// also check if framebuffers are complete (no need for depth buffer)
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "Framebuffer not complete!" << std::endl;
		}


		glUseProgram(ShaderHandler::GetInstance()->GetShader("baseShader"));
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("baseShader"), "inputTexture"), 0);
		glUseProgram(ShaderHandler::GetInstance()->GetShader("ParallaxShader"));
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("ParallaxShader"), "ParallaxTexture"), 2);
		glUseProgram(ShaderHandler::GetInstance()->GetShader("frameShader"));
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("frameShader"), "skybox"), 4);
		glUseProgram(ShaderHandler::GetInstance()->GetShader("frameShader"));
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("frameShader"), "sceneCube"), 3);
		glUseProgram(ShaderHandler::GetInstance()->GetShader("bloomShader"));
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("bloomShader"), "diffuseTexture"), 0);
		glUseProgram(ShaderHandler::GetInstance()->GetShader("blurShader"));
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("blurShader"), "image"), 0);
		glUseProgram(ShaderHandler::GetInstance()->GetShader("quadShader"));
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("quadShader"), "quadSample"), 2);
		glUseProgram(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"));
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"), "scene"), 0);
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"), "bloomBlur"), 1);
		glUniform1i(glGetUniformLocation(ShaderHandler::GetInstance()->GetShader("bloomFinalShader"), "Midnight"), 2);



		worldSettings.worldName = "ContinuumWorld";
		world = new rp3d::CollisionWorld(worldSettings);
		mContactManager = new ContactManager;

		if (gameInterface) {
			if (!gameInterface->Initialize()) {
				Debug::FatalError("GameInterface failed to initialize", __FILE__, __LINE__);
				return isRunning = false;
			}
		}


		Debug::Info("initied", __FILE__, __LINE__);
		timer.Start();
		return isRunning = true;
	}

	void ContinuumEngine::Run() {
		while (isRunning) {
			EventListener::Update();
			timer.UpdateFrameTicks();
			Update(timer.getDeltaTime());
			Render();
			SDL_Delay(timer.GetSleepTime(fps));
		}
		if (!isRunning) {
			Shutdown();
		}
	}

	bool ContinuumEngine::GetIsRunning() {
		return isRunning;
	}

	void ContinuumEngine::Update(const float deltaTime_) {
		if (gameInterface) {
			gameInterface->Update(deltaTime_);

		}
	}

	void ContinuumEngine::Render() {

		//glClearColor(0.160f, 0.048f, 0.320f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (gameInterface) {
			gameInterface->Render();
		}

		window->swapBuffer();
	}


	void ContinuumEngine::renderQuad()
	{
		unsigned int quadVAO = 0;//!up
		unsigned int quadVBO;
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &quadVAO);
		glDeleteBuffers(1, &quadVBO);
	}


	void ContinuumEngine::renderFrame()
	{
		unsigned int quadVAO = 0;//!up
		unsigned int quadVBO;
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				// positions   
				-1.0f,  1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				-1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f
			};
			// setup plane VAO

			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			//glGenVertexArrays(1, &quadVAO);
			//glGenBuffers(1, &quadVBO);
			//glBindVertexArray(quadVAO);
			//glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			//glEnableVertexAttribArray(0);
			//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
			//glEnableVertexAttribArray(1);
			//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		}

		glDepthFunc(GL_LEQUAL);
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		glDeleteVertexArrays(1, &quadVAO);
		glDeleteBuffers(1, &quadVBO);

		//glBindVertexArray(quadVAO);

		//glDrawArrays(GL_TRIANGLES, 0, 6);

		////glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//glBindVertexArray(0);
		//glDeleteVertexArrays(1, &quadVAO);
		//glDeleteBuffers(1, &quadVBO);
	}


	void ContinuumEngine::Shutdown() {

		delete window;
		window = nullptr;

		delete gameInterface;
		gameInterface = nullptr;

		delete world;
		world = nullptr;
		delete mContactManager;
		mContactManager = nullptr;
		delete gGameController;
		gGameController = nullptr;
		delete joystick;
		joystick = nullptr;

		delete audioHandler;
		audioHandler = nullptr;

		SDL_Quit();
		exit(0);
	}

	void ContinuumEngine::SetGameInterface(GameInterface* gameInterface_) {
		gameInterface = gameInterface_;
	}

	glm::vec2 ContinuumEngine::GetScreenSize() const {
		return glm::vec2(window->GetWidth(), window->GetHeight());
	}


	void ContinuumEngine::NotifyOfMousePressed(int x_, int y_) {
		bloom = true;
	}
	void ContinuumEngine::NotifyOfMouseReleased(int x_, int y_, int buttonType_) {
		bloom = false;
	}
	void ContinuumEngine::NotifyOfMouseMove(int x_, int y_) {
		if (bloom)
			Camera::GetInstance()->ProcessMouseMovement(MouseEventListener::GetMouseOffset().x, MouseEventListener::GetMouseOffset().y);

	}
	void ContinuumEngine::NotifyOfMouseScroll(int y_) {
		Camera::GetInstance()->ProcessMouseZoom(y_);
	}


	void ContinuumEngine::NotifyOfKeyDown(SDL_Event e_) {
		switch (e_.key.keysym.sym)
		{
		case SDLK_a:
			keyMap[0].x = 1;
			//printf("a key pressed ");
			break;
		case SDLK_s:
			keyMap[1].x = 1;
			//		printf("s key pressed ");
			break;
		case SDLK_d:
			keyMap[2].x = 1;
			//		printf("d key pressed ");
			break;
		case SDLK_w:
			keyMap[3].x = 1;
			//		printf("w key pressed ");
			break;
		case SDLK_q:
			keyMap[4].x = 1;
			//	printf("q key pressed ");
			break;
		case SDLK_e:
			keyMap[5].x = 1;
			//	printf("e key pressed ");
			break;
		case SDLK_z:
			keyMap[6].x = 1;
			//	printf("z key pressed ");
			break;
		case SDLK_x:
			keyMap[7].x = 1;
			//	printf("x key pressed ");
			break;
		case SDLK_ESCAPE:
			keyMap[8].x = 1;
			ExitGame();
			break;
		case SDLK_SPACE:
			keyMap[9].x = 1;
			//printf("Space key pressed ");
			break;
		case SDLK_c:
			keyMap[10].x = 1;
			//printf("c key pressed ");
			break;
		}
	}
	void ContinuumEngine::NotifyOfKeyHold(SDL_Event e_) {
		switch (e_.key.keysym.sym)
		{
		case SDLK_a:
			keyMap[0].y = 1;
			//	printf("a is being held down ");
			break;
		case SDLK_s:
			keyMap[1].y = 1;
			//	printf("s is being held down ");
			break;
		case SDLK_d:
			keyMap[2].y = 1;
			//	printf("d is being held down ");
			break;
		case SDLK_w:
			keyMap[3].y = 1;
			//	printf("w is being held down ");
			break;
		case SDLK_q:
			keyMap[4].y = 1;
			//	printf("q is being held down ");
			break;
		case SDLK_e:
			keyMap[5].y = 1;
			//	printf("e is being held down ");
			break;
		case SDLK_z:
			keyMap[6].y = 1;
			//	printf("z is being held down ");
			break;
		case SDLK_x:
			keyMap[7].y = 1;
			//	printf("x is being held down ");
			break;
		case SDLK_SPACE:
			keyMap[9].y = 1;
			//printf("Space is being held down ");
			break;
		case SDLK_c:
			keyMap[10].y = 1;
			//printf("c key pressed ");
			break;
		}
	}
	void ContinuumEngine::NotifyOfKeyReleased(SDL_Event e_) {
		switch (e_.key.keysym.sym)
		{
		case SDLK_a:
			keyMap[0].x = 0;
			keyMap[0].y = 0;
			//		printf("a has been released ");
			break;
		case SDLK_s:
			keyMap[1].x = 0;
			keyMap[1].y = 0;
			//		printf("s has been released ");
			break;
		case SDLK_d:
			keyMap[2].x = 0;
			keyMap[2].y = 0;
			//		printf("d has been released ");
			break;
		case SDLK_w:
			keyMap[3].x = 0;
			keyMap[3].y = 0;
			//		printf("w has been released ");
			break;
		case SDLK_q:
			keyMap[4].x = 0;
			keyMap[4].y = 0;
			//		printf("q has been released ");
			break;
		case SDLK_e:
			keyMap[5].x = 0;
			keyMap[5].y = 0;
			//		printf("e has been released ");
			break;
		case SDLK_z:
			keyMap[6].x = 0;
			keyMap[6].y = 0;
			//		printf("z has been released ");
			break;
		case SDLK_x:
			keyMap[7].x = 0;
			keyMap[7].y = 0;
			//		printf("x has been released ");
			break;
		case SDLK_SPACE:
			keyMap[9].x = 0;
			keyMap[9].y = 0;
			//		printf("Space has been released ");
			break;
		case SDLK_c:
			keyMap[10].x = 0;
			keyMap[10].y = 0;
			//		printf("c has been released");
			break;
		}
	}

	void ContinuumEngine::NotifyOfAxisEvents(SDL_Event e_)
	{
		if (e_.caxis.which == 0) //Controller 0
		{
			switch (e_.caxis.axis)
			{
			case SDL_CONTROLLER_AXIS_LEFTX:
				//printf("This is x axis on left stick\n");
				if ((e_.caxis.value > -8000) && (e_.caxis.value < 8000)) {
					keyMap[0].x = 0;
					keyMap[2].x = 0;
				}
				else { // Or not
					if (e_.caxis.value < 0) //Moving to the left
					{
						//printf("Moving to the left.\n");
						keyMap[0].x = 1;
						//printf("a key pressed ");
					}
					else {				    // Moving to the right
						//printf("Moving to the right.\n");
						keyMap[2].x = 1;
					}
				}
				break;
			case SDL_CONTROLLER_AXIS_LEFTY:
				//printf("This is y axis on left stick\n");
				if ((e_.caxis.value > -8000) && (e_.caxis.value < 8000)) {
					keyMap[3].x = 0;
					keyMap[1].x = 0;
				}
				else { // Or not
					if (e_.caxis.value < 0)
					{
						//printf("Moving up.\n");
						keyMap[3].x = 1;
					}
					else {
						//printf("Moving down.\n");
						keyMap[1].x = 1;
					}
				}
				break;
			case SDL_CONTROLLER_AXIS_RIGHTX:
				if ((e_.caxis.value > -8000) && (e_.caxis.value < 8000)) {

				}
				else { // Or not
					if (e_.caxis.value < 0)
					{
						//printf("Right stick to the left\n");
					}
					else {
						//printf("Right stick to the right\n");
					}
				}
				break;
			case SDL_CONTROLLER_AXIS_RIGHTY:
				if ((e_.caxis.value > -8000) && (e_.caxis.value < 8000)) {

				}
				else { // Or not
					if (e_.caxis.value < 0)
					{
						//printf("Right stick to the up\n");
					}
					else {
						//printf("Right stick to the down\n");
					}
				}
				break;
			}  // Possible to calculate the angle of the analog: http://lazyfoo.net/tutorials/SDL/19_gamepads_and_joysticks/index.php
		}
		else if (e_.caxis.which == 1) {
			switch (e_.caxis.axis)
			{
			case SDL_CONTROLLER_AXIS_LEFTX:
				//printf("This is x axis on left stick\n");
				if ((e_.caxis.value > -8000) && (e_.caxis.value < 8000)) {
					keyMap[11].x = 0;
					keyMap[12].x = 0;
				}
				else { // Or not
					if (e_.caxis.value < 0) //Moving to the left
					{
						//printf("Moving to the left.\n");
						keyMap[11].x = 1;
						//printf("a key pressed ");
					}
					else {				    // Moving to the right
					//	printf("Moving to the right.\n");
						keyMap[12].x = 1;
					}
				}
				break;
			case SDL_CONTROLLER_AXIS_LEFTY:
				//printf("This is y axis on left stick\n");
				if ((e_.caxis.value > -8000) && (e_.caxis.value < 8000)) {
					keyMap[13].x = 0;
					keyMap[14].x = 0;
				}
				else { // Or not
					if (e_.caxis.value < 0)
					{
						//printf("Moving up.\n");
						keyMap[3].x = 1;
					}
					else {
						//printf("Moving down.\n");
						keyMap[1].x = 1;
					}
				}
				break;
			case SDL_CONTROLLER_AXIS_RIGHTX:
				if ((e_.caxis.value > -8000) && (e_.caxis.value < 8000)) {

				}
				else { // Or not
					if (e_.caxis.value < 0)
					{
						//printf("Right stick to the left\n");
					}
					else {
						//printf("Right stick to the right\n");
					}
				}
				break;
			case SDL_CONTROLLER_AXIS_RIGHTY:
				if ((e_.caxis.value > -8000) && (e_.caxis.value < 8000)) {

				}
				else { // Or not
					if (e_.caxis.value < 0)
					{
						//printf("Right stick to the up\n");
					}
					else {
						//printf("Right stick to the down\n");
					}
				}
				break;
			}  // Possible to calculate the angle of the analog: http://lazyfoo.net/tutorials/SDL/19_gamepads_and_joysticks/index.php
		}
	}

	void ContinuumEngine::NotifyOfButtonPressed(SDL_Event e_)
	{
		switch (e_.cbutton.button) {
		case SDL_CONTROLLER_BUTTON_A:
			//printf("Button A is being pressed\n");
			keyMap[9].x = 1;
			keyMap[9].y = 1;
			break;
		case SDL_CONTROLLER_BUTTON_B:
			//printf("Button B is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_X:
			//printf("Button X is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			//printf("Button Y is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_START:
			//printf("Button Start is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			//("Button Left Shoulder is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			//printf("Button Right Shoulder is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSTICK:
			//printf("Button Left Stick is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
			//printf("Button Right Stick is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			//printf("D-Pad Up is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			//printf("D-Pad Down is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			//printf("D-Pad Left is being pressed\n");
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			//printf("D-Pad Right is being pressed\n");
			break;
		}
	}

	void ContinuumEngine::NotifyOfButtonReleased(SDL_Event e_)
	{
		switch (e_.cbutton.button) {
		case SDL_CONTROLLER_BUTTON_A:
			//printf("Button A has just been released\n");
			keyMap[9].x = 0;
			keyMap[9].y = 0;
			break;
		case SDL_CONTROLLER_BUTTON_B:
			//printf("Button B has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_X:
			//printf("Button X has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			//printf("Button Y has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_START:
			//printf("Button Start has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			//printf("Button Left Shoulder has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			//printf("Button Left Shoulder has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSTICK:
			//printf("Button Left Stick has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
			//printf("Button Right Stick has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			//printf("D-Pad Up has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			//printf("D-Pad Up has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			//printf("D-Pad Left has just been released\n");
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			//printf("D-Pad Right has just been released\n");
			break;
		}
	}

	void ContinuumEngine::NotifyOfControllerConnected(SDL_Event e_, int controllerIndex_)
	{
		switch (e_.type) {

		case SDL_CONTROLLERDEVICEADDED:

			std::cout << "Number of game controllers: " << SDL_NumJoysticks() << std::endl;

			for (int i = numGameControllers; i < SDL_NumJoysticks(); i++) {
				if (SDL_IsGameController(i))
				{
					printf("Index \'%i\' is a compatible controller, named \'%s\'\n", i, SDL_GameControllerNameForIndex(i));
					//gGameController = SDL_GameControllerOpen(i);
					numGameControllers++;
					std::cout << "Number of game controllers: " << SDL_NumJoysticks() << std::endl;
				}
			}

			if (SDL_IsGameController(controllerIndex_)) {
				controller = SDL_GameControllerOpen(controllerIndex_);
				joystick = SDL_GameControllerGetJoystick(controller);
				joyID = SDL_JoystickInstanceID(joystick);

				if (numGameControllers > 0)
				{
					for (int i = numGameControllers; i <= numGameControllers; i++) {

						gGameController = SDL_GameControllerOpen(i - 1);
						if (SDL_GameControllerGetAttached(gGameController) == 1)
							gameControllers.emplace_back(gGameController, joyID);
						else
							printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
					}
					SDL_GameControllerEventState(SDL_ENABLE);
				}

				printf("Controller added");
			}

			for (int i = 0; i < gameControllers.size(); i++) {
				std::cout << "Amount of the controllers: " << gameControllers.size() << std::endl;
			}
			break;
		}
	}

	void ContinuumEngine::NotifyOfControllerDisconnected(SDL_Event e_, int controllerIndex_)
	{
		switch (e_.type) {

		case SDL_CONTROLLERDEVICEREMOVED:

			controller = SDL_GameControllerFromInstanceID(controllerIndex_);

			std::vector<std::pair<SDL_GameController*, SDL_JoystickID>>::iterator iter = gameControllers.begin();

			while (iter != gameControllers.end()) {
				if (iter->first == controller && iter->second == controllerIndex_) {
					//printf("Hi");
					iter = gameControllers.erase(iter);
				}
				else
					++iter;
			}

			SDL_GameControllerClose(controller);

			printf("check");
			//Will be implemented later/Trying to figure out the logic.

			break;
		}
	}

	float ContinuumEngine::Randomize(float min_, float max_) {

		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = max_ - min_;
		float r = random * diff;
		return min_ + r;
	}

	void ContinuumEngine::setCollidingBodies(rp3d::bodyindex index1_, rp3d::bodyindex index2_) {
		collidingBody1 = index1_;
		collidingBody2 = index2_;
	}


	glm::vec3 ContinuumEngine::ConvertrpV3_to_glmV3(rp3d::Vector3 vector_) {
		glm::vec3 tempVec;
		tempVec.x = vector_.x;
		tempVec.y = vector_.y;
		tempVec.z = vector_.z;
		return tempVec;
	}

	rp3d::Vector3 ContinuumEngine::ConvertglmV3_to_rpV3(glm::vec3 vector_) {
		rp3d::Vector3 tempVec;
		tempVec.x = vector_.x;
		tempVec.y = vector_.y;
		tempVec.z = vector_.z;
		return tempVec;
	}




	void ContinuumEngine::ExitGame() {
		isRunning = false;
	}

}