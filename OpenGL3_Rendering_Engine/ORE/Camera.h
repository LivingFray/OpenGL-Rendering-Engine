#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace ORE {
	class Camera {
	public:
		Camera();
		~Camera();
		// Sets the postion of the camera
		void setPosition(const glm::vec3 pos);
		// Gets the position of the camera
		glm::vec3 getPosition() const;
		// Sets the orientation of the camera
		void setRotation(const glm::quat rot);
		// Gets the orientation of the camera
		glm::quat getRotation() const;
		// Sets the field of view of the camera
		void setFOV(float fov);
		// Gets the field of view of the camera
		float getFOV() const;
		// Sets whether the camera uses perspective or orthographic projection
		void setPerspective(bool perspective);
		// Gets whether the camera uses perspective projection
		bool getPerspective() const;
		// Sets the near clipping distance of the camera
		void setNear(float near);
		// Gets the near clipping distance of the camera
		float getNear() const;
		// Sets the far clipping distance of the camera
		void setFar(float near);
		// Gets the far clipping distance of the camera
		float getFar() const;
		// Sets the width of the camera
		void setWidth(float width);
		// Gets the width of the camera
		float getWidth() const;
		// Sets the width of the camera
		void setHeight(float height);
		// Gets the width of the camera
		float getHeight() const;
		// Gets the projection matrix associated with the camera
		glm::mat4 getProjection() const;
		// Gets the view matrix associated with the camera
		glm::mat4 getView() const;
	private:
		glm::vec3 pos;
		glm::quat rot;
		float fov;
		bool perspective;
		float near;
		float far;
		float width;
		float height;
		glm::mat4 proj;
		// Updates the projection matrix
		void updateProjection();
	};
}
