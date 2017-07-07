#include "../ORE/World.h"
#include "../ORE/Engine.h"
#include "../ORE/SimpleVAO.h"
#include <glm/gtc/matrix_transform.hpp>
//TODO: ADD Callbacks

double pitch, yaw;

void moveCamera(ORE::Camera* c, double t) {
	double sensitivity = 0.05f;
	//Calculate orientation
	int w, h;
	glfwGetWindowSize(ORE::window, &w, &h);
	double mx, my;
	glfwGetCursorPos(ORE::window, &mx, &my);
	double dx, dy;
	dx = mx - (w / 2.0);
	dy = my - (h / 2.0);
	glfwSetCursorPos(ORE::window, w / 2.0, h / 2.0);
	yaw += dx * sensitivity;
	pitch += dy * sensitivity;
	if (pitch > 89.9f) {
		pitch = 89.9f;
	}
	if (pitch < -89.9f) {
		pitch = -89.9f;
	}
	glm::vec3 front, right, up;
	front.x = static_cast<float>(cos(glm::radians(pitch)) * cos(glm::radians(yaw)));
	front.y = static_cast<float>(sin(glm::radians(pitch)));
	front.z = static_cast<float>(cos(glm::radians(pitch)) * sin(glm::radians(yaw)));
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0)));
	up = glm::normalize(glm::cross(right, front));
	c->setRotation(glm::quat(glm::vec3(0,glm::pi<float>(), 0)) * glm::toQuat(glm::lookAt(c->getPosition(), c->getPosition() + front, up)));
	//Calculate movement
	glm::vec3 pos = c->getPosition();
	float cameraSpeed = 5.0f * static_cast<float>(t); // adjust accordingly
	if (glfwGetKey(ORE::window, GLFW_KEY_W) == GLFW_PRESS) {
		pos += cameraSpeed * front;
	}
	if (glfwGetKey(ORE::window, GLFW_KEY_S) == GLFW_PRESS) {
		pos -= cameraSpeed * front;
	}
	if (glfwGetKey(ORE::window, GLFW_KEY_A) == GLFW_PRESS) {
		pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
	}
	if (glfwGetKey(ORE::window, GLFW_KEY_D) == GLFW_PRESS) {
		pos += glm::normalize(glm::cross(front, up)) * cameraSpeed;
	}
	c->setPosition(pos);
}

//Shamelessly lifted from learnopengl.com
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

int main() {
	ORE::init(1024, 768);
	ORE::World world;
	ORE::Camera* cam = world.getCamera();
	ORE::SimpleVAO testVAO(ORE::loadImage("Testing/tmp.png"));
	ORE::Skybox sky;
	//Convert test data into vectors
	std::vector<GLfloat> vert;
	std::vector<GLfloat> uv;
	for (int i=0; i < 36; i++) {
		vert.push_back(vertices[i * 5 + 0]);
		vert.push_back(vertices[i * 5 + 1]);
		vert.push_back(vertices[i * 5 + 2]);
		uv.push_back(vertices[i * 5 + 3]);
		uv.push_back(vertices[i * 5 + 4]);
	}
	/*
	vert.push_back(-1.0f);
	vert.push_back(-1.0f);
	vert.push_back(0.0f);

	vert.push_back(1.0f);
	vert.push_back(-1.0f);
	vert.push_back(0.0f);

	vert.push_back(0.0f);
	vert.push_back(1.0f);
	vert.push_back(0.0f);
	uv.push_back(0.0f);
	uv.push_back(0.0f);

	uv.push_back(1.0f);
	uv.push_back(0.0f);

	uv.push_back(0.5f);
	uv.push_back(1.0f);
	*/
	std::vector<GLfloat> norm;
	norm.push_back(0.0f);
	norm.push_back(0.0f);
	norm.push_back(1.0f);
	sky.setTextures("Testing/sky/right.png", "Testing/sky/left.png", "Testing/sky/top.png", "Testing/sky/bottom.png", "Testing/sky/front.png", "Testing/sky/back.png");
	world.setSkybox(&sky);
	testVAO.setMesh(vert, uv, norm);
	ORE::SimpleVAO test2 = testVAO;
	test2.setParent(&testVAO);
	testVAO.setPosition(glm::vec3(-2.0f, 0, 0));
	test2.setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	test2.setRotation(glm::quat(glm::vec3(0.0f, 0.8f, 0.0f)));
	world.addRenderable(&testVAO);
	world.addRenderable(&test2);
	cam->setPosition(glm::vec3(0, 0, 0));
	glfwSwapInterval(1);
	int w, h;
	glfwGetWindowSize(ORE::window, &w, &h);
	glfwSetCursorPos(ORE::window, w / 2.0, h / 2.0);
	pitch = 0;
	yaw = 0;
	double t = glfwGetTime();
	double testPos = 0;
	while (!glfwWindowShouldClose(ORE::window) && !glfwGetKey(ORE::window, GLFW_KEY_ESCAPE)) {
		glfwPollEvents();
		double elapsed = glfwGetTime() - t;
		t += elapsed;
		moveCamera(cam, elapsed);
		if (glfwGetKey(ORE::window, GLFW_KEY_SPACE)) {
			testPos += elapsed;
			testVAO.setPosition(glm::vec3(testPos, 0.0f, 0.0f));
		}
		world.draw();
	}
	ORE::destroy();
	return 0;
}
