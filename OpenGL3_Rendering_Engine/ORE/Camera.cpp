#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace ORE {
	Camera::Camera() {
		fov = glm::pi<float>() / 3.0f;
		perspective = true;
		near = 0.1f;
		far = 100.0f;
		width = 1.0f;
		height = 1.0f;
		pos = glm::vec3(0.0f);
		rot = glm::quat();
		proj = glm::perspective(fov, width / height, near, far);
	}


	Camera::~Camera() {
	}


	// Gets the projection matrix associated with the camera
	glm::mat4 Camera::getProjection() const {
		return proj;
	}


	// Gets the view matrix associated with the camera
	glm::mat4 Camera::getView() const {
		glm::mat4 view = glm::translate(glm::mat4(1.0f), -pos);
		view = glm::toMat4(rot) * view;
		return view;
	}


	// Updates the projection matrix
	void Camera::updateProjection() {
		if (perspective) {
			proj = glm::perspective(fov, width / height, near, far);
		} else {
			proj = glm::ortho(-width / 2, -height / 2, width / 2, height / 2);
		}
	}


	// Sets the postion of the camera
	void Camera::setPosition(const glm::vec3 pos) {
		this->pos = pos;
	}


	// Gets the position of the camera
	glm::vec3 Camera::getPosition() const {
		return pos;
	}


	// Sets the postion of the camera
	void Camera::setRotation(const glm::quat rot) {
		this->rot = rot;
	}


	// Gets the position of the camera
	glm::quat Camera::getRotation() const {
		return rot;
	}


	// Sets the field of view of the camera
	void Camera::setFOV(float fov) {
		if (fov > 0 && fov < glm::pi<float>() * 2.0f) {
			this->fov = fov;
			updateProjection();
		}
	}


	// Gets the field of view of the camera
	float Camera::getFOV() const {
		return fov;
	}


	// Sets whether the camera uses perspective or orthographic projection
	void Camera::setPerspective(bool perspective) {
		this->perspective = perspective;
		updateProjection();
	}


	// Gets whether the camera uses perspective projection
	bool Camera::getPerspective() const {
		return perspective;
	}


	// Sets the near clipping distance of the camera
	void Camera::setNear(float near) {
		this->near = near;
		updateProjection();
	}


	// Gets the near clipping distance of the camera
	float Camera::getNear() const {
		return near;
	}


	// Sets the far clipping distance of the camera
	void Camera::setFar(float far) {
		this->far = far;
		updateProjection();
	}


	// Gets the far clipping distance of the camera
	float Camera::getFar() const {
		return far;
	}


	// Sets the width of the camera
	void Camera::setWidth(float width) {
		if (width > 0) {
			this->width = width;
			updateProjection();
		}
	}


	// Gets the width of the camera
	float Camera::getWidth() const {
		return width;
	}


	// Sets the width of the camera
	void Camera::setHeight(float height) {
		if (height > 0) {
			this->height = height;
			updateProjection();
		}
	}


	// Gets the width of the camera
	float Camera::getHeight() const {
		return height;
	}
}
