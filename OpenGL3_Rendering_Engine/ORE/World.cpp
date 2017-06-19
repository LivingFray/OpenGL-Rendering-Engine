#include "World.h"
#include "Engine.h"

namespace ORE {
	World::World() {
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		camera.setWidth(static_cast<float>(w));
		camera.setHeight(static_cast<float>(h));
	}


	World::~World() {
	}


	// Renders the world
	void World::draw() const{
		if (window) {
			//temp
			glClearColor(0.0, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			////Draw the world
			//Draw objects
			//Draw the skybox
			skybox.draw(camera);
		}
		glfwSwapBuffers(window);
	}

	// Gets a pointer to the camera
	Camera* World::getCamera() {
		return &camera;
	}


	// Sets the skybox of the world
	void World::setSkybox(Skybox s) {
		this->skybox = s;
	}
}