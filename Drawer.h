#pragma once
#include <MainWindow.h>
#include <BasicMath.h>
class Drawer : public MainWindow {
public:
	Drawer(HINSTANCE hInstance);
	~Drawer();

	virtual bool Init(bool customized = 0, int *height = nullptr, int *width = nullptr) override;

	//void OnResize();

	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

	virtual void UpdateScene() override;
	virtual void DrawScene() override;
	virtual void OnResize() override;


protected:

	void DrawPixel(int x,int y, UINT32 color);
	void DrawLine(BasicMath::SceenPoint p1, BasicMath::SceenPoint p2, UINT32 color);
	void ClearBuffer();

	


protected:

	void *globalPtr;
	UINT32 *globalMem;

	UINT32 **frameBuf;
	float **zBuf;

	UINT32 bgColor;
	UINT32 frColor;
};