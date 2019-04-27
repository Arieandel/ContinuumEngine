#ifndef PLANETSPAWNER_H
#define PLANETSPAWNER_H

#include "GameObject.h"


namespace ContinuumEngine3D {

	class PlanetSpawner
	{
	public:
		ContinuumEngine3D::GameObject* spawner;

		ContinuumEngine3D::Model * smallSun;
		ContinuumEngine3D::Model * moon;
		ContinuumEngine3D::Model * artemis;
		ContinuumEngine3D::Model * sun;

		std::vector<ContinuumEngine3D::GameObject*> planetsObjs;
		std::vector<ContinuumEngine3D::Model *>planetModels;
		PlanetSpawner(ContinuumEngine3D::GameObject* planetSpawner_);
		void spawnPlanet(int planetIndex_, float x_, float y_);
		~PlanetSpawner();
	};


}
#endif