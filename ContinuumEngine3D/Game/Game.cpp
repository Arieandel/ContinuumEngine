#include "Game.h"

namespace ContinuumEngine3D {

	Game::Game()
	{
	}


	Game::~Game()
	{
		//delete model;
		//model = nullptr;

		//delete object1;
		//object1 = nullptr;
	}

	bool Game::Initialize() {
		////Setting Camera options and lights
		//Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 1.0f, 15.0f));
		//Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 8.0f), 0.1f, 0.9f, glm::vec3(1.0f, 1.0f, 1.0f))); //0.5,0.3
		//Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(-10.0f, -7.0f, -15.0f), 0.1f, 0.9f, glm::vec3(1.0f, 1.0f, 1.0f)));
		//Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(10.0f, -7.0f, -15.0f), 0.1f, 0.9f, glm::vec3(1.0f, 1.0f, 1.0f)));
		////initiating audio
		//audioHandler = new AudioHandler();

		////Creating Models
		//Land1 = new Model("../Resources/Models/Land1.obj", "../Resources/Materials/Land1.mtl", "ParallaxShader", false, true);
		//projectileModel = new Model("../Resources/Models/projectile.obj", "../Resources/Materials/projectile.mtl", "glowShader", true, false);
		//model = new Model("../Resources/Models/Aircraft_obj.obj", "../Resources/Materials/Aircraft_obj.mtl", "glowShader", false, false);
		//spawnerModel = new Model("../Resources/Models/spawner.obj", "../Resources/Materials/spawner.mtl", "glowShader", false, false);



		////Creating Objects  //v0.00: scaling objects breaks collision
		//Land1Obj = new GameObject(Land1);
		//Land1Obj->SetPosition(glm::vec3(0.0f, 0.0f, -30.0f));
		//Land1Obj->SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));
		//Land1Obj->SetAngle(3.14f);
		//Land1Obj->SetScale(glm::vec3(2.5f, 2.5f, 2.5f));
		//Land1Obj->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0001);
		//Land1Obj->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0009);

		//character = new GameObject(model);
		//character->SetPosition(glm::vec3(10.0f, -7.0f, -6.0f));
		//character->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0002);
		//character->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0003 | 0x0002);

		//character2 = new GameObject(model);
		//character2->SetPosition(glm::vec3(-10.0f, -7.0f, -6.0f));
		//character2->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0002);
		//character2->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0003 | 0x0002);


		//planetSpawner = new GameObject(spawnerModel);
		//planetSpawner->SetPosition(glm::vec3(0.0f, 0.0f, -40.0f));
		//planetSpawner->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0001);
		//planetSpawner->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0009);

		////Creating planet spawner
		//planetSpawnerObject = new PlanetSpawner(planetSpawner);
		//for (auto planet_models : planetSpawnerObject->planetModels) {
		//	models.push_back(planet_models);
		//}



		//models.push_back(model);
		//models.push_back(projectileModel);
		//models.push_back(Land1);
		//models.push_back(spawnerModel);

		//objects.push_back(Land1Obj);
		//objects.push_back(character);
		//objects.push_back(character2);

		//for (auto loadedModels : models) {

		//	if (!loadedModels) {
		//		return false;
		//	}
		//}



		//for (auto object : objects) {

		//	if (!object) {
		//		return false;
		//	}
		//}

		return true;
	}

	void Game::Update(const float deltaTime_) {
		////Setting Game parameters
		//audioHandler->PlayMusic("Background.wav");
		//k = ContinuumEngine::GetInstance()->mContactManager->k_;
		//moveSpeed = ContinuumEngine::GetInstance()->mContactManager->moveSpeed_;

		//moveObjects();
		//checkKeymap();
		//updateState();
	}

	void Game::Render() {

	/*	RenderMachine::GetInstance()->Render(models, delta);
		delta += 0.05f;*/

	}

	void Game::spawnPlanet() {
		//int randomNumber = (int)(ContinuumEngine::GetInstance()->Randomize(0.0f, 3.9f));
		//int randomX = (int)(ContinuumEngine::GetInstance()->Randomize(-10.0f, 10.0f));
		//int randomY = (int)(ContinuumEngine::GetInstance()->Randomize(-6.0f, 6.0f));
		////tempPlanet = planetSpawnerObject->spawnPlanet(randomNumber, randomX, randomY);
		////objects.push_back(tempPlanet);

	}

	void Game::moveObjects() {
		/*Camera::GetInstance()->SetPosition(Camera::GetInstance()->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
		planetSpawner->SetPosition(planetSpawner->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
		Land1Obj->SetPosition(Land1Obj->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
		character->SetPosition(character->GetPosition() + glm::vec3(0.0f, 0.0f, -k));
		character2->SetPosition(character2->GetPosition() + glm::vec3(0.0f, 0.0f, -k));

		for (int i = 0; i < Camera::GetInstance()->GetLightSources().size(); i++) {
			Camera::GetInstance()->GetLightSources()[i]->SetPosition(Camera::GetInstance()->GetLightSources()[i]->GetPosition() + glm::vec3(0.0f, 0.0f, -k));

		}
		for (int i = 0; i < projectileList.size(); i++) {

			projectileList[i]->SetPosition(projectileList[i]->GetPosition() + glm::vec3(0.0f, 0.0f, -k * 2.0f));
		}*/
	}



	void Game::updateState() {

	/*	spawnTimer += 0.05;
		if (int(spawnTimer + 1.0f) % 9 == 0) {
			spawnTimer = 0.0f;
			spawnPlanet();
			std::cout << "planet spawned" << std::endl;
		}



		if (projectileAlive) {
			projectileShot += 0.05;
			if (int(projectileShot + 1.0f) % 9 == 0) {
				projectileAlive = false;
				projectileShot = 0.0f;
				std::cout << projectileAlive << std::endl;
			}
		}


		ContinuumEngine::GetInstance()->mContactManager->resetPoints();
		ContinuumEngine::GetInstance()->world->testCollision(ContinuumEngine::GetInstance()->mContactManager);*/

	}

	void Game::onCollision() {

	/*	for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->mBody->getId() == ContinuumEngine::GetInstance()->collidingBody1 || objects[i]->mBody->getId() == ContinuumEngine::GetInstance()->collidingBody2) {

				objects[i]->GetModel()->DeleteInstance(objects[i]->modelInstance);
				objects.erase(objects.begin() + i);

			}
		}
		for (int j = 0; j < projectileList.size(); j++) {
			if (projectileList[j]->mBody->getId() == ContinuumEngine::GetInstance()->collidingBody1 || projectileList[j]->mBody->getId() == ContinuumEngine::GetInstance()->collidingBody2) {
				projectileList.erase(projectileList.begin() + j);
			}
		}*/
	}


	void Game::checkKeymap() {


		//if (ContinuumEngine::GetInstance()->keyMap[0] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[0] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[0] == glm::vec2(1, 1)) {
		//	character->SetPosition(character->GetPosition() + glm::vec3(-moveSpeed, 0.0f, 0.0f));
		//	//Camera::GetInstance()->SetPosition(glm::vec3(character->GetPosition().x + 10.0f, Camera::GetInstance()->GetPosition().y, character->GetPosition().z + 25.0f));
		//	rp3d::Transform transform = character->getBody()->getTransform();
		//	rp3d::Vector3 position = transform.getPosition();
		//	rp3d::Quaternion orientation = transform.getOrientation();

		//}
		//if (ContinuumEngine::GetInstance()->keyMap[2] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[2] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[2] == glm::vec2(1, 1)) {
		//	character->SetPosition(character->GetPosition() + glm::vec3(moveSpeed, 0.0f, 0.0f));
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 4);
		//	//Camera::GetInstance()->SetPosition(glm::vec3(character->GetPosition().x + 10.0f, Camera::GetInstance()->GetPosition().y, character->GetPosition().z + 25.0f));
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[1] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[1] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[1] == glm::vec2(1, 1)) {
		//	character->SetPosition(character->GetPosition() + glm::vec3(0.0f, -moveSpeed, 0.0f));
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 3);
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[3] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[3] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[3] == glm::vec2(1, 1)) {
		//	character->SetPosition(character->GetPosition() + glm::vec3(0.0f, moveSpeed, 0.0f));
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 5);
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[6] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[6] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[6] == glm::vec2(1, 1)) {
		//	character->SetPosition(character->GetPosition() + glm::vec3(0.0f, 0.0f, -moveSpeed));
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 6);
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[7] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[7] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[7] == glm::vec2(1, 1)) {
		//	character->SetPosition(character->GetPosition() + glm::vec3(0.0f, 0.0f, moveSpeed));
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 7);
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[4] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[4] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[4] == glm::vec2(1, 1)) {
		//	character->SetAngle(character->GetAngle() + k * 0.1f);
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 8);
		//	ContinuumEngine::GetInstance()->mContactManager->k_ += 0.01f;
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[5] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[5] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[5] == glm::vec2(1, 1)) {
		//	character->SetAngle(character->GetAngle() - k * 0.1f);
		//	audioHandler->PlaySFX("EngineSound.wav", 0, 2);
		//	ContinuumEngine::GetInstance()->mContactManager->k_ += -0.01f;
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[10] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[10] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[10] == glm::vec2(1, 1)) {
		//	//Just play audio.
		//	audioHandler->PlaySFX("FireSound.wav", 0, 1);
		//}

		////Character 2
		//if (ContinuumEngine::GetInstance()->keyMap[11] == glm::vec2(1, 0))
		//{
		//	character2->SetPosition(character2->GetPosition() + glm::vec3(-0.05f, 0.0f, 0.0f));
		//	audioHandler->PlaySFX("EngineSound2.wav", 0, 10);
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[12] == glm::vec2(1, 0))
		//{
		//	character2->SetPosition(character2->GetPosition() + glm::vec3(0.05f, 0.0f, 0.0f));
		//	audioHandler->PlaySFX("EngineSound2.wav", 0, 11);
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[13] == glm::vec2(1, 0))
		//{
		//	character2->SetPosition(character2->GetPosition() + glm::vec3(0.0f, -0.05f, 0.0f));
		//	audioHandler->PlaySFX("EngineSound2.wav", 0, 12);
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[14] == glm::vec2(1, 0))
		//{
		//	character2->SetPosition(character2->GetPosition() + glm::vec3(0.0f, 0.05f, 0.0f));
		//	audioHandler->PlaySFX("EngineSound2.wav", 0, 13);
		//}
		//if (ContinuumEngine::GetInstance()->keyMap[9] == glm::vec2(1, 0) || ContinuumEngine::GetInstance()->keyMap[9] == glm::vec2(0, 1) || ContinuumEngine::GetInstance()->keyMap[9] == glm::vec2(1, 1)) {


		//	if (!projectileAlive) {
		//		projectileAlive = true;
		//		projectile = new GameObject(projectileModel);
		//		projectile->SetPosition(character->GetPosition() + glm::vec3(0.0f, 0.0f, -8.0f));
		//		projectile->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0004);
		//		projectile->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0003);
		//		projectileList.push_back(projectile);
		//		objects.push_back(projectile);

		//		std::cout << projectileAlive << std::endl;
		//	}

		//}

	}



	//std::couts
	//std::cout << character->GetBoundaryBox().minVert.x << " x " << character->GetBoundaryBox().minVert.y << " y " << character->GetBoundaryBox().minVert.z << " z " << std::endl;
	//std::cout << character->GetBoundaryBox().maxVert.x << " x " << character->GetBoundaryBox().maxVert.y << " y " << character->GetBoundaryBox().maxVert.z << " z " << std::endl;
	//std::cout << character->GetBoundaryBox().xyZ.x << " x " << character->GetBoundaryBox().xyZ.y << " y " << character->GetBoundaryBox().xyZ.z << " z " << std::endl;
	//std::cout << character->GetBoundaryBox().xYz.x << " x " << character->GetBoundaryBox().xYz.y << " y " << character->GetBoundaryBox().xYz.z << " z " << std::endl;
	//std::cout << character->GetBoundaryBox().Xyz.x << " x " << character->GetBoundaryBox().Xyz.y << " y " << character->GetBoundaryBox().Xyz.z << " z " << std::endl;
	//std::cout << character->GetBoundaryBox().xYZ.x << " x " << character->GetBoundaryBox().xYZ.y << " y " << character->GetBoundaryBox().xYZ.z << " z " << std::endl;
	//std::cout << character->GetBoundaryBox().XyZ.x << " x " << character->GetBoundaryBox().XyZ.y << " y " << character->GetBoundaryBox().XyZ.z << " z " << std::endl;
	//std::cout << character->GetBoundaryBox().XYz.x << " x " << character->GetBoundaryBox().XYz.y << " y " << character->GetBoundaryBox().XYz.z << " z " << std::endl;
	//std::cout << character->GetBoundaryBox().xSize << " xSize " << std::endl;
	//std::cout << character->GetBoundaryBox().ySize << " ySize " << std::endl;
	//std::cout << character->GetBoundaryBox().zSize << " zSize " << std::endl;


	//std::cout << "position: (" << position.x << " , " << position.y << " , " << position.z << "); " << std::endl;
	//std::cout << "orientation: (" << orientation.x << " , " << orientation.y << " , " << orientation.z << "); " << std::endl;


}