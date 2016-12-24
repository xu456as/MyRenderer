#include <MainWindow.h>
#include <BasicMath.h>
class Renderer : public MainWindow {
public:
	Renderer(HINSTANCE hInstance);
	~Renderer();

	bool Init(bool customized = 0, int *height = nullptr, int *width = nullptr) override;

	void OnResize();

	void UpdateScene();
	void DrawScene();


protected:
	void FrameClear();
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

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, PSTR cmdLine, int showMode){
	Renderer theApp(hCurInst);

	if(!theApp.Init()){
		return 0;
	}
	return theApp.Run();
}

Renderer::Renderer(HINSTANCE Hinst)
:MainWindow(Hinst), globalMem(nullptr), globalPtr(nullptr), frameBuf(nullptr), zBuf(nullptr)
{

}

Renderer::~Renderer(){
	if(globalPtr)
		delete globalPtr;

	if(globalMem)
		delete globalMem;
}

bool Renderer::Init(bool customized, int* height, int* width){
	if(!MainWindow::Init(customized, height, width))
		return false;

	globalPtr = new void*[mClientHeight*2];
	globalMem = new UINT32[mClientHeight * mClientWidth *2];

	
	frameBuf = (UINT32**)globalPtr;

	zBuf = ((float**)globalPtr + mClientHeight);

	for(int i = 0;i<mClientHeight;++i){
		frameBuf[i] = screenFb + i*mClientWidth;
		zBuf[i] = (float*)globalMem + mClientHeight*mClientWidth + i*mClientWidth;
	}	

	return true;
}

void Renderer::OnResize(){
	
}

void Renderer::UpdateScene(){

}

void Renderer::ClearBuffer(){

}

void Renderer::DrawScene(){

}