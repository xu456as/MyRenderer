#include <algorithm>
#include<Drawer.h>
//int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, PSTR cmdLine, int showMode){
//	Drawer theApp(hCurInst);
//
//	if(!theApp.Init()){
//		return 0;
//	}
//	return theApp.Run();
//}


Drawer::Drawer(HINSTANCE Hinst)
:MainWindow(Hinst), globalMem(nullptr), globalPtr(nullptr), frameBuf(nullptr), zBuf(nullptr)
{

}
Drawer::~Drawer(){
	if(globalPtr)
		delete[] globalPtr;

	if(globalMem)
		delete[] globalMem;
}

bool Drawer::Init(bool customized, int* height, int* width){
	if(!MainWindow::Init(customized, height, width))
		return false;

	globalPtr = new void*[mClientHeight*2];
	globalMem = new UINT32[mClientHeight * mClientWidth];

	
	frameBuf = (UINT32**)globalPtr;

	zBuf = ((float**)globalPtr+mClientHeight);

	for(int i = 0;i<mClientHeight;++i){
		frameBuf[i] = screenFb + i*mClientWidth;
		zBuf[i] = (float*)globalMem + i*mClientWidth;
		memset(zBuf[i], 0, sizeof(float) * mClientWidth);
	}

	return true;
}

void Drawer::DrawPixel(int x,int y, UINT32 color){
	--x;--y;
	if(x<0 || x>=mClientWidth)
		return;
	if(y<0 || y>=mClientHeight)
		return;
	//MessageBox(0, L"Draw pixed", L"draw pixel", 0);

	frameBuf[y][x] = color;

}


void Drawer::DrawLine(BasicMath::SceenPoint p1, BasicMath::SceenPoint p2, UINT32 color){
	//MessageBox(0, L"Draw Line", L"draw line", 0);
	int absX = abs(p1.x - p2.x);
	int absY = abs(p1.y - p2.y);
	if(absX==0 && absY==0){
		DrawPixel(p1.x, p2.y, color);
		return;
	}
	if(absX ==0){
		int minY = min(p1.y, p2.y);
		int maxY = max(p1.y, p2.y);
		for(int i = minY;i<=maxY;++i){
			DrawPixel(p1.x, i, color);
		}
		return;
	}
	if(absY ==0){
		int minX = min(p1.x, p2.x);
		int maxX = max(p1.x, p2.x);
		for(int i = minX;i<=maxX;++i){
			DrawPixel(i, p1.y, color);
		}
		return;
	}
	int a = BasicMath::gcd(absX, absY);
	absX /= a;
	absY /= a;
	if(absX>absY){
		if(p2.x<p1.x){
			BasicMath::SceenPoint temp = p1;
			p1 = p2;
			p2 = temp;
		}	
		int acc = 0;
		int curY = p1.y;
		int unitY = (p1.y<p2.y)?1:-1;
		for(int i=p1.x;i<=p2.x;++i){
			DrawPixel(i, curY, color);
			acc += absY;
			if(acc >= absX){
				acc -= absX;
				curY += unitY;
				DrawPixel(i, curY, color);
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
			DrawPixel(curX, i, color);
			acc += absX;
			if(acc >= absY){
				acc -= absY;
				curX += unitX;
				DrawPixel(curX, i, color);
			}
		}
	}
}


void Drawer::OnResize(){
	MainWindow::OnResize();
}

void Drawer::UpdateScene(){
	MainWindow::UpdateScene();
}


void Drawer::DrawScene(){
	//MessageBox(0, L"21", L"11", 0);
	DrawLine({ 0, 0 }, { 400, 425 }, -1);
}

void Drawer::ClearBuffer() {
	for (int i = 0; i < mClientHeight; ++i) {
		memset(frameBuf[i], 0, sizeof(UINT32) * mClientWidth);
		memset(zBuf[i], 0, sizeof(float) * mClientWidth);
	}
}