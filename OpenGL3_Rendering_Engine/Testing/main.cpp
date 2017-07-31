#include "../ORE/World.h"
#include "../ORE/Engine.h"
#include "../ORE/SimpleVAO.h"
#include "../ORE/Skybox.h"
#include "../ORE/Light.h"
#include "../ORE/Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
//TODO: ADD Callbacks

double pitch, yaw;
glm::vec3 front;

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
	glm::vec3 right, up;
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
		pos -= cameraSpeed * front;
	}
	if (glfwGetKey(ORE::window, GLFW_KEY_S) == GLFW_PRESS) {
		pos += cameraSpeed * front;
	}
	if (glfwGetKey(ORE::window, GLFW_KEY_A) == GLFW_PRESS) {
		pos += glm::normalize(glm::cross(front, up)) * cameraSpeed;
	}
	if (glfwGetKey(ORE::window, GLFW_KEY_D) == GLFW_PRESS) {
		pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
	}
	c->setPosition(pos);
}

//Shamelessly lifted from learnopengl.com
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

int main() {
	ORE::init(1024, 768);
	ORE::World world;
	ORE::Camera* cam = world.getCamera();
	ORE::SimpleVAO testVAO;
	ORE::Model suit("Testing/nanosuit/nanosuit.obj");
	suit.setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	//suit.visible = false;
	GLuint texs[] = {
		ORE::loadImage("Testing/tmp.png"),
		ORE::loadImage("Testing/tmpSpec.png"),
		ORE::loadImage("Testing/tmpEm.png"),
		ORE::loadImage("Testing/tmpNorm.png"),
	};
	testVAO.setTexture(texs[0]);
	//testVAO.setSpecular(texs[1]);
	//testVAO.setEmission(texs[2]);
	testVAO.setNormal(texs[3]);
	ORE::Skybox sky;
	/*
	ORE::Light sun;
	sun.setType(ORE::LightType::DIRECTIONAL);
	sun.setDirection(glm::vec3(-1.0f, -1.0f, 0.0f));
	sun.setAmbient(glm::vec3(0.25f, 0.25f, 0.25f));
	sun.setDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	//sun.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
	sun.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	//sun.setSpecular(glm::vec3(0.5f, 0.0f, 0.0f));
	world.setLight(sun);
	//*/
	/*
	ORE::Light point;
	point.setType(ORE::LightType::POINT);
	point.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	point.setAmbient(glm::vec3(0.25f, 0.25f, 0.25f));
	point.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
	point.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	point.setAttenuation(1.0f, 0.09f, 0.032f);
	world.setLight(point);
	//*/
	//*
	ORE::Light spot;
	spot.setType(ORE::LightType::SPOTLIGHT);
	spot.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	spot.setDirection(glm::vec3(0.0f, 0.0f, -1.0f));
	spot.setAmbient(glm::vec3(0.25f, 0.25f, 0.25f));
	spot.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
	spot.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	spot.setAttenuation(1.0f, 0.09f, 0.032f);
	spot.setCutOff(glm::cos(glm::radians(12.5f)));
	spot.setOuterCutOff(glm::cos(glm::radians(17.5f)));
	world.setLight(spot);
	//*/
	//Convert test data into vectors
	std::vector<GLfloat> vert;
	std::vector<GLfloat> uv;
	std::vector<GLfloat> norm;
	for (int i=0; i < 36; i++) {
		vert.push_back(vertices[i * 8 + 0]);
		vert.push_back(vertices[i * 8 + 1]);
		vert.push_back(vertices[i * 8 + 2]);
		norm.push_back(vertices[i * 8 + 3]);
		norm.push_back(vertices[i * 8 + 4]);
		norm.push_back(vertices[i * 8 + 5]);
		uv.push_back(vertices[i * 8 + 6]);
		uv.push_back(vertices[i * 8 + 7]);
	}
	sky.setTextures("Testing/sky/right.png", "Testing/sky/left.png", "Testing/sky/top.png", "Testing/sky/bottom.png", "Testing/sky/front.png", "Testing/sky/back.png");
	world.setSkybox(&sky);
	testVAO.setMesh(vert, uv, norm);
	ORE::SimpleVAO test2 = testVAO;
	test2.setParent(&testVAO);
	testVAO.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	test2.setPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	test2.setRotation(glm::quat(glm::vec3(0.0f, 0.8f, 0.0f)));
	test2.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	world.addRenderable(&testVAO);
	world.addRenderable(&test2);
	world.addRenderable(&suit);
	cam->setPosition(glm::vec3(0, 0, 0));
	glfwSwapInterval(1);
	int w, h;
	glfwGetWindowSize(ORE::window, &w, &h);
	glfwSetCursorPos(ORE::window, w / 2.0, h / 2.0);
	pitch = 0;
	yaw = 0;
	double t = glfwGetTime();
	double testPos = 0;
	glfwSetInputMode(ORE::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	while (!glfwWindowShouldClose(ORE::window) && !glfwGetKey(ORE::window, GLFW_KEY_ESCAPE)) {
		glfwPollEvents();
		double elapsed = glfwGetTime() - t;
		t += elapsed;
		moveCamera(cam, elapsed);
		world.getLight()->setPosition(cam->getPosition());
		world.getLight()->setDirection(-front);
		if (glfwGetKey(ORE::window, GLFW_KEY_SPACE)) {
			testPos += elapsed;
			testVAO.setPosition(glm::vec3(testPos, 0.0f, 0.0f));
		}
		glm::vec3 p = cam->getPosition();
		//test2.setPosition(cam->getPosition());
		std::string t = std::to_string(p.x) + ", " + std::to_string(p.y) + ", " + std::to_string(p.z);
		glfwSetWindowTitle(ORE::window, t.c_str());
		world.draw();
	}
	ORE::destroy();
	return 0;
}
