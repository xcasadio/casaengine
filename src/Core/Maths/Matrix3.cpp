#include "Maths/Matrix3.h"
#include "Maths/Vector2.h"
#include "Maths/Vector3.h"

namespace CasaEngine
{
	Matrix3::Matrix3(float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33) :
		a11(m11), a21(m21), a31(m31),
		a12(m12), a22(m22), a32(m32),
		a13(m13), a23(m23), a33(m33)
	{
	}

	void Matrix3::Identity()
	{
		a11 = 1.0f; a12 = 0.0f; a13 = 0.0f;
		a21 = 0.0f; a22 = 1.0f; a23 = 0.0f;
		a31 = 0.0f; a32 = 0.0f; a33 = 1.0f;
	}

	float Matrix3::Determinant() const
	{
		const float A = a22 * a33 - a32 * a23;
		const float B = a21 * a33 - a31 * a23;
		const float C = a22 * a32 - a31 * a22;

		return a11 * A - a12 * B + a13 * C;
	}

	Matrix3 Matrix3::Transpose() const
	{
		return {
			a11, a21, a31,
			a12, a22, a32,
			a13, a23, a33
		};
	}

	Matrix3 Matrix3::Inverse() const
	{
		Matrix3 Ret;
		const float Det = Determinant();

		if (std::fabs(Det) > std::numeric_limits<float>::epsilon())
		{
			Ret.a11 = (a22 * a33 - a23 * a32) / Det;
			Ret.a12 = (a12 * a13 - a32 * a33) / Det;
			Ret.a13 = (a12 * a13 - a22 * a23) / Det;

			Ret.a21 = (a21 * a33 - a23 * a31) / Det;
			Ret.a22 = (a11 * a33 - a31 * a13) / Det;
			Ret.a23 = (a11 * a23 - a21 * a13) / Det;

			Ret.a31 = (a21 * a22 - a31 * a32) / Det;
			Ret.a32 = (a11 * a32 - a32 * a12) / Det;
			Ret.a33 = (a11 * a22 - a21 * a12) / Det;
		}

		return Ret;
	}

	void Matrix3::CreateTranslation(float x, float y)
	{
		a11 = 1.0f; a12 = 0.0f; a13 = 0.0f;
		a21 = 0.0f; a22 = 1.0f; a23 = 0.0f;
		a31 = x; a32 = y; a33 = 1.0f;
	}

	void Matrix3::CreateScaling(float x, float y)
	{
		a11 = x;    a12 = 0.0f; a13 = 0.0f;
		a21 = 0.0f; a22 = y;    a23 = 0.0f;
		a31 = 0.0f; a32 = 0.0f; a33 = 0.0f;
	}

	void Matrix3::CreateRotation(float Angle)
	{
		const float Cos = std::cos(Angle);
		const float Sin = std::sin(Angle);

		a11 = Cos;  a12 = Sin;  a13 = 0.0f;
		a21 = -Sin; a22 = Cos;  a23 = 0.0f;
		a31 = 0.0f; a32 = 0.0f; a33 = 0.0f;
	}

	void Matrix3::CreateRotation(float Angle, const Vector2& Center)
	{
		Matrix3 Tr1, Tr2, Rot;

		Tr1.CreateTranslation(Center.x, Center.y);
		Tr2.CreateTranslation(-Center.x, -Center.y);
		Rot.CreateRotation(Angle);

		*this = Tr1 * Rot * Tr2;
	}

	void Matrix3::Scale(float x, float y)
	{
		Matrix3 Scale;
		Scale.CreateScaling(x, y);
		*this *= Scale;
	}

	void Matrix3::Translate(float x, float y)
	{
		Matrix3 Tr;
		Tr.CreateTranslation(x, y);
		*this *= Tr;
	}

	void Matrix3::Rotate(float Angle)
	{
		Matrix3 Rot;
		Rot.CreateRotation(Angle);
		*this *= Rot;
	}

	void Matrix3::Rotate(const Vector2& fwd, const Vector2& side)
	{
		const Matrix3 mat;

		a11 = fwd.x;  a12 = fwd.y; 	a13 = 0;
		a21 = side.x; a22 = side.y; 	a23 = 0;
		a31 = 0; 		a32 = 0; 		a33 = 1;

		*this *= mat;
	}

	Vector2 Matrix3::GetTranslation() const
	{
		return {a13, a23};
	}

	Vector3 Matrix3::Transform(const Vector2& v, float w) const
	{
		return {
			v.x * a11 + v.y * a21 + w * a31,
			v.x * a12 + v.y * a22 + w * a32,
			v.x * a13 + v.y * a23 + w * a33
		};
	}

	Vector3 Matrix3::Transform(const Vector3& v) const
	{
		return {
			v.x * a11 + v.y * a21 + v.z * a31,
			v.x * a12 + v.y * a22 + v.z * a32,
			v.x * a13 + v.y * a23 + v.z * a33
		};
	}

	void Matrix3::TransformVectors(std::vector<Vector2>& vPoint_) const
	{
		for (unsigned int i = 0; i < vPoint_.size(); ++i)
		{
			const float tempX = a11 * vPoint_[i].x + a21 * vPoint_[i].y + a31;
			const float tempY = a12 * vPoint_[i].x + a22 * vPoint_[i].y + a32;
			vPoint_[i].x = tempX;
			vPoint_[i].y = tempY;
		}
	}

	void Matrix3::TransformVector(Vector2& vPoint_) const
	{
		const float tempX = a11 * vPoint_.x + a21 * vPoint_.y + a31;
		const float tempY = a12 * vPoint_.x + a22 * vPoint_.y + a32;
		vPoint_.x = tempX;
		vPoint_.y = tempY;
	}

	Matrix3 Matrix3::operator +() const
	{
		return *this;
	}

	Matrix3 Matrix3::operator -() const
	{
		return {
			-a11, -a12, -a13,
			-a21, -a22, -a23,
			-a31, -a32, -a33
		};
	}

	Matrix3 Matrix3::operator +(const Matrix3& m) const
	{
		return {
			a11 + m.a11, a12 + m.a12, a13 + m.a13,
			a21 + m.a21, a22 + m.a22, a23 + m.a23,
			a31 + m.a31, a32 + m.a32, a33 + m.a33
		};
	}

	Matrix3 Matrix3::operator -(const Matrix3& m) const
	{
		return {
			a11 - m.a11, a12 - m.a12, a13 - m.a13,
			a21 - m.a21, a22 - m.a22, a23 - m.a23,
			a31 - m.a31, a32 - m.a32, a33 - m.a33
		};
	}

	const Matrix3& Matrix3::operator +=(const Matrix3& m)
	{
		a11 += m.a11; a12 += m.a12; a13 += m.a13;
		a21 += m.a21; a22 += m.a22; a23 += m.a23;
		a31 += m.a31; a32 += m.a32; a33 += m.a33;

		return *this;
	}

	const Matrix3& Matrix3::operator -=(const Matrix3& m)
	{
		a11 -= m.a11; a12 -= m.a12; a13 -= m.a13;
		a21 -= m.a21; a22 -= m.a22; a23 -= m.a23;
		a31 -= m.a31; a32 -= m.a32; a33 -= m.a33;

		return *this;
	}

	Matrix3 Matrix3::operator *(const Matrix3& m) const
	{
		return {
			a11 * m.a11 + a21 * m.a12 + a31 * m.a13,
			a12 * m.a11 + a22 * m.a12 + a32 * m.a13,
			a13 * m.a11 + a23 * m.a12 + a33 * m.a13,

			a11 * m.a21 + a21 * m.a22 + a31 * m.a23,
			a12 * m.a21 + a22 * m.a22 + a32 * m.a23,
			a13 * m.a21 + a23 * m.a22 + a33 * m.a23,

			a11 * m.a31 + a21 * m.a32 + a31 * m.a33,
			a12 * m.a31 + a22 * m.a32 + a32 * m.a33,
			a13 * m.a31 + a23 * m.a32 + a33 * m.a33
		};
	}

	const Matrix3& Matrix3::operator *=(const Matrix3& m)
	{
		*this = *this * m;
		return *this;
	}

	const Matrix3& Matrix3::operator *=(float t)
	{
		a11 *= t; a12 *= t; a13 *= t;
		a21 *= t; a22 *= t; a23 *= t;
		a31 *= t; a32 *= t; a33 *= t;

		return *this;
	}

	const Matrix3& Matrix3::operator /=(float t)
	{
		a11 /= t; a12 /= t; a13 /= t;
		a21 /= t; a22 /= t; a23 /= t;
		a31 /= t; a32 /= t; a33 /= t;

		return *this;
	}

	bool Matrix3::operator ==(const Matrix3& m) const
	{
		return std::fabs(a11 - m.a11) < std::numeric_limits<float>::epsilon() && std::fabs(a12 - m.a12) < std::numeric_limits<float>::epsilon() &&
			std::fabs(a13 - m.a13) < std::numeric_limits<float>::epsilon() && std::fabs(a21 - m.a21) < std::numeric_limits<float>::epsilon() &&
			std::fabs(a22 - m.a22) < std::numeric_limits<float>::epsilon() && std::fabs(a23 - m.a23) < std::numeric_limits<float>::epsilon() &&
			std::fabs(a31 - m.a31) < std::numeric_limits<float>::epsilon() && std::fabs(a32 - m.a32) < std::numeric_limits<float>::epsilon() &&
			std::fabs(a33 - m.a33) < std::numeric_limits<float>::epsilon();
	}

	bool Matrix3::operator !=(const Matrix3& m) const
	{
		return !(*this == m);
	}

	float& Matrix3::operator ()(std::size_t i, std::size_t j)
	{
		return operator float* ()[i + 3 * j];
	}

	const float& Matrix3::operator ()(std::size_t i, std::size_t j) const
	{
		return operator const float* ()[i + 3 * j];
	}

	Matrix3::operator const float* () const
	{
		return &a11;
	}

	Matrix3::operator float* ()
	{
		return &a11;
	}

	Matrix3 operator *(const Matrix3& m, float t)
	{
		return {
			m.a11 * t, m.a12 * t, m.a13 * t,
			m.a21 * t, m.a22 * t, m.a23 * t,
			m.a31 * t, m.a32 * t, m.a33 * t
		};
	}

	Matrix3 operator *(float t, const Matrix3& m)
	{
		return m * t;
	}

	Matrix3 operator /(const Matrix3& m, float t)
	{
		return {
			m.a11 / t, m.a12 / t, m.a13 / t,
			m.a21 / t, m.a22 / t, m.a23 / t,
			m.a31 / t, m.a32 / t, m.a33 / t
		};
	}
}