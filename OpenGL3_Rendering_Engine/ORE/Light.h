#pragma once
#include "Transformable.h"
#include "Engine.h"
//TODO: Split into different classes?
namespace ORE {
	enum class LightType {DIRECTIONAL, POINT, SPOTLIGHT};
	class Light :
		public Transformable {
	public:
		Light();
		virtual ~Light();
		//Temp, will not work when more light sources are added
		void updateShader(GLuint program);
		void setType(LightType type);
		void setPosition(glm::vec3 position);
		void setDirection(glm::vec3 direction);
		void setAmbient(glm::vec3 ambient);
		void setDiffuse(glm::vec3 diffuse);
		void setSpecular(glm::vec3 specular);
		void setAttenuation(float constant, float linear, float quadratic);
		void setCutOff(float cosAngle);
		void setOuterCutOff(float cosAngle);
	private:
		LightType type;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;
		float cutOff;
		float outerCutOff;
	};
}
