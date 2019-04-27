#include "ParticleEngine2D.h"

#include "ParticleBatch2D.h"
#include "SpriteBatch.h"

namespace ContinuumEngine2D{
	ParticleEngine2D::ParticleEngine2D() {}

	ParticleEngine2D::~ParticleEngine2D() {
		for (auto& batch : batches) {
			delete batch;
		}
	}

	void ParticleEngine2D::addParticleBatch(ParticleBatch2D* batch) {
		batches.push_back(batch);
	}

	void ParticleEngine2D::update(float dTime) {
		for (auto& batch : batches) {
			batch->update(dTime);
		}
	}

	void ParticleEngine2D::draw(SpriteBatch* spriteBatch) {
		for (auto& batch : batches) {
			spriteBatch->begin();

			batch->draw(spriteBatch);

			spriteBatch->end();
			spriteBatch->renderBatch();
		}
	}
}