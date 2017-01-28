#pragma once
#include<BasicMath.h>
#include<vector>
using namespace BasicMath;
namespace GeometryUtil{
	struct Color{
		float r;
		float g;
		float b;
	};

	struct Vertex {
		BasicMath::Vector4 pos;
		Color color;
		float rhw;

		void InitToRHW();
		
		Vertex operator+ (const Vertex& value);

		Vertex operator- (const Vertex& value);

		Vertex operator* (const float& num);
		

		static Vertex GenerateMiddleVert(const Vertex& v1, const Vertex& v2, float weight);

		
	};

	struct Edge {
		Vertex v1;
		Vertex v2;
	};

	struct Scanline {
		Vertex curVert;
		Vertex step;
		int x;
		int y;
		int w;
	};

	struct Trapezoid {
		float top;
		float bottom;
		Edge left;
		Edge right;
		Vertex curLeftVert;
		Vertex curRightVert;
		

		static std::vector<Trapezoid> GenerateTrapezoid(const Vertex& v1, const Vertex& v2, const Vertex& v3);


		void ComputeCurVertices(float y);

		Scanline GenerateScanlineByHeight(int y);

	};

	struct Transform {
		Matrix4x4 world;
		Matrix4x4 view;
		Matrix4x4 project;
		Matrix4x4 wvprj;
		float w;
		float h;

		Transform();

		Transform(int screenW, int screenH);

		void CountWVProj();

		void Apply(Vertex& x);

		int CheckCVV(const Vertex& v);

		void Homogenize(Vertex& v);
	};



}