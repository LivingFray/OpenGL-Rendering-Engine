#pragma once
#include "Skybox.h"
#include "Camera.h"
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
		void setSkybox(Skybox s);
	private:
		Camera camera;
		Skybox skybox;
	};
}
