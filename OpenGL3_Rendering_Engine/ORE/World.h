#pragma once
#include "Camera.h"
#include "Light.h"
#include <vector>

namespace ORE {
	class Renderable;
	class Skybox;
	class World {
	public:
		World();
		~World();
		// Renders the world
		void draw();
		// Gets a pointer to the camera
		Camera* getCamera();
		// Sets the skybox of the world
		void setSkybox(Skybox* s);
		// Adds a new renderable to the world
		void addRenderable(Renderable* r);
		//TEMP
		Light* getLight();
		void setLight(Light l);
	private:
		Camera camera;
		Skybox* skybox;
		std::vector<Renderable*> renderables;
		Light lightSource; //TEMP, 1 source per scene is horrible
	};
}
