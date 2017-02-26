#pragma once
#include "Mesh.h"


namespace Merlin{
	class SphereMesh : public Mesh{
	private:
		void Create(double r, int lats, int longs);
	public:
		SphereMesh();
		~SphereMesh();
		void Initialise();
		void Render();
	};
}