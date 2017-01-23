#include<GeometryUtil.h>
using namespace GeometryUtil;

void Vertex::InitToRHW() {
	rhw = 1.0f / pos[3];
	
	for (int i = 0; i < 3; ++i) {
		pos[i] * rhw;
	}
	color.r *= rhw;
	color.g *= rhw;
	color.b *= rhw;
}

Vertex Vertex::GenerateMiddleVert(const Vertex& v1, const Vertex& v2, float weight) {
	Vertex newVert;
	float inv = 1.0 / weight;
	newVert.pos = (v2.pos - v1.pos) * inv;
	newVert.color.r = (v2.color.r - v1.color.r) * inv;
	newVert.color.g = (v2.color.g - v1.color.g) * inv;
	newVert.color.b = (v2.color.b - v1.color.b) * inv;
	newVert.rhw = (v2.rhw - v1.rhw) * inv;
	return newVert;
}

Vertex Vertex::operator+(const Vertex& v) {
	Vertex newVert;
	newVert.pos = this->pos +  v.pos;

	newVert.color.r = this->color.r + v.color.r;
	newVert.color.g = this->color.g + v.color.g;
	newVert.color.b = this->color.b + v.color.b;

	newVert.rhw = this->rhw + v.rhw;
	return newVert;
}
