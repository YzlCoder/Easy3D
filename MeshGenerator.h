#pragma once
#include "Mesh.h"

namespace easym
{
	class MeshGenerator
	{
	private:
		MeshGenerator();
		MeshGenerator(const MeshGenerator&);
		~MeshGenerator() {}
	public:
		static  Mesh CreateBox(real width, real height, real depth);
	};
}
