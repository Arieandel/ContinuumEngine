#pragma once

#include <functional>

#include <OpenGL/glm/glm.hpp>

#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"

namespace ContinuumEngine2D {
	class Particle2D {
	public:
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);
		ColorRGB8 color;
		float life = 0.0f;
		float width = 0.0f;
	};

	inline void defaultParticleUpdate(Particle2D& particle, float dTime) {
		particle.position += particle.velocity * dTime;
	}

	class ParticleBatch2D {
	public:
		ParticleBatch2D();
		~ParticleBatch2D();

		void init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> updateFunction = defaultParticleUpdate);
		void update(float dTime);
		void draw(SpriteBatch * spriteBatch);
		void addParticle(const glm::vec2& position, const glm::vec2& velocity, const ColorRGB8& color, float width);

	private:
		int findFreeParticle();

		float decayRate = 0.1f;
		Particle2D* particles = nullptr;
		int maxParticles = 0;
		int lastFreeParticle = 0;
		GLTexture texture;
		std::function<void(Particle2D&, float)> updateFunction;
	};
}