#pragma once

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "Matrix3.h"

namespace CasaEngine
{
	class CA_EXPORT Quaternion
	{
	public:
		Quaternion(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 1.0f);
		Quaternion(const Matrix4& matrix);
		Quaternion(const Vector3& axis, float angle);

		float GetX() const;
		float GetY() const;
		float GetZ() const;
		float GetW() const;

		static Quaternion Zero();

		static Quaternion CreateIdentity();
		void Identity();
		bool IsIdentity() const;
		void Normalize();
		static Quaternion Normalize(const Quaternion& q);
		static Quaternion Inverse(const Quaternion& value);

		static Quaternion Conjugate(const Quaternion &q);
		static float Dot(const Quaternion& q1, const Quaternion& q2);
		static Quaternion Lerp(Quaternion quaternion1, Quaternion quaternion2, float amount);
		static Quaternion Slerp(Quaternion quaternion1, Quaternion quaternion2, float amount);
		static Quaternion Concatenate(const Quaternion &value1, const Quaternion &value2);

		float Length() const;
		float LengthSquared() const;

		Matrix3 ToMatrix3() const;
		Matrix4 ToMatrix4() const;

		static Quaternion CreateFromRotationMatrix(const Matrix4& matrix);
		void FromMatrix(const Matrix4& matrix);
		static Quaternion CreateFromAxisAngle(const Vector3& axis, float angle);
		void FromAxisAngle(const Vector3& axis, float angle);
		void ToAxisAngle(Vector3& axis, float& angle) const;

		Vector3 Transform(const Vector3& value) const;
		void Transform(const Vector3& value, Vector3& result) const;
		void Transform(const std::vector<Vector3>& sourceArray, std::vector<Vector3>& destinationArray) const;

		static Quaternion CreateFromYawPitchRoll(float X, float Y, float Z);
		void FromYawPitchRoll(float yawAngle, float pitchAngle, float rollAngle);

		static Quaternion Negate(const Quaternion& q);
		static Quaternion Add(const Quaternion& value1, const Quaternion& value2);
		static Quaternion Subtract(Quaternion value1, Quaternion value2);
		static Quaternion Multiply(const Quaternion& value1, const Quaternion& value2);
		static Quaternion Divide(const Quaternion& value1, const Quaternion& value2);

		static Quaternion Multiply(Quaternion value1, float value2);

		Quaternion operator +() const;
		Quaternion operator -() const;
		Quaternion operator +(const Quaternion& quat) const;
		const Quaternion& operator +=(const Quaternion& quat);
		Quaternion operator -(const Quaternion& quat) const;
		const Quaternion& operator -=(const Quaternion& quat);
		Quaternion operator /(const Quaternion& quat) const;
		const Quaternion& operator /=(const Quaternion& quat);
		Quaternion operator *(const Quaternion& quat) const;
		const Quaternion& operator *=(const Quaternion& quat);
		Quaternion operator *(float f) const;
		const Quaternion& operator *=(float f);

		bool operator ==(const Quaternion& v) const;
		bool operator !=(const Quaternion& v) const;

		float x{};
		float y{};
		float z{};
		float w{};
	};

	std::istream& operator >>(std::istream& stream, Quaternion& quat);
	std::ostream& operator <<(std::ostream& stream, const Quaternion& quat);
}
