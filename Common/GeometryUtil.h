#pragma once
#include<BasicMath.h>
namespace GeometryUtil{
	struct Color{
		float r;
		float g;
		float b;
	};

	struct Vertex {
		BasicMath::Vector4 pos;
		Color color;

	};

	struct Edge {
		Vertex v1;
		Vertex v2;
	};

	struct Trapezoid {
		float top;
		float bottom;
		Edge left;
		Edge right;
		Vertex curLeftVert;
		Vertex curRightVert;

		void ComputeCurVertices();
	};

	struct Scanline {

	};

}