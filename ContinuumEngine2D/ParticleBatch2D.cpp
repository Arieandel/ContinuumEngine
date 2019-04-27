#include "ParticleBatch2D.h"

namespace ContinuumEngine2D {
	ParticleBatch2D::ParticleBatch2D() {}

	ParticleBatch2D::~ParticleBatch2D() {
		delete[] particles;
	}

	void ParticleBatch2D::init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> updateFunction) {
		this->maxParticles = maxParticles;
		this->particles = new Particle2D[maxParticles];
		this->decayRate = decayRate;
		this->texture = texture;
		this->updateFunction = updateFunction;
	}

	void ParticleBatch2D::update(float dTime) {
		for (int i = 0; i < maxParticles; ++i) {
			if (particles[i].life > 0.0f) {
				updateFunction(particles[i], dTime);
				particles[i].life -= decayRate * dTime;
			}
		}
	}

	void ParticleBatch2D::draw(SpriteBatch * spriteBatch) {
		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

		for (int i = 0; i < maxParticles; ++i) {
			auto& particle = particles[i];
			if (particle.life > 0.0f) {
				glm::vec4 destRect(particle.position.x, particle.position.y, particle.width, particle.width);
				spriteBatch->draw(destRect, uvRect, texture.id, 0.0f, particle.color);
			}
		}
	}

	int ParticleBatch2D::findFreeParticle() {
		for (int i = lastFreeParticle; i < maxParticles; ++i) {
			if (particles[i].life <= 0.0f) {
				lastFreeParticle = i;
				return i;
			}
		}
		for (int i = 0; i < lastFreeParticle; ++i) {
			if (particles[i].life <= 0.0f) {
				lastFreeParticle = i;
				return i;
			}
		}

		return 0;
	}

	void ParticleBatch2D::addParticle(const glm::vec2& position, const glm::vec2& velocity, const ColorRGB8& color, float width) {
		int particleIndex = findFreeParticle();
		auto& particle = particles[particleIndex];

		particle.life = 1.0f;
		particle.position = position;
		particle.velocity = velocity;
		particle.color = color;
		particle.width = width;
	}
}