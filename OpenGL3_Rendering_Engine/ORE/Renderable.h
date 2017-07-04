#pragma once
#include "Camera.h"
namespace ORE {
	class Renderable {
	public:
		Renderable();
		virtual ~Renderable();
		// Draws the renderable
		virtual void draw(Camera cam) = 0;
	};
}
