#ifndef QUATERNION_H
#define QUATERNION_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "Memory/MemoryAllocation.h"
#include "Matrix3.h"

namespace CasaEngine
{
	class CA_EXPORT Quaternion :
		public AllocatedObject<Quaternion>
	{
	public:
		Quaternion(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 1.0f);
		Quaternion(const Matrix4& Matrix);
		Quaternion(const Vector3F& Axis, float Angle);

		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

		void Identity();
		void Normalize();

		Quaternion Conjugate() const;

		Matrix3 ToMatrix3() const;
		Matrix4 ToMatrix4() const;

		void FromMatrix(const Matrix4& matrix);
		void FromAxisAngle(const Vector3F& Axis, float Angle);
		void ToAxisAngle(Vector3F& Axis, float& Angle) const;

		void Transform(const Vector3F& value, Vector3F& result) const;
		void Transform(const std::vector<Vector3F>& sourceArray, std::vector<Vector3F>& destinationArray) const;

		void CreateFromYawPitchRoll(float X, float Y, float Z);

		Quaternion operator *(const Quaternion& q_) const;
		const Quaternion& operator *=(const Quaternion& q_);

		float x{};
		float y{};
		float z{};
		float w{};
	};

	std::istream& operator >>(std::istream& Stream, Quaternion& Quaternion);
	std::ostream& operator <<(std::ostream& Stream, const Quaternion& Quaternion);
}

#endif
