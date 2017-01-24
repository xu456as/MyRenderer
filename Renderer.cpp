#include<Renderer.h>

Renderer::Renderer(HWND hInst)
	:Drawer(hInst), transform(mClientWidth, mClientHeight)
{
	
}

Renderer::~Renderer() {}

void Renderer::DrawScene() {

}
void Renderer::UpdateScene() {

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

}

void Renderer::DrawPrimitive(const Vertex& v1, const Vertex& v2, const Vertex& v3) {

	Vertex p1 = v1, p2 = v2, p3 = v3;

	transform.Apply(p1);
	transform.Apply(p2);
	transform.Apply(p3);

	if (!transform.CheckCVV(p1) || !transform.CheckCVV(p2) || !transform.CheckCVV(p3))
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
