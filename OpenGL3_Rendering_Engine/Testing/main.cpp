#include "../ORE/World.h"
#include "../ORE/Engine.h"

int main() {
	ORE::init();
	World world;
	while(!glfwWindowShouldClose(ORE::window) && !glfwGetKey(ORE::window, GLFW_KEY_ESCAPE)) {
		glfwPollEvents();
		world.draw();
	}
	ORE::destroy();
	return 0;
}