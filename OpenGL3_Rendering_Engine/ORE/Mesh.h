#pragma once
#include "Renderable.h"
#include "Transformable.h"

namespace ORE {
	class Mesh :
		public Renderable,
		public Transformable{
	public:
		Mesh();
		virtual ~Mesh();
	};
}
