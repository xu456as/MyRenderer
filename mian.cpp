#include<Windows.h>
#include<Renderer.h>
using namespace GeometryUtil;
using namespace BasicMath;
Vertex mesh[8] = {
	{{-1, -1, -1, 1} , {0, 0, 0}, 1 }, 
	{ { -1, -1, 1, 1 } ,{ 0, 0, 0 }, 1 },
	{ { -1, 1, -1, 1 } ,{ 0, 0, 0 }, 1 },
	{ { -1, 1, 1, 1 } ,{ 0, 0, 0 }, 1 },
	{ { 1, -1, -1, 1 } ,{ 0, 0, 0 }, 1 },
	{ { 1, -1, 1, 1 } ,{ 0, 0, 0 }, 1 },
	{ { 1, 1, -1, 1 } ,{ 0, 0, 0 }, 1 },
	{ { 1, 1, 1, 1 } ,{ 0, 0, 0 }, 1 }
};

Renderer *theApp;

void DrawPlane(int i1, int i2, int i3, int i4) {
	Vertex v1 = mesh[i1], v2 = mesh[i2], v3 = mesh[i3], v4 = mesh[i4];

	(*theApp).DrawPrimitive(v1, v2, v3);
	(*theApp).DrawPrimitive(v2, v3, v4);
}

void DrawBox(float theta) {
	Matrix4x4 m;
	(*theApp).transform.world.SetRotate({ 0, 1, 0 , 1}, theta);
	(*theApp).transform.CountWVProj();

	DrawPlane(0, 1, 5, 4);
	DrawPlane(2, 3, 7, 6);
	DrawPlane(4, 5, 7, 6);
	DrawPlane(0, 1, 3, 1);
	DrawPlane(0, 2, 6, 4);
	DrawPlane(1, 3, 7, 5);
	
}
void LookAtZero(float x, float y, float z) {
	Vector4 eye{ x, y, z, 1 };
	Vector4 at{ 0, 0, 0, 1 };
	Vector4 up{ 0, 1, 0, 1 };
	(*theApp).transform.view.SetLookAt(eye, at, up);
	(*theApp).transform.CountWVProj();
}


int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, PSTR cmdLine, int showMode){
	theApp = &Renderer(hCurInst);

	if(!(*theApp).Init()){
		return 0;
	}
	return (*theApp).Run();
}