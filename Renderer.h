#pragma once
#include<Drawer.h>
#include<BasicMath.h>
#include<GeometryUtil.h>
using namespace BasicMath;
using namespace GeometryUtil;

class Renderer : public Drawer {

	

public:
	Renderer(HINSTANCE hInst);
	~Renderer();

	virtual void UpdateScene() override;
	virtual void DrawScene() override;
	bool Init(bool customized = 0, int *height = nullptr, int *width = nullptr) override;


	void RenderTrapezoid(Trapezoid& trape);
	

	void DrawScanline(const Scanline& scanline);

	void DrawPrimitive(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	Transform transform;
};