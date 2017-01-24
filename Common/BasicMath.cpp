#include <BasicMath.h>
#include<math.h>
namespace BasicMath
{
	/*
		Start Vector definition and operation
 	*/


	float Vector4::Length(){
		return sqrt(v[0] * v[0] + v[1]*v[1]+ v[2]*v[2]);
	}
	void Vector4::Normalize(){
		float length = Length();
		v[0] /= length;
		v[1] /= length;
		v[2] /= length;
	}
	Vector4 Vector4::Cross (const Vector4& x) const{
		Vector4 retVec;
		retVec[0] = this->v[1] * x[2] - this->v[2] * x[1];
		retVec[1] = this->v[2] * x[0] - this->v[0] * x[2];
		retVec[2] = this->v[0] * x[1] - this->v[1] * x[0];
		retVec[3] = 1.0f;

		return retVec;
	}
	Vector4 Vector4::Apply (const Matrix4x4& x) const{
		
		Vector4 retVec;
		for(int i=0;i<4;++i){
			for(int j=0;j<4;++j){
				retVec[j] += this->v[i] * x.m[j][i];
			}
		}
		return retVec;
	}

	Vector4 Vector4::operator- (const Vector4& x) const {
		return Vector4(this->v[0]-x[0], this->v[1]-x[1], this->v[2]-x[2], this->v[3]-x[3]);
	}

	float operator* (const Vector4& x, const Vector4& y){
		float sum = 0.0f;
		for(int i=0;i<3;++i){
			sum += x[i] *y[i];
		}
		return sum;
	}
		

	Vector4 operator+ (const Vector4& x, const Vector4& y){
		return Vector4(x[0]+y[0], x[1]+y[1], x[2]+y[2], x[3]+y[3]);
	}

	Vector4 operator* (const Vector4& x, const float& num){
		return Vector4(x[0]*num, x[1]*num, x[2]*num, x[3]);
	}

	/*
		End Vector definition and operation
 	*/

	/*
		Start Matrix definition and operation
 	*/

	
	void Matrix4x4::SetZero(){
		memset(m, 0, sizeof(m));
	}
	void Matrix4x4::SetIdentity(){
		memset(m, 0, sizeof(m));
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
	}

	void Matrix4x4::SetTranslate(float x, float y, float z){
		SetIdentity();
		m[3][0] = x;
		m[3][1] = y;
		m[3][2] = z;
	}
	void Matrix4x4::SetScale(float x, float y, float z){
		SetIdentity();
		m[0][0] *= x;
		m[1][1] *= y;
		m[2][2] *= z;
	}

	void Matrix4x4::SetRotate(Vector4 privot, float theta){
		privot.Normalize();
		float x = privot[0],y = privot[1], z = privot[2];
		float s = sinf(theta);
		float c = cosf(theta);

		m[0][0] = c + (1 - c) * x*x;
		m[1][0] = -s*z + (1-c) * y*x;
		m[2][0] = s*y + (1-c) * z*x;

		m[0][1] = s*z + (1 - c) * x*y;
		m[1][1] = c + (1-c) * y*y;
		m[2][1] = -s*x + (1-c) * z*y;

		m[0][2] = -s*y + (1 - c) * x*z;
		m[1][2] = s*x + (1-c) * y*z;
		m[2][2] = c + (1-c) * z*z;

		m[0][3] = m[1][3] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	void Matrix4x4::SetLookAt(Vector4 eye, Vector4 at, Vector4 up){
		Vector4 zAxis = at - eye;
		zAxis.Normalize();

		Vector4 xAxis =  up.Cross(zAxis);
		xAxis.Normalize();

		Vector4 yAxis = zAxis.Cross(xAxis);
		yAxis.Normalize();

		m[0][0] = xAxis[0];
		m[1][0] = xAxis[1];
		m[2][0] = xAxis[2];
		m[3][0] =  -(xAxis * eye);

		m[0][1] = yAxis[0];
		m[1][1] = yAxis[1];
		m[2][1] = yAxis[2];
		m[3][1] = -(yAxis * eye);

		m[0][2] = zAxis[0];
		m[1][2] = zAxis[1];
		m[2][2] = zAxis[2];
		m[3][2] = -(zAxis * eye);

		m[0][3] = m[1][3] = m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	void Matrix4x4::SetPerspective(float fovAngleY, float aspectRatio, float nearZ, float farZ){
		float tan = tanf(aspectRatio / 2);
		SetZero();

		m[0][0] = 1 / (aspectRatio * tan);

		m[1][1] = 1 / (tan);

		m[2][2] = farZ / (farZ - nearZ);
		m[3][2] = - (nearZ*farZ) / (farZ - nearZ);

		m[2][3] = 1.0f;

	}

	Matrix4x4 Matrix4x4::operator* (const Matrix4x4& y) const {
		Matrix4x4 retMat;
		for(int i=0;i<4;++i){
			for(int j=0;j<4;++j){
				for(int k=0;k<4;++k){
					retMat[i][j] = (this->m[i][k] * y[k][j]);
				}
			}
		}
		return retMat;
	}

	Matrix4x4 Matrix4x4::operator- (const Matrix4x4& y) const {
		Matrix4x4 retMat;
		for(int i=0;i<4;++i){
			for(int j=0;j<4;++j){
				retMat[i][j] = this->m[i][j] - y[i][j];
			}
		}
		return retMat;
	}



	Matrix4x4 operator* (const Matrix4x4& x, const float& num){
		Matrix4x4 retMat;
		for(int i=0;i<4;++i){
			for(int j=0;j<4;++j){
				retMat[i][j] = x[i][j] * num;
			}
		}
		return retMat;
	}
	
	/*
		End Matrix definition and operation
 	*/
	template<typename T>
	T Clamp(T x, T min, T max){
		if(x<min)
			return min;
		else if(x>max)
			return max;
		else
			return x;
	}

	template<typename T>
	T Lerp(T from, T to, float x){
		return from + (to - from) * x;
	}

	int gcd(int x, int y){
		return y==0?x:gcd(y, x%y);
	}

	bool EqualF(float f1, float f2) {
		return fabs(f1 - f2) <= 0.0001f;
	}
}