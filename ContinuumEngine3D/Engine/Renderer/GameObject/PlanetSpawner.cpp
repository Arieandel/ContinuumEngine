#include "PlanetSpawner.h"


namespace ContinuumEngine3D {

	PlanetSpawner::PlanetSpawner(ContinuumEngine3D::GameObject* planetSpawner_)
	{

		spawner = planetSpawner_;
		spawner->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0001);
		spawner->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0009);

		moon = new ContinuumEngine3D::Model("../Resources/Models/sparkly.obj", "../Resources/Materials/sparkly.mtl", "glowShader", true, false); //glowShader
		artemis = new ContinuumEngine3D::Model("../Resources/Models/pinky.obj", "../Resources/Materials/pinky.mtl", "glowShader", true, false); //glowShader
		smallSun = new ContinuumEngine3D::Model("../Resources/Models/smallSun.obj", "../Resources/Materials/smallSun.mtl", "glowShader", true, false); //glowShader
		sun = new ContinuumEngine3D::Model("../Resources/Models/sun.obj", "../Resources/Materials/sun.mtl", "glowShader", true, false); //glowShader
		planetModels.push_back(moon);
		planetModels.push_back(artemis);
		planetModels.push_back(smallSun);
		planetModels.push_back(sun);


		ContinuumEngine3D::GameObject* sunObj = new ContinuumEngine3D::GameObject(sun);
		sunObj->SetPosition(spawner->GetPosition() + glm::vec3(0, 0, 100.0f));
		sunObj->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0003);
		sunObj->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0002 | 0x0004);
		planetsObjs.push_back(sunObj);


	}


	PlanetSpawner::~PlanetSpawner()
	{
		delete spawner;
		spawner = nullptr;
		delete smallSun;
		smallSun = nullptr;
		delete moon;
		moon = nullptr;
		delete artemis;
		artemis = nullptr;
		for (auto m : planetsObjs) {
			delete m;
			m = nullptr;
		}
		for (auto m : planetModels) {
			delete m;
			m = nullptr;
		}
		planetsObjs.clear();
		planetModels.clear();
		planetsObjs.shrink_to_fit();
		planetModels.shrink_to_fit();
	}


	void PlanetSpawner::spawnPlanet(int planetIndex_, float x_, float y_) {



		if (planetIndex_ == 1) {
			ContinuumEngine3D::GameObject* smallSunObj = new ContinuumEngine3D::GameObject(smallSun);
			smallSunObj->SetPosition(spawner->GetPosition() + glm::vec3(x_, y_, -10.0f));
			smallSunObj->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0003);
			smallSunObj->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0002 | 0x0004);
			planetsObjs.push_back(smallSunObj);

		}
		else if (planetIndex_ == 2) {
			ContinuumEngine3D::GameObject* moonObj = new ContinuumEngine3D::GameObject(moon);
			moonObj->SetPosition(spawner->GetPosition() + glm::vec3(x_, y_, -10.0f));
			moonObj->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0003);
			moonObj->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0002 | 0x0004);
			planetsObjs.push_back(moonObj);

		}
		else  {
			ContinuumEngine3D::GameObject* artemisObj = new ContinuumEngine3D::GameObject(artemis);
			artemisObj->SetPosition(spawner->GetPosition() + glm::vec3(x_, y_, -10.0f));
			artemisObj->getBody()->getProxyShapesList()[0].setCollisionCategoryBits(0x0003);
			artemisObj->getBody()->getProxyShapesList()[0].setCollideWithMaskBits(0x0002 | 0x0004);
			planetsObjs.push_back(artemisObj);

		}


	}

}