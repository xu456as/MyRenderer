#pragma once
#include <WindowsX.h>
#include <Windows.h>
#include <string>

class MainWindow{
public :
	MainWindow(HINSTANCE hInstance);
	virtual ~MainWindow();

	HINSTANCE AppInst() const;
	HWND mainWnd() const;

	int Run();

	virtual bool Init(bool customized = 0, int *height = nullptr, int *width = nullptr);

	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void UpdateScene();
	virtual void DrawScene(){}

	// Convenience overrides for handling mouse input.
	virtual void OnResize();
	virtual void OnMouseDown(WPARAM btnState, int x, int y){ }
	virtual void OnMouseUp(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y){ }

public:
	HINSTANCE mhAppInst;
	HWND      mhMainWnd;

	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	HDC screenDC;
	HBITMAP screenHb;
	HBITMAP screenOb;

	UINT32* screenFb;
};