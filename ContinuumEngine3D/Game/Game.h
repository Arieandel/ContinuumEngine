#ifndef GAME_H
#define GAME_H

#include "../Engine/Renderer/Graphics/RenderMachine.h"
#include <OpenGL/glm/gtx/string_cast.hpp>
#include "../Engine/Renderer/GameObject/PlanetSpawner.h"


namespace ContinuumEngine3D {

	class Game : public GameInterface
	{
	public:
		Game();
		virtual ~Game();

		virtual bool Initialize();
		virtual void Update(const float deltaTime_);
		virtual void Render();
		void moveObjects();
		void checkKeymap();
		void updateState();
		void spawnPlanet();
		virtual void onCollision();

		//float k = 0.1f;
		//float moveSpeed = 0.05f;
		//bool projectileAlive = false;
		//float projectileShot = 0.0f;
		//float delta = 0.0f;
		//float spawnTimer = 0.0f;
		//std::vector<GameObject*> objects;
		//PlanetSpawner* planetSpawnerObject;

	private:
		//Model * model;
		//Model * model1;
		//Model * model2;
		//Model * projectileModel;
		//Model * model5;
		//Model * Land1;
		//Model * spawnerModel;
		//std::vector<Model*> models;
		//GameObject* object1;
		//GameObject* object5;
		//GameObject* projectileObj;
		//GameObject* character;
		//GameObject* character2;
		//GameObject* Land1Obj;
		//GameObject* moon;
		//GameObject* smallSunObj;
		//GameObject* projectile;
		//GameObject* planetSpawner;
		//GameObject* tempPlanet;

		//std::vector<GameObject*> projectileList;


		//AudioHandler* audioHandler;

	};
}
#endif