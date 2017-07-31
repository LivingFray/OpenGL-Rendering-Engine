#pragma once
#include "Camera.h"
#include "World.h"
namespace ORE {
	class Renderable {
	public:
		Renderable();
		virtual ~Renderable();
		// Draws the renderable
		virtual void draw(ORE::World* world) = 0;
		bool visible = true;
	};
}
