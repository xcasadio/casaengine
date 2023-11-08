#pragma once

#include "CA_Export.hpp"

#include  "Maths/Vector2.hpp"
#include  "Maths/Vector3.hpp"

namespace CasaEngine
{
	class CA_EXPORT Matrix3
	{
	public:
		float a11, a21, a31;
		float a12, a22, a32;
		float a13, a23, a33;

		Matrix3(float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f,
			float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f,
			float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f);

		void Identity();
		float Determinant() const;
		Matrix3 Transpose() const;
		Matrix3 Inverse() const;

		void CreateTranslation(float x, float y);
		void CreateScaling(float x, float y);
		void CreateRotation(float Angle);
		void CreateRotation(float Angle, const Vector2& Center);
		void Translate(float x, float y);
		void Scale(float x, float y);
		void Rotate(float Angle);
		void Rotate(const Vector2& fwd, const Vector2& side);
		Vector2 GetTranslation() const;

		Vector3 Transform(const Vector2& v, float w = 1.0f) const;
		Vector3 Transform(const Vector3& v) const;
		void TransformVectors(std::vector<Vector2>& vPoint_) const;
		void TransformVector(Vector2& vPoint) const;

		Matrix3 operator +() const;
		Matrix3 operator -() const;
		Matrix3 operator +(const Matrix3& m) const;
		Matrix3 operator -(const Matrix3& m) const;
		const Matrix3& operator +=(const Matrix3& m);
		const Matrix3& operator -=(const Matrix3& m);
		Matrix3 operator *(const Matrix3& m) const;
		const Matrix3& operator *=(const Matrix3& m);
		const Matrix3& operator *=(float t);
		const Matrix3& operator /=(float t);
		bool operator ==(const Matrix3& m) const;
		bool operator !=(const Matrix3& m) const;
		float& operator ()(std::size_t i, std::size_t j);
		const float& operator ()(std::size_t i, std::size_t j) const;
		operator float* ();
		operator const float* () const;
	};

	Matrix3      operator * (const Matrix3& m, float t);
	Matrix3      operator * (float t, const Matrix3& m);
	Matrix3      operator / (const Matrix3& m, float t);
}
