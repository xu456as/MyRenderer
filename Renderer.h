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
	virtual bool Init(bool customized = 0, int *height = nullptr, int *width = nullptr) override;

	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

	void RenderTrapezoid(Trapezoid& trape);
	

	void DrawScanline(const Scanline& scanline);

	void DrawPrimitive(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	void DrawPlane(int i1, int i2, int i3, int i4);

	void DrawBox();

	void LookAtZero(float x, float y, float z);

	virtual void OnMouseDown(WPARAM wParam, int x, int y) override;

	virtual void OnMouseUp(WPARAM wParam, int x, int y) override;

	virtual void OnMouseMove(WPARAM wParam, int x, int y) override;

public:

	Vertex mesh[8] = {
		{ { -1, -1, -1, 1 } ,{ 1.0f, 1.0f, 1.0f }, 1 },
		{ { -1, -1, 1, 1 } ,{ 1.0f, 1.0f, 1.0f }, 1 },
		{ { -1, 1, -1, 1 } ,{ 1.0f, 1.0f, 1.0f }, 1 },
		{ { -1, 1, 1, 1 } ,{ 1.0f, 1.0f, 1.0f }, 1 },
		{ { 1, -1, -1, 1 } ,{ 1.0f, 1.0f, 1.0f }, 1 },
		{ { 1, -1, 1, 1 } ,{ 1.0f, 1.0f, 1.0f }, 1 },
		{ { 1, 1, -1, 1 } ,{ 1.0f, 1.0f, 1.0f }, 1 },
		{ { 1, 1, 1, 1 } ,{ 1.0f, 1.0f, 1.0f }, 1 }
	};
	Transform transform;

	BasicMath::SceenPoint lastPoint;

	float mTheta = 0.0f;
};