#pragma once
#include "Skybox.h"
#include "Camera.h"
#include "Renderable.h"
#include <vector>

namespace ORE {
	class World {
	public:
		World();
		~World();
		// Renders the world
		void draw() const;
		// Gets a pointer to the camera
		Camera* getCamera();
		// Sets the skybox of the world
		void setSkybox(Skybox* s);
		// Adds a new renderable to the world
		void addRenderable(Renderable* r);
	private:
		Camera camera;
		Skybox* skybox;
		std::vector<Renderable*> renderables;
	};
}
