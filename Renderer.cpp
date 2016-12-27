#include <MainWindow.h>
#include <BasicMath.h>
class Renderer : public MainWindow {
public:
	Renderer(HINSTANCE hInstance);
	~Renderer();

	bool Init(bool customized = 0, int *height = nullptr, int *width = nullptr) override;

	void OnResize();

	void UpdateScene() override;
	void DrawScene() override;


protected:
	
	void DrawPixel(int x,int y, UINT32 color);
	void DrawLine(BasicMath::SceenPoint p1, BasicMath::SceenPoint p2, UINT32 color);
	

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
		delete[] globalPtr;

	if(globalMem)
		delete[] globalMem;
}

bool Renderer::Init(bool customized, int* height, int* width){
	if(!MainWindow::Init(customized, height, width))
		return false;

	globalPtr = new void*[mClientHeight*2];
	globalMem = new UINT32[mClientHeight * mClientWidth];

	
	frameBuf = (UINT32**)globalPtr;

	zBuf = ((float**)globalPtr+mClientHeight);

	for(int i = 0;i<mClientHeight;++i){
		frameBuf[i] = screenFb + i*mClientWidth;
		zBuf[i] = (float*)globalMem + i*mClientWidth;
	}	

	return true;
}

void Renderer::DrawPixel(int x,int y, UINT32 color){
	if(x<0 || x>=mClientWidth)
		return;
	if(y<0 || y>=mClientHeight)
		return;

	frameBuf[y][x] = color;
}

void Renderer::DrawLine(BasicMath::SceenPoint p1, BasicMath::SceenPoint p2, UINT32 color){

	int absX = abs(p1.x - p2.x);
	int absY = abs(p1.y - p2.y);
	int a = BasicMath::gcd(absX, absY);
	absX /= a;
	absY /= a;
	if(absX<absY){
		if(p2.x<p1.x){
			BasicMath::SceenPoint temp = p1;
			p1 = p2;
			p2 = temp;
		}	
		int acc = 0;
		int curY = p1.y;
		int unitY = (p1.y<p2.y)?1:-1;
		for(int i=p1.x;i<=p2.x;++i){
			DrawPixel(curY, i, color);
			if(++acc == absX){
				acc -= absY;
				curY += unitY;
				DrawPixel(curY, i, color);
			}
		}
	}
	else{
		if(p2.y<p1.y){
			BasicMath::SceenPoint temp = p1;
			p1 = p2;
			p2 = temp;
		}	
		int acc = 0;
		int curX = p1.x;
		int unitX = (p1.x<p2.x)?1:-1;
		for(int i=p1.y;i<=p2.y;++i){
			DrawPixel(i, curX, color);
			if(++acc == absY){
				acc -= absX;
				curX += unitX;
				DrawPixel(i, curX, color);
			}
		}
	}
}


void Renderer::OnResize(){
	MainWindow::OnResize();
}

void Renderer::UpdateScene(){
	MainWindow::UpdateScene();
}


void Renderer::DrawScene(){
	
	DrawLine( BasicMath::SceenPoint(420, 440), BasicMath::SceenPoint(40, 20), -1);
	DrawLine( BasicMath::SceenPoint(440, 420), BasicMath::SceenPoint(20, 40), -1);
}