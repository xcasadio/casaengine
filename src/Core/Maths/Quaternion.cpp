#include "Base.h"
#include "Log/LogManager.h"

#include "Maths/Quaternion.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "CA_Assert.h"

namespace CasaEngine
{
	Quaternion::Quaternion(float X, float Y, float Z, float W) :
		x(X),
		y(Y),
		z(Z),
		w(W)
	{
	}

	Quaternion::Quaternion(const Matrix4& matrix)
	{
		FromMatrix(matrix);
	}

	Quaternion::Quaternion(const Vector3& axis, float angle) :
		Quaternion(axis.x, axis.y, axis.z, angle)
	{
		//FromAxisAngle(axis, angle);
	}

	float Quaternion::GetX() const
	{
		return x;
	}

	float Quaternion::GetY() const
	{
		return y;
	}

	float Quaternion::GetZ() const
	{
		return z;
	}

	float Quaternion::GetW() const
	{
		return w;
	}

	Quaternion Quaternion::Zero()
	{
		return { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	Quaternion Quaternion::CreateIdentity()
	{
		Quaternion q;
		q.Identity();
		return q;
	}

	void Quaternion::Identity()
	{
		x = y = z = 0.0f;
		w = 1.0f;
	}

	bool Quaternion::IsIdentity() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f;
	}

	void Quaternion::Normalize()
	{
		*this = Normalize(*this);
	}

	Quaternion Quaternion::Normalize(const Quaternion& q)
	{
		Quaternion result;
		const float ls = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
		float invNorm = 1.0f / sqrtf(ls);

		//if (std::fabs(Norm) > Epsilon)
		{
			result.x = q.x * invNorm;
			result.y = q.y * invNorm;
			result.z = q.z * invNorm;
			result.w = q.w * invNorm;
		}

		return result;
	}

	Quaternion Quaternion::Inverse(const Quaternion& value)
	{
		//  -1   (       a              -v       )
		// q   = ( -------------   ------------- )
		//       (  a^2 + |v|^2  ,  a^2 + |v|^2  )

		Quaternion ans;

		float ls = value.x * value.x + value.y * value.y + value.z * value.z + value.w * value.w;
		float invNorm = 1.0f / ls;

		ans.x = -value.x * invNorm;
		ans.y = -value.y * invNorm;
		ans.z = -value.z * invNorm;
		ans.w = value.w * invNorm;

		return ans;
	}

	float Quaternion::Dot(const Quaternion& q1, const Quaternion& q2)
	{
		return q1.x * q2.x +
			q1.y * q2.y +
			q1.z * q2.z +
			q1.w * q2.w;
	}

	Quaternion Quaternion::Conjugate(const Quaternion& q)
	{
		return { -q.x, -q.y, -q.z, q.w };
	}

	Quaternion Quaternion::Lerp(Quaternion quaternion1, Quaternion quaternion2, float amount)
	{
		float t = amount;
		float t1 = 1.0f - t;

		Quaternion r;

		float dot = quaternion1.x * quaternion2.x + quaternion1.y * quaternion2.y +
			quaternion1.z * quaternion2.z + quaternion1.w * quaternion2.w;

		if (dot >= 0.0f)
		{
			r.x = t1 * quaternion1.x + t * quaternion2.x;
			r.y = t1 * quaternion1.y + t * quaternion2.y;
			r.z = t1 * quaternion1.z + t * quaternion2.z;
			r.w = t1 * quaternion1.w + t * quaternion2.w;
		}
		else
		{
			r.x = t1 * quaternion1.x - t * quaternion2.x;
			r.y = t1 * quaternion1.y - t * quaternion2.y;
			r.z = t1 * quaternion1.z - t * quaternion2.z;
			r.w = t1 * quaternion1.w - t * quaternion2.w;
		}

		// normalize it.
		float ls = r.x * r.x + r.y * r.y + r.z * r.z + r.w * r.w;
		float invNorm = 1.0f / sqrtf(ls);

		r.x *= invNorm;
		r.y *= invNorm;
		r.z *= invNorm;
		r.w *= invNorm;

		return r;
	}

	Quaternion Quaternion::Slerp(Quaternion quaternion1, Quaternion quaternion2, float amount)
	{
		constexpr float epsilon = 1e-6f;

		float t = amount;

		float cosOmega = quaternion1.x * quaternion2.x + quaternion1.y * quaternion2.y +
			quaternion1.z * quaternion2.z + quaternion1.w * quaternion2.w;

		bool flip = false;

		if (cosOmega < 0.0f)
		{
			flip = true;
			cosOmega = -cosOmega;
		}

		float s1, s2;

		if (cosOmega > (1.0f - epsilon))
		{
			// Too close, do straight linear interpolation.
			s1 = 1.0f - t;
			s2 = (flip) ? -t : t;
		}
		else
		{
			float omega = acosf(cosOmega);
			float invSinOmega = 1.0f / sinf(omega);

			s1 = sinf((1.0f - t) * omega) * invSinOmega;
			s2 = (flip)
				? -sinf(t * omega) * invSinOmega
				: sinf(t * omega) * invSinOmega;
		}

		Quaternion ans;

		ans.x = s1 * quaternion1.x + s2 * quaternion2.x;
		ans.y = s1 * quaternion1.y + s2 * quaternion2.y;
		ans.z = s1 * quaternion1.z + s2 * quaternion2.z;
		ans.w = s1 * quaternion1.w + s2 * quaternion2.w;

		return ans;
	}

	Quaternion Quaternion::Concatenate(const Quaternion& value1, const Quaternion& value2)
	{
		Quaternion ans;

		// Concatenate rotation is actually q2 * q1 instead of q1 * q2.
		// So that's why value2 goes q1 and value1 goes q2.
		float q1x = value2.x;
		float q1y = value2.y;
		float q1z = value2.z;
		float q1w = value2.w;

		float q2x = value1.x;
		float q2y = value1.y;
		float q2z = value1.z;
		float q2w = value1.w;

		// cross(av, bv)
		float cx = q1y * q2z - q1z * q2y;
		float cy = q1z * q2x - q1x * q2z;
		float cz = q1x * q2y - q1y * q2x;

		float dot = q1x * q2x + q1y * q2y + q1z * q2z;

		ans.x = q1x * q2w + q2x * q1w + cx;
		ans.y = q1y * q2w + q2y * q1w + cy;
		ans.z = q1z * q2w + q2z * q1w + cz;
		ans.w = q1w * q2w - dot;

		return ans;
	}

	float Quaternion::Length() const
	{
		float ls = x * x + y * y + z * z + w * w;

		return sqrtf(ls);
	}

	float Quaternion::LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	Quaternion Quaternion::CreateFromRotationMatrix(const Matrix4& matrix)
	{
		Quaternion q;
		q.FromMatrix(matrix);
		return q;
	}

	void Quaternion::FromMatrix(const Matrix4& matrix)
	{
		float trace = matrix.m11 + matrix.m22 + matrix.m33;

		if (trace > 0.0f)
		{
			float s = sqrtf(trace + 1.0f);
			w = s * 0.5f;
			s = 0.5f / s;
			x = (matrix.m23 - matrix.m32) * s;
			y = (matrix.m31 - matrix.m13) * s;
			z = (matrix.m12 - matrix.m21) * s;
		}
		else if (matrix.m11 > matrix.m22 && matrix.m11 > matrix.m33)
		{
			float s = sqrtf(1.0f + matrix.m11 - matrix.m22 - matrix.m33);
			float invS = 0.5f / s;
			x = 0.5f * s;
			y = (matrix.m12 + matrix.m21) * invS;
			z = (matrix.m13 + matrix.m31) * invS;
			w = (matrix.m23 - matrix.m32) * invS;
		}
		else if (matrix.m22 > matrix.m33)
		{
			float s = sqrtf(1.0f + matrix.m22 - matrix.m11 - matrix.m33);
			float invS = 0.5f / s;
			x = (matrix.m21 + matrix.m12) * invS;
			y = 0.5f * s;
			z = (matrix.m32 + matrix.m23) * invS;
			w = (matrix.m31 - matrix.m13) * invS;
		}
		else
		{
			float s = sqrtf(1.0f + matrix.m33 - matrix.m11 - matrix.m22);
			float invS = 0.5f / s;
			x = (matrix.m31 + matrix.m13) * invS;
			y = (matrix.m32 + matrix.m23) * invS;
			z = 0.5f * s;
			w = (matrix.m12 - matrix.m21) * invS;
		}


		float num8 = (matrix.m11 + matrix.m22) + matrix.m33;
		Quaternion quaternion;
		if (num8 > 0.0f)
		{
			float num = sqrtf(num8 + 1.0f);
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = -(matrix.m23 - matrix.m32) * num; // -
			quaternion.y = -(matrix.m31 - matrix.m13) * num; // -
			quaternion.z = -(matrix.m12 - matrix.m21) * num; // -
		}
		else if ((matrix.m11 >= matrix.m22) && (matrix.m11 >= matrix.m33))
		{
			float num7 = sqrtf(1.0 + matrix.m11 - matrix.m22 - matrix.m33);
			float num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = (matrix.m12 + matrix.m21) * num4;
			quaternion.z = (matrix.m13 + matrix.m31) * num4;
			quaternion.w = -(matrix.m23 - matrix.m32) * num4; // -
		}
		else if (matrix.m22 > matrix.m33)
		{
			float num6 = sqrtf(1.0 + matrix.m22 - matrix.m11 - matrix.m33);
			float num3 = 0.5f / num6;
			quaternion.x = (matrix.m21 + matrix.m12) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = (matrix.m32 + matrix.m23) * num3;
			quaternion.w = -(matrix.m31 - matrix.m13) * num3; // -
		}
		else
		{
			float num5 = sqrtf(1.0 + matrix.m33 - matrix.m11 - matrix.m22);
			float num2 = 0.5f / num5;
			quaternion.x = (matrix.m31 + matrix.m13) * num2;
			quaternion.y = (matrix.m32 + matrix.m23) * num2;
			quaternion.z = 0.5f * num5;
			quaternion.w = -(matrix.m12 - matrix.m21) * num2; // -
		}

		*this = quaternion;
	}

	Quaternion Quaternion::CreateFromAxisAngle(const Vector3& axis, float angle)
	{
		Quaternion q;
		q.FromAxisAngle(axis, angle);
		return q;
	}

	void Quaternion::FromAxisAngle(const Vector3& axis, float angle)
	{
		float halfAngle = angle * 0.5f;
		const float Cos = std::cosf(halfAngle);
		const float Sin = std::sinf(halfAngle);

		x = axis.x * Sin;
		y = axis.y * Sin;
		z = axis.z * Sin;
		w = Cos;
	}

	void Quaternion::ToAxisAngle(Vector3& axis, float& angle) const
	{
		angle = std::acosf(w) * 2;

		const float Norm = std::sqrtf(x * x + y * y + z * z);
		if (std::fabs(Norm) > Epsilon)
		{
			axis.x = x / Norm;
			axis.y = y / Norm;
			axis.z = z / Norm;
		}
		else
		{
			axis.x = 0.0f;
			axis.y = 1.0f;
			axis.z = 0.0f;
		}
	}

	Vector3 Quaternion::Transform(const Vector3& value) const
	{
		Vector3 result;
		Transform(value, result);
		return result;
	}

	void Quaternion::Transform(const Vector3& value, Vector3& result) const
	{
		const float x1 = 2 * (y * value.z - z * value.y);
		const float y1 = 2 * (z * value.x - x * value.z);
		const float z1 = 2 * (x * value.y - y * value.x);

		result.x = value.x + x1 * w + (y * z1 - z * y1);
		result.y = value.y + y1 * w + (z * x1 - x * z1);
		result.z = value.z + z1 * w + (x * y1 - y * x1);
	}

	void Quaternion::Transform(const std::vector<Vector3>& sourceArray, std::vector<Vector3>& destinationArray) const
	{
		CA_ASSERT(destinationArray.size() >= sourceArray.size(), "The destination array is smaller than the source array.");

		int i = 0;

		for (auto it = sourceArray.cbegin();
			it != sourceArray.cend();
			++it)
		{
			const Vector3 position = *it;

			const float x1 = 2 * (y * position.z - z * position.y);
			const float y1 = 2 * (z * position.x - x * position.z);
			const float z1 = 2 * (x * position.y - y * position.x);

			destinationArray[i] = Vector3(
				position.x + x1 * w + (y * z1 - z * y1),
				position.y + y1 * w + (z * x1 - x * z1),
				position.z + z1 * w + (x * y1 - y * x1));
			i++;
		}
	}

	Quaternion Quaternion::CreateFromYawPitchRoll(float X, float Y, float Z)
	{
		Quaternion q;
		q.FromYawPitchRoll(X, Y, Z);
		return q;
	}

	void Quaternion::FromYawPitchRoll(float yawAngle, float pitchAngle, float rollAngle)
	{
		const Quaternion Qx = CreateFromAxisAngle(Vector3::UnitY(), yawAngle);
		const Quaternion Qy = CreateFromAxisAngle(Vector3::UnitX(), pitchAngle);
		const Quaternion Qz = CreateFromAxisAngle(Vector3::UnitZ(), rollAngle);

		*this = Qx * Qy * Qz;
	}

	Quaternion Quaternion::Negate(const Quaternion& q)
	{
		return { -q.x, -q.y, -q.z, -q.w };
	}

	Quaternion Quaternion::Add(const Quaternion& value1, const Quaternion& value2)
	{
		Quaternion ans;

		ans.x = value1.x + value2.x;
		ans.y = value1.y + value2.y;
		ans.z = value1.z + value2.z;
		ans.w = value1.w + value2.w;

		return ans;
	}

	Quaternion Quaternion::Subtract(Quaternion value1, Quaternion value2)
	{
		Quaternion ans;

		ans.x = value1.x - value2.x;
		ans.y = value1.y - value2.y;
		ans.z = value1.z - value2.z;
		ans.w = value1.w - value2.w;

		return ans;
	}

	Quaternion Quaternion::Multiply(const Quaternion& value1, const Quaternion& value2)
	{
		Quaternion ans;

		float q1x = value1.x;
		float q1y = value1.y;
		float q1z = value1.z;
		float q1w = value1.w;

		float q2x = value2.x;
		float q2y = value2.y;
		float q2z = value2.z;
		float q2w = value2.w;

		// cross(av, bv)
		float cx = q1y * q2z - q1z * q2y;
		float cy = q1z * q2x - q1x * q2z;
		float cz = q1x * q2y - q1y * q2x;

		float dot = q1x * q2x + q1y * q2y + q1z * q2z;

		ans.x = q1x * q2w + q2x * q1w + cx;
		ans.y = q1y * q2w + q2y * q1w + cy;
		ans.z = q1z * q2w + q2z * q1w + cz;
		ans.w = q1w * q2w - dot;

		return ans;
	}

	Quaternion Quaternion::operator *(const Quaternion& quat) const
	{
		return Multiply(*this, quat);
	}

	const Quaternion& Quaternion::operator *=(const Quaternion& quat)
	{
		*this = Multiply(*this, quat);
		return *this;
	}

	Quaternion Quaternion::operator*(float f) const
	{
		return Multiply(*this, f);
	}

	const Quaternion& Quaternion::operator*=(float f)
	{
		*this = Multiply(*this, f);
		return *this;
	}

	Quaternion Quaternion::Divide(const Quaternion& value1, const Quaternion& value2)
	{
		Quaternion ans;

		float q1x = value1.x;
		float q1y = value1.y;
		float q1z = value1.z;
		float q1w = value1.w;

		//-------------------------------------
		// Inverse part.
		float ls = value2.x * value2.x + value2.y * value2.y +
			value2.z * value2.z + value2.w * value2.w;
		float invNorm = 1.0f / ls;

		float q2x = -value2.x * invNorm;
		float q2y = -value2.y * invNorm;
		float q2z = -value2.z * invNorm;
		float q2w = value2.w * invNorm;

		//-------------------------------------
		// Multiply part.

		// cross(av, bv)
		float cx = q1y * q2z - q1z * q2y;
		float cy = q1z * q2x - q1x * q2z;
		float cz = q1x * q2y - q1y * q2x;

		float dot = q1x * q2x + q1y * q2y + q1z * q2z;

		ans.x = q1x * q2w + q2x * q1w + cx;
		ans.y = q1y * q2w + q2y * q1w + cy;
		ans.z = q1z * q2w + q2z * q1w + cz;
		ans.w = q1w * q2w - dot;

		return ans;
	}

	Quaternion Quaternion::Multiply(Quaternion value1, float value2)
	{
		Quaternion ans;

		ans.x = value1.x * value2;
		ans.y = value1.y * value2;
		ans.z = value1.z * value2;
		ans.w = value1.w * value2;

		return ans;
	}

	Quaternion Quaternion::operator+() const
	{
		return *this;
	}

	Quaternion Quaternion::operator-() const
	{
		return Negate(*this);
	}

	Quaternion Quaternion::operator+(const Quaternion& quat) const
	{
		return Add(*this, quat);
	}

	const Quaternion& Quaternion::operator+=(const Quaternion& quat)
	{
		*this = Add(*this, quat);
		return *this;
	}

	Quaternion Quaternion::operator-(const Quaternion& quat) const
	{
		return Subtract(*this, quat);
	}

	const Quaternion& Quaternion::operator-=(const Quaternion& quat)
	{
		*this = Subtract(*this, quat);
		return *this;
	}

	Quaternion Quaternion::operator/(const Quaternion& quat) const
	{
		return Divide(*this, quat);
	}

	const Quaternion& Quaternion::operator/=(const Quaternion& quat)
	{
		*this = Divide(*this, quat);
		return *this;
	}

	bool Quaternion::operator==(const Quaternion& v) const
	{
		return std::fabs(x - v.x) <= Epsilon &&
			std::fabs(y - v.y) <= Epsilon &&
			std::fabs(z - v.z) <= Epsilon &&
			std::fabs(w - v.w) <= Epsilon;
	}

	bool Quaternion::operator!=(const Quaternion& v) const
	{
		return !(*this == v);
	}
}