#pragma once
#include<Drawer.h>
#include<BasicMath.h>
#include<GeometryUtil.h>
using namespace BasicMath;
using namespace GeometryUtil;

class Renderer : Drawer {
public:
	Renderer(HWND hInst);
	~Renderer();

	virtual void UpdateScene() override;
	virtual void DrawScene() override;

protected:

	void RenderTrapezoid(Trapezoid& trape);
	

	void DrawScanline(const Scanline& scanline);

	void DrawPrimitive(const Vertex& v1, const Vertex& v2, const Vertex& v3);

protected:
	Transform transform;
};