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
		{ { -1, -1, -1, 1 } ,{ 1.0f, 0.3f, 0.2f }, 1 }, //0
		{ { -1, -1, 1, 1 } ,{ 1.0f, 0.2f, 0.3f }, 1 }, //1
		{ { -1, 1, -1, 1 } ,{ 0.2f, 0.3f, 1.0f }, 1 }, //2
		{ { -1, 1, 1, 1 } ,{ 0.3f, 0.2f, 1.0f }, 1 }, //3
		{ { 1, -1, -1, 1 } ,{ 0.5f, 0.0f, 0.5f }, 1 }, //4
		{ { 1, -1, 1, 1 } ,{ 0.0f, 0.2f, 0.5f }, 1 }, //5
		{ { 1, 1, -1, 1 } ,{ 0.2f, 1.0f, 0.3f }, 1 }, //6
		{ { 1, 1, 1, 1 } ,{ 0.5f, 1.0f, 0.2f }, 1 } //7
	};
	Transform transform;

	BasicMath::SceenPoint lastPoint;

	float mTheta = 0.0f;
};