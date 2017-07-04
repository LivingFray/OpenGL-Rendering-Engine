#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
namespace ORE {
	class Transformable {
	public:
		Transformable();
		virtual ~Transformable();
		// Sets the position of the transformable
		void setPosition(glm::vec3 pos);
		// Gets the position of the transformable
		glm::vec3 getPosition() const;
		// Sets the rotation of the transformable
		void setRotation(glm::quat rot);
		// Gets the rotation of the transformable
		glm::quat getRotation() const;
		// Sets the scale of the transformable
		void setScale(glm::vec3 scale);
		// Gets the scale of the transformable
		glm::vec3 getScale() const;
		// Sets the parent of the transformable
		void setParent(Transformable* p);
		// Sets the parent of the transformable
		Transformable* getParent() const;
		// Gets the local transformation matrix
		glm::mat4 getLocalMatrix() const;
		// Gets the global transformation matrix
		glm::mat4 getGlobalMatrix() const;
	protected:
		glm::vec3 pos;
		glm::quat rot;
		glm::vec3 scale;
		glm::mat4 matrix;
		Transformable* parent;
	private:
		void recalcMatrix();
	};
}
