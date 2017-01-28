#include<Renderer.h>

Renderer::Renderer(HINSTANCE hInst)
	:Drawer(hInst), transform(mClientWidth, mClientHeight)
{
	
}

Renderer::~Renderer() {}

bool Renderer::Init(bool customized, int *height , int *width) {
	return Drawer::Init(customized, height, width);
}

void Renderer::DrawScene() {	
	ClearBuffer();


	LookAtZero(0, 0,15);

	DrawBox(0);

	/*Scanline scanline;
	scanline.y = 100;
	scanline.x = 3;

	scanline.curVert = Vertex{ {3, 100, 1, 1}, {1.0, 1.0, 1.0 }, 1.0f };
	scanline.step = Vertex{ {1, 0, 1, 1}, {0,0, 0}, 1.0f };
	scanline.w = 600;
	DrawScanline(scanline);*/

	//Vertex m[3] = {
	//	{ { 0.4f, 0.3f, 1.0f, 1 } ,{ 1, 1, 1 }, 1 },
	//	{ { 0.1f, 0.2f, 1.0f, 1 } ,{ 1, 1, 1 }, 1 },
	//	{ { 0.4f, 0.1f, 1.0f, 1 } ,{ 1, 1, 1 }, 1 }
	//};

	//DrawPrimitive(m[0], m[1], m[2]);

}
void Renderer::UpdateScene() {
	Drawer::UpdateScene();
}

void Renderer::RenderTrapezoid(Trapezoid& trape) {
	int top = (int)(trape.top + 0.5f);
	int bottom = (int)(trape.bottom + 0.5f);
	for (int i = top; i <= bottom; ++i) {
		if (i >= 0 && i < mClientHeight) {
			trape.ComputeCurVertices((int)(i + 0.5f));
			Scanline scanline = trape.GenerateScanlineByHeight(i);
			DrawScanline(scanline);
		}
		else
			break;
	}
}


void Renderer::DrawScanline(const Scanline& scanline) {

	float* curZBufLn = zBuf[scanline.y];
	UINT32* curFBufLn = frameBuf[scanline.y];

	int beg = scanline.x, ed = beg + scanline.w;

	Vertex curVert = scanline.curVert;

	for (int i = beg; i <= ed; ++i) {
		if (i < 0 || i >= mClientWidth)
			break;

		float rhw = curVert.rhw;
		float w = 1.0f / rhw;
		
		curZBufLn[i] = rhw;

		float r = curVert.color.r * w;
		float g = curVert.color.g * w;
		float b = curVert.color.b * w;

		int R = (int)(255.0f * r);
		int G = (int)(255.0f * g);
		int B = (int)(255.0f * b);

		curFBufLn[i] = (R << 16) | (G << 8) | (B);

		curVert = curVert + scanline.step;
	}
}

void Renderer::DrawPrimitive(const Vertex& v1, const Vertex& v2, const Vertex& v3) {

	Vertex p1 = v1, p2 = v2, p3 = v3;

	transform.Apply(p1);
	transform.Apply(p2);
	transform.Apply(p3);

	if (transform.CheckCVV(p1) || transform.CheckCVV(p2) || transform.CheckCVV(p3))
		return;


	transform.Homogenize(p1);
	transform.Homogenize(p2);
	transform.Homogenize(p3);

	std::vector<Trapezoid> traps = Trapezoid::GenerateTrapezoid(p1, p2, p3);

	if (traps.size() >= 1) {
		RenderTrapezoid(traps[0]);
	}
	if (traps.size() >= 2) {
		RenderTrapezoid(traps[1]);
	}



}

void Renderer::DrawPlane(int i1, int i2, int i3, int i4) {
	Vertex v1 = mesh[i1], v2 = mesh[i2], v3 = mesh[i3], v4 = mesh[i4];

	DrawPrimitive(v1, v2, v3);
	DrawPrimitive(v3, v4, v1);
}

void Renderer::DrawBox(float theta) {
	Matrix4x4 m;
	transform.world.SetRotate({ 0, 1, 0 , 1 }, theta);
	transform.CountWVProj();

	//Vertex mesh[8] = {
	//0	{ { -1, -1, -1, 1 } ,{ 1, 1, 1 }, 1 },
	//1	{ { -1, -1, 1, 1 } ,{ 1, 1, 1 }, 1 },
	//2	{ { -1, 1, -1, 1 } ,{ 1, 1, 1 }, 1 },
	//3	{ { -1, 1, 1, 1 } ,{ 1, 1, 1 }, 1 },
	//4	{ { 1, -1, -1, 1 } ,{ 1, 1, 1 }, 1 },
	//5	{ { 1, -1, 1, 1 } ,{ 1, 1, 1 }, 1 },
	//6	{ { 1, 1, -1, 1 } ,{ 1, 1, 1 }, 1 },
	//7	{ { 1, 1, 1, 1 } ,{ 1, 1, 1 }, 1 }
	//};

	DrawPlane(1, 5, 7, 3);
//	DrawPlane(5, 4, 6, 7);
	//DrawPlane(4, 0, 2, 6);
//	DrawPlane(0, 1, 3, 2);
//	DrawPlane(3, 7, 6, 2);
//	DrawPlane(0, 4, 5, 1);

}
void Renderer::LookAtZero(float x, float y, float z) {
	Vector4 eye{ x, y, z, 1 };
	Vector4 at{ 0, 0, 0, 1 };
	Vector4 up{ 0, 1, 0, 1 };
	transform.view.SetLookAt(eye, at, up);
	transform.CountWVProj();
}


int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, PSTR cmdLine, int showMode) {

	Renderer instApp = Renderer(hCurInst);
	if (!(instApp).Init()) {
		return 0;
	}
	return (instApp).Run();
}
