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

	virtual bool Init(bool customized, int *height, int *width);

	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y){ }
	virtual void OnMouseUp(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y){ }

protected:
	HINSTANCE mhAppInst;
	HWND      mhMainWnd;

	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

};