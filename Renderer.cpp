#include<Renderer.h>
#include<assert.h>
Renderer::Renderer(HINSTANCE hInst)
	:Drawer(hInst), transform(mClientWidth, mClientHeight), lastPoint{0, 0}
{
	
}

Renderer::~Renderer() {}

bool Renderer::Init(bool customized, int *height , int *width) {
	return Drawer::Init(customized, height, width);
}

void Renderer::UpdateScene() {
	Drawer::UpdateScene();
}


void Renderer::OnMouseDown(WPARAM wParam, int x, int y) {
	lastPoint.x = x;
	lastPoint.y = y;
	SetCapture(mhMainWnd);
}

void Renderer::OnMouseUp(WPARAM wParam, int x, int y) {
	ReleaseCapture();
}

void Renderer::OnMouseMove(WPARAM wParam, int x, int y) {
	if ((wParam & MK_LBUTTON) != 0)
	{
		
		float dx = x - lastPoint.x;

	
		mTheta += dx;
	}

	lastPoint.x = x;
	lastPoint.y = y;
}

LRESULT Renderer::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	default:
		return MainWindow::MsgProc(hwnd, msg, wParam, lParam);
	}
}

void Renderer::RenderTrapezoid(Trapezoid& trape) {
	int top = (int)(trape.top + 0.5f);
	int bottom = (int)(trape.bottom + 0.5f);


	for (int i = top; i <= bottom; ++i) {
		if (i >= 0 && i < mClientHeight) {
			trape.ComputeCurVertices((i + 0.5f));
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

		if (rhw >= curZBufLn[i]) {

			curZBufLn[i] = rhw;

			float r = curVert.color.r ;
			float g = curVert.color.g ;
			float b = curVert.color.b ;

			int R = (int)(255.0f * r);
			int G = (int)(255.0f * g);
			int B = (int)(255.0f * b);

			curFBufLn[i] = (R << 16) | (G << 8) | (B);
		}

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

void Renderer::DrawBox() {
	Matrix4x4 m;
	transform.world.SetRotate({ 0, 1, 0 , 1 }, mTheta);
	transform.CountWVProj();

	//WCHAR str[1000];
	//swprintf(str, L"%.2f\n", mTheta);
	//OutputDebugString(str);

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
	
	
	DrawPlane(4, 5, 7, 6);
	DrawPlane(5, 1, 3, 7);
	DrawPlane(1, 0, 2, 3);
	DrawPlane(4, 0, 2, 6);
	DrawPlane(6, 7, 3, 2);
	DrawPlane(0, 1, 5, 4);

}
void Renderer::DrawScene() {
	ClearBuffer();


	LookAtZero(5, 0, 0);

	DrawBox();
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
