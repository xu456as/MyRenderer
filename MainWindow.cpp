#include <MainWindow.h>

namespace{
	MainWindow* gmainWindow = nullptr;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
	return gmainWindow->MsgProc(hwnd, msg, wParam, lParam);
}

MainWindow::MainWindow(HINSTANCE hInstance)
:mhAppInst(hInstance), 
mMainWndCaption(L"My Renderer"),
mClientWidth(800),
mClientHeight(600),
mhMainWnd(0)
{

	gmainWindow = this;
}

MainWindow::~MainWindow(){

}

HINSTANCE MainWindow::AppInst() const {
	return mhAppInst;
}
HWND MainWindow::mainWnd() const {
	return mhMainWnd;
}

int MainWindow::Run()
{
	MSG msg = {0};


	while(msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if(PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		// Otherwise, do animation/game stuff.
		else
		{
			DrawScene();
			UpdateScene();
			Sleep(100);
		}
	}

	return (int)msg.wParam;
}
bool MainWindow::Init(bool customized, int *height, int *width){
	if(customized){
		mClientHeight = *height;
		mClientWidth = *width;
	}
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = MainWndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = mhAppInst;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = L"TemplateClass";

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);


	if( !RegisterClass(&wc) )
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mClientWidth, mClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int recWidth  = R.right - R.left;
	int recHeight = R.bottom - R.top;

	mhMainWnd = CreateWindow(L"TemplateClass", mMainWndCaption.c_str(), 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, recWidth, recHeight, 0, 0, mhAppInst, 0); 
	if( !mhMainWnd ){
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), mClientWidth, -mClientHeight, 1, 32, BI_RGB, 
		mClientWidth * mClientHeight * 4, 0, 0, 0, 0 }  };

	void* ptr;
	HDC hdc = GetDC(mhMainWnd);
	screenDC = CreateCompatibleDC(hdc);
	ReleaseDC(mhMainWnd, hdc);
	screenHb = CreateDIBSection(screenDC, &bi, DIB_RGB_COLORS, &ptr, nullptr, 0);

	if(!screenHb){
		MessageBox(0, L"CreateDIB Failed.", 0, 0);
		return false;
	}

	screenOb = (HBITMAP)SelectObject(screenDC, screenHb);

	screenFb = (UINT32*)ptr;

	memset(screenFb, 0, 4 * mClientHeight* mClientWidth);

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);

	return true;
}

LRESULT MainWindow::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

	switch( msg ){	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	//case WM_SIZE:
	////	mClientWidth = 0xffff & lParam;
	////	mClientHeight = 0xffff & (lParam >> 16);
	//	OnResize();

	//	return 0;


	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}	
}

void MainWindow::UpdateScene(){
//	*(screenFb + mClientWidth*40 + 40) = -1;
	HDC hDC = GetDC(mhMainWnd);
	BitBlt(hDC, 0, 0, mClientWidth, mClientHeight, screenDC, 0, 0, SRCCOPY);
	ReleaseDC(mhMainWnd, hDC);
}

void MainWindow::OnResize(){
	
}