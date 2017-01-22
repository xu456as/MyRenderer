#include <MainWindow.h>
#include <BasicMath.h>
class Renderer : public MainWindow {
public:
	Renderer(HINSTANCE hInstance);
	~Renderer();

	virtual bool Init(bool customized = 0, int *height = nullptr, int *width = nullptr) override;

	void OnResize();

	//LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

	virtual void UpdateScene() override;
	virtual void DrawScene() override;


protected:

	void DrawPixel(int x,int y, UINT32 color);
	void DrawLine(BasicMath::SceenPoint p1, BasicMath::SceenPoint p2, UINT32 color);
	void ClearBuffer();


private:

	void *globalPtr;
	UINT32 *globalMem;

	UINT32 **frameBuf;
	float **zBuf;

	UINT32 bgColor;
	UINT32 frColor;
};