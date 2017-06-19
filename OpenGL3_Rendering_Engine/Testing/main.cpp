#include "../ORE/World.h"
#include "../ORE/Engine.h"
#include <string>

int main() {
	ORE::init();
	ORE::World world;
	ORE::Camera* cam = world.getCamera();
	ORE::Skybox sky;
	sky.setTextures("Testing/sky/right.png", "Testing/sky/left.png", "Testing/sky/top.png", "Testing/sky/bottom.png", "Testing/sky/front.png", "Testing/sky/back.png");
	world.setSkybox(sky);
	cam->setPosition(glm::vec3(100, 100, 0));
	while(!glfwWindowShouldClose(ORE::window) && !glfwGetKey(ORE::window, GLFW_KEY_ESCAPE)) {
		glfwPollEvents();
		float t = static_cast<float>(glfwGetTime());
		t -= (glm::pi<float>()*2.0f) * floor(t / (glm::pi<float>()*2.0f));
		cam->setRotation(glm::quat(glm::vec3(0, t, 0.0f)));
		world.draw();
	}
	ORE::destroy();
	return 0;
}
