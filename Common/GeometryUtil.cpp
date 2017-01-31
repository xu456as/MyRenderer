#include<GeometryUtil.h>
using namespace GeometryUtil;

void Vertex::InitToRHW() {
	rhw = 1.0f / pos[3];
	
	color.r *= rhw;
	color.g *= rhw;
	color.b *= rhw;
}

Vertex Vertex::GenerateMiddleVert(const Vertex& v1, const Vertex& v2, float weight) {
	Vertex newVert;
	float inv = 1.0f / weight;
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

Vertex Vertex::operator-(const Vertex& v) {
	Vertex newVert;

	newVert.pos = this->pos - v.pos;

	newVert.color.r = this->color.r - v.color.r;
	newVert.color.g = this->color.g - v.color.g;
	newVert.color.b = this->color.b - v.color.b;

	newVert.rhw = this->rhw - v.rhw;
	return newVert;
}

Vertex Vertex::operator* (const float& num) {
	Vertex newVert;

	newVert.pos = this->pos * num;

	newVert.color.r = this->color.r * num;
	newVert.color.g = this->color.g * num;
	newVert.color.b = this->color.b * num;

	newVert.rhw = this->rhw * num;
	return newVert;
}

std::vector<Trapezoid> Trapezoid::GenerateTrapezoid(const Vertex& v1, const Vertex& v2, const Vertex& v3) {

	Vertex temp;

	Vertex p1 = v1, p2 = v2, p3 = v3;

	std::vector<Trapezoid> ret(0);

	if ((EqualF(p1.pos[1], p2.pos[1]) && EqualF(p2.pos[1], p3.pos[1]) ) ||
		(EqualF(p1.pos[0], p2.pos[0]) && EqualF(p2.pos[0], p3.pos[0]) ) )
		return ret;

	if (p1.pos[1] > p2.pos[1]) {
		temp = p1;
		p1 = p2;
		p2 = temp;
	}
	if (p1.pos[1] > p3.pos[1]) {
		temp = p1;
		p1 = p3;
		p3 = temp;
	}
	if (p2.pos[1] > p3.pos[1]) {
		temp = p2;
		p2 = p3;
		p3 = temp;
	}	

	if (EqualF(p1.pos[1], p2.pos[1])) {
		if (p1.pos[0] > p2.pos[0]) {
			temp = p1;
			p1 = p2;
			p2 = temp;
		}
		Trapezoid trape;
		trape.top = p1.pos[1];
		trape.bottom = p3.pos[1];
		trape.left.v1 = p1;
		trape.left.v2 = p3;
		trape.right.v1 = p2;
		trape.right.v2 = p3;
		
		ret.push_back(trape);
		return ret;
	}
	if (EqualF(p2.pos[1], p3.pos[1])) {
		if (p2.pos[0] > p3.pos[0]) {
			temp = p2;
			p2 = p3;
			p3 = temp;
		}
		Trapezoid trape;
		trape.top = p1.pos[1];
		trape.bottom = p3.pos[1];
		trape.left.v1 = p1;
		trape.left.v2 = p2;
		trape.right.v1 = p1;
		trape.right.v2 = p3;

		ret.push_back(trape);
		return ret;

	}

	Trapezoid up, down;

	up.top = p1.pos[1];
	up.bottom = p2.pos[1];
	down.top = p2.pos[1];
	down.bottom = p3.pos[1];

	float k = (p3.pos[1] - p1.pos[1]) / (p2.pos[1] - p1.pos[1]);
	float prjX2 = (p1.pos[0] + (p2.pos[0] - p1.pos[0]) * k);


	//angle in left side
	if (prjX2 < p3.pos[0]) {
		up.left.v1 = p1;
		up.left.v2 = p2;
		up.right.v1 = p1;
		up.right.v2 = p3;
		down.left.v1 = p2;
		down.left.v2 = p3;
		down.right.v1 = p1;
		down.right.v2 = p3;
	}
	//angle in right side
	else {
		up.left.v1 = p1;
		up.left.v2 = p3;
		up.right.v1 = p1;
		up.right.v2 = p2;
		down.left.v1 = p1;
		down.left.v2 = p3;
		down.right.v1 = p2;
		down.right.v2 = p3;
	}

	ret.push_back(up);
	ret.push_back(down);

	return ret;

}


void Trapezoid::ComputeCurVertices(float y) {
	float s1 = left.v2.pos[1] - left.v1.pos[1];
	float s2 = right.v2.pos[1] - right.v1.pos[1];

	float t1 = (y - left.v1.pos[1]) / s1;
	float t2 = (y - right.v1.pos[1]) / s2;

	curLeftVert = Lerp(left.v1, left.v2, t1);
	curRightVert = Lerp(right.v1, right.v2, t2);
}



Scanline Trapezoid::GenerateScanlineByHeight(int y) {
	Scanline scanline;
	scanline.y = y;
	scanline.curVert = curLeftVert;
	scanline.x = (int)(curLeftVert.pos[0] + 0.5f);
	scanline.w = (int)(curRightVert.pos[0] + 0.5f) - scanline.x;
	
	
	Vertex delta = curRightVert - curLeftVert;

	scanline.step = delta * (1.0f /  scanline.w);

	if (scanline.w < 0) {
		scanline.w = 0;
		scanline.step = Vertex{ {0, 0, 0, 1}, {0, 0, 0}, 0.0f };
	}

	return scanline;

}

Transform::Transform() {
	world.SetIdentity();
	view.SetIdentity();
	project.SetIdentity();
	wvprj.SetIdentity();
	CountWVProj();
}

Transform::Transform(int screenW, int screenH) {
	float aspectRatio = (float)screenW / screenH;
	world.SetIdentity();
	view.SetIdentity();
	project.SetIdentity();
	wvprj.SetIdentity();
	w = (float)screenW;
	h = (float)screenH;

	project.SetPerspective(0.5f * 3.14f, w / h, 1.0f, 500.0f);

	CountWVProj();
}

void Transform::CountWVProj() {
	wvprj = world * view * project;
}

void Transform::Apply(Vertex& x) {
	x.pos = x.pos.Apply(wvprj);
}

int Transform::CheckCVV(const Vertex& v) {

	float w = v.pos[3];
	int check = 0;

	if (v.pos[2] <= 0.0f) check |= 1;
	if (v.pos[2] >= w) check |= 2;
	if (v.pos[0] <= -w) check |= 4;
	if (v.pos[0] >= w) check |= 8;
	if (v.pos[1] <= -w) check |= 16;
	if (v.pos[1] >= w) check |= 32;

	return check;
}

void Transform::Homogenize(Vertex& v) {

	float rhw = (1.0f / v.pos[3]);

	v.rhw = rhw;

	v.pos = v.pos * rhw;

	v.pos[0] = (v.pos[0] + 1.0f) * 0.5f * w;
	v.pos[1] = (1.0f - v.pos[1]) * 0.5f * h;

}
