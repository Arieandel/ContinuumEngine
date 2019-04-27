#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <OpenGL/glm/glm.hpp>


namespace ContinuumEngine3D {

	class LightSource
	{
	public:
		LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 lightColour_);
		~LightSource();


		glm::vec3 GetPosition() const;
		float GetAmbient() const;
		float GetDiffuse() const;
		glm::vec3 GetLightColour() const;

		void SetPosition(glm::vec3 position_);
		void SetAmbient(float ambient_);
		void SetDiffuse(float diffuse_);
		void SetLightColour(glm::vec3 lightColour_);

	private:
		glm::vec3 position;
		float ambient;
		float diffuse;
		glm::vec3 lightColour;
	};

}

#endif
