#include "Light.h"

namespace ORE {
	Light::Light() {
	}


	Light::~Light() {
	}


	void Light::updateShader(GLuint program) {
		glUniform3fv(glGetUniformLocation(program, "light.ambient"), 1, &ambient[0]);
		glUniform3fv(glGetUniformLocation(program, "light.diffuse"), 1, &diffuse[0]);
		glUniform3fv(glGetUniformLocation(program, "light.specular"), 1, &specular[0]);
		if (type == LightType::DIRECTIONAL) {
			glUniform1i(glGetUniformLocation(program, "lightType"), 0);
			glUniform3fv(glGetUniformLocation(program, "dirLight.direction"), 1, &direction[0]);
		} else if (type == LightType::POINT) {
			glUniform1i(glGetUniformLocation(program, "lightType"), 1);
			glUniform3fv(glGetUniformLocation(program, "pointLight.position"), 1, &position[0]);
			glUniform1f(glGetUniformLocation(program, "pointLight.constant"), constant);
			glUniform1f(glGetUniformLocation(program, "pointLight.linear"), linear);
			glUniform1f(glGetUniformLocation(program, "pointLight.quadratic"), quadratic);

		} else if (type == LightType::SPOTLIGHT) {
			glUniform1i(glGetUniformLocation(program, "lightType"), 2);
			glUniform3fv(glGetUniformLocation(program, "spotLight.direction"), 1, &direction[0]);
			glUniform3fv(glGetUniformLocation(program, "spotLight.position"), 1, &position[0]);
			glUniform1f(glGetUniformLocation(program, "spotLight.constant"), constant);
			glUniform1f(glGetUniformLocation(program, "spotLight.linear"), linear);
			glUniform1f(glGetUniformLocation(program, "spotLight.quadratic"), quadratic);
			glUniform1f(glGetUniformLocation(program, "spotLight.cutOff"), cutOff);
			glUniform1f(glGetUniformLocation(program, "spotLight.outerCutOff"), outerCutOff);
		}
	}

	void Light::setType(LightType type) {
		this->type = type;
	}


	void Light::setPosition(glm::vec3 position) {
		this->position = position;
	}


	void Light::setDirection(glm::vec3 direction) {
		this->direction = direction;
	}


	void Light::setAmbient(glm::vec3 ambient) {
		this->ambient = ambient;
	}


	void Light::setDiffuse(glm::vec3 diffuse) {
		this->diffuse = diffuse;
	}


	void Light::setSpecular(glm::vec3 specular) {
		this->specular = specular;
	}


	void Light::setAttenuation(float constant, float linear, float quadratic) {
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}


	void Light::setCutOff(float cosAngle) {
		cutOff = cosAngle;
	}


	void Light::setOuterCutOff(float cosAngle) {
		outerCutOff = cosAngle;
	}
}
