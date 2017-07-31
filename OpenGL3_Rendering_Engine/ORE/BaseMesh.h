#pragma once
#include "Renderable.h"
#include "Transformable.h"

namespace ORE {
	class BaseMesh :
		public Renderable,
		public Transformable{
	public:
		BaseMesh();
		virtual ~BaseMesh();
	};
}
