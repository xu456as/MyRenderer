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

		void InitToRHW();
		
		Vertex operator+ (const Vertex& value);
		

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

		void Draw();
	};

	struct Trapezoid {
		float top;
		float bottom;
		Edge left;
		Edge right;
		Vertex curLeftVert;
		Vertex curRightVert;
		

		static std::vector<Trapezoid> GenerateTrapeZoid(const Vertex& v1, const Vertex& v2, const Vertex& v3);


		void ComputeCurVertices();

		Scanline GenerateScanlineByHeight(int y);

	};

	struct Transform {
		Matrix4x4 world;
		Matrix4x4 view;
		Matrix4x4 project;
		Matrix4x4 wvprj;
		float w;
		float h;

		Transform(int screenW, int screenH) {
			float aspectRatio = (float)screenW / screenH;
			world.SetIdentity();
			view.SetIdentity();
			project.SetIdentity();
			wvprj.SetIdentity();
			w = (float)screenW;
			h = (float)screenH;
			wvprj = world * view * project;

		}

		void Apply();

		int CheckCVV(const Vertex& v);

		Vertex Homogenize(const Vertex& v);
	};



}