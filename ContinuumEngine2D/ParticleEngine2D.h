#pragma once

#include <vector>

namespace ContinuumEngine2D {
	class ParticleBatch2D;
	class SpriteBatch;

	class ParticleEngine2D {
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		void addParticleBatch(ParticleBatch2D* batch);
		void update(float dTime);
		void draw(SpriteBatch* spriteBatch);

	private:
		std::vector<ParticleBatch2D*> batches;
	};
}