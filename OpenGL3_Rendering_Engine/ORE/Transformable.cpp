#include "Transformable.h"
#include <glm/gtc/matrix_transform.hpp>

namespace ORE {
	Transformable::Transformable() {
		parent = NULL;
		matrix = glm::mat4(1.0f);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}


	Transformable::~Transformable() {
	}


	// Sets the position of the transformable
	void Transformable::setPosition(glm::vec3 pos) {
		this->pos = pos;
		recalcMatrix();
	}


	// Gets the position of the transformable
	glm::vec3 Transformable::getPosition() const{
		return pos;
	}


	// Sets the rotation of the transformable
	void Transformable::setRotation(glm::quat rot) {
		this->rot = rot;
		recalcMatrix();
	}


	// Gets the rotation of the transformable
	glm::quat Transformable::getRotation() const {
		return rot;
	}


	// Sets the scale of the transformable
	void Transformable::setScale(glm::vec3 scale) {
		this->scale = scale;
		recalcMatrix();
	}


	// Gets the scale of the transformable
	glm::vec3 Transformable::getScale() const {
		return scale;
	}


	// Sets the parent of the transformable
	void Transformable::setParent(Transformable* p) {
		parent = p;
	}


	// Sets the parent of the transformable
	Transformable* Transformable::getParent() const {
		return parent;
	}


	// Gets the local transformation matrix
	glm::mat4 Transformable::getLocalMatrix() const {
		return matrix;
	}


	// Gets the global transformation matrix
	glm::mat4 Transformable::getGlobalMatrix() const {
		if (!parent) {
			return matrix;
		}
		return parent->getGlobalMatrix() * matrix;
	}


	void Transformable::recalcMatrix() {
		glm::mat4 m4_pos = glm::translate(glm::mat4(1.0f), pos);
		glm::mat4 m4_rot = glm::toMat4(rot);
		glm::mat4 m4_scale = glm::scale(glm::mat4(1.0f), scale);
		matrix = m4_scale * m4_rot * m4_pos;
	}
}
