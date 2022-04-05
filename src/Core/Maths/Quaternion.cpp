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

	Quaternion::Quaternion(const Matrix4& Matrix)
	{
		FromMatrix(Matrix);
	}

	Quaternion::Quaternion(const Vector3F& Axis, float Angle)
	{
		FromAxisAngle(Axis, Angle);
	}

	float Quaternion::getX() const
	{
		return x;
	}

	float Quaternion::getY() const
	{
		return y;
	}

	float Quaternion::getZ() const
	{
		return z;
	}

	float Quaternion::getW() const
	{
		return w;
	}

	void Quaternion::Identity()
	{
		x = y = z = 0.0f;
		w = 1.0f;
	}

	void Quaternion::Normalize()
	{
		const float Norm = x * x + y * y + z * z + w * w;

		if (std::fabs(Norm) > std::numeric_limits<float>::epsilon())
		{
			x /= Norm;
			y /= Norm;
			z /= Norm;
			w /= Norm;
		}
	}

	Quaternion Quaternion::Conjugate() const
	{
		return {-x, -y, -z, w};
	}

	Matrix3 Quaternion::ToMatrix3() const
	{
		// 	CA_ASSERT(q.IsValid(0.05f), "Quaternion::ToMatrix3()");
		// 	Vector3F v2(x, y, z);
		// 	v2 *= 2.0f;
		// 	float xx=1-v2.x*x;	float yy=v2.y*y;	float xw=v2.x*w;
		// 	float xy=v2.y*x;	float yz=v2.z*y;	float yw=v2.y*w;
		// 	float xz=v2.z*x;	float zz=v2.z*z;	float zw=v2.z*w;
		// 	m00=1.0f-yy-zz;		m01=xy-zw;			m02=xz+yw;
		// 	m10=xy+zw;			m11=xx-zz;			m12=yz-xw;
		// 	m20=xz-yw;			m21=yz+xw;			m22=xx-yy;

		const float xx = x * x;
		const float xy = x * y;
		const float xz = x * z;
		const float xw = x * w;
		const float yy = y * y;
		const float yz = y * z;
		const float yw = y * w;
		const float zz = z * z;
		const float zw = z * w;

		return {
			1.0f - 2.0f * (yy + zz), 2.0f * (xy - zw), 2.0f * (xy + yw),
			2.0f * (xy + zw), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - xw),
			2.0f * (xz - yw), 2.0f * (yz + xw), 1.0f - 2.0f * (xx + yy)
		};
	}

	Matrix4 Quaternion::ToMatrix4() const
	{
		const float xx = x * x;
		const float xy = x * y;
		const float xz = x * z;
		const float xw = x * w;
		const float yy = y * y;
		const float yz = y * z;
		const float yw = y * w;
		const float zz = z * z;
		const float zw = z * w;

		return {
			1 - 2 * (yy + zz), 2 * (xy - zw), 2 * (xy + yw), 0,
			2 * (xy + zw), 1 - 2 * (xx + zz), 2 * (yz - xw), 0,
			2 * (xz - yw), 2 * (yz + xw), 1 - 2 * (xx + yy), 0,
			0, 0, 0, 1
		};
	}

	void Quaternion::FromMatrix(const Matrix4& matrix)
	{
		const float Trace = matrix(0, 0) + matrix(1, 1) + matrix(2, 2) + 1;

		if (Trace > 0)
		{
			const float s = 0.5f / std::sqrt(Trace);
			x = (matrix(2, 1) - matrix(1, 2)) * s;
			y = (matrix(0, 2) - matrix(2, 0)) * s;
			z = (matrix(1, 0) - matrix(0, 1)) * s;
			w = 0.25f / s;
		}
		else
		{
			if (matrix(0, 0) > matrix(1, 1) && (matrix(0, 0) > matrix(2, 2)))
			{
				const float s = std::sqrt(1 + matrix(0, 0) - matrix(1, 1) - matrix(2, 2)) * 2;
				x = 0.5f / s;
				y = (matrix(0, 1) + matrix(1, 0)) / s;
				z = (matrix(0, 2) + matrix(2, 0)) / s;
				w = (matrix(1, 2) + matrix(2, 1)) / s;
			}
			else if (matrix(1, 1) > matrix(2, 2))
			{
				const float s = std::sqrt(1 - matrix(0, 0) + matrix(1, 1) - matrix(2, 2)) * 2;
				x = (matrix(0, 1) + matrix(1, 0)) / s;
				y = 0.5f / s;
				z = (matrix(1, 2) + matrix(2, 1)) / s;
				w = (matrix(0, 2) + matrix(2, 0)) / s;
			}
			else
			{
				const float s = std::sqrt(1 - matrix(0, 0) - matrix(1, 1) + matrix(2, 2)) * 2;
				x = (matrix(0, 2) + matrix(2, 0)) / s;
				y = (matrix(1, 2) + matrix(2, 1)) / s;
				z = 0.5f / s;
				w = (matrix(0, 1) + matrix(1, 0)) / s;
			}
		}
	}

	void Quaternion::FromAxisAngle(const Vector3F& Axis, float Angle)
	{
		const float Cos = std::cos(Angle / 2);
		const float Sin = std::sin(Angle / 2);

		x = Axis.x * Sin;
		y = Axis.y * Sin;
		z = Axis.z * Sin;
		w = Cos;

		Normalize();
	}

	void Quaternion::ToAxisAngle(Vector3F& Axis, float& Angle) const
	{
		Angle = std::acos(w) * 2;

		const float Norm = std::sqrt(x * x + y * y + z * z);
		if (std::fabs(Norm) > std::numeric_limits<float>::epsilon())
		{
			Axis.x = x / Norm;
			Axis.y = y / Norm;
			Axis.z = z / Norm;
		}
		else
		{
			Axis.x = 0.0f;
			Axis.y = 1.0f;
			Axis.z = 0.0f;
		}
	}

	void Quaternion::Transform(const Vector3F& value, Vector3F& result) const
	{
		const float x1 = 2 * (y * value.z - z * value.y);
		const float y1 = 2 * (z * value.x - x * value.z);
		const float z1 = 2 * (x * value.y - y * value.x);

		result.x = value.x + x1 * w + (y * z1 - z * y1);
		result.y = value.y + y1 * w + (z * x1 - x * z1);
		result.z = value.z + z1 * w + (x * y1 - y * x1);
	}

	void Quaternion::Transform(const std::vector<Vector3F>& sourceArray, std::vector<Vector3F>& destinationArray) const
	{
		CA_ASSERT(destinationArray.size() >= sourceArray.size(), "The destination array is smaller than the source array.");

		int i = 0;

		for (auto it = sourceArray.cbegin();
		     it != sourceArray.cend();
		     ++it)
		{
			const Vector3F position = *it;

			const float x1 = 2 * (y * position.z - z * position.y);
			const float y1 = 2 * (z * position.x - x * position.z);
			const float z1 = 2 * (x * position.y - y * position.x);

			destinationArray[i] = Vector3F(
				position.x + x1 * w + (y * z1 - z * y1),
				position.y + y1 * w + (z * x1 - x * z1),
				position.z + z1 * w + (x * y1 - y * x1));
			i++;
		}
	}

	void Quaternion::CreateFromYawPitchRoll(float X, float Y, float Z)
	{
		const Quaternion Qx(Vector3F(1, 0, 0), X);
		const Quaternion Qy(Vector3F(0, 1, 0), Y);
		const Quaternion Qz(Vector3F(0, 0, 1), Z);

		*this = Qx * Qy * Qz;
	}

	Quaternion Quaternion::operator *(const Quaternion& quat_) const
	{
		return {
			w * quat_.x + x * quat_.w + y * quat_.z - z * quat_.y,
			w * quat_.y + y * quat_.w + z * quat_.x - x * quat_.z,
			w * quat_.z + z * quat_.w + x * quat_.y - y * quat_.x,
			w * quat_.w - x * quat_.x - y * quat_.y - z * quat_.z
		};
	}

	const Quaternion& Quaternion::operator *=(const Quaternion& q_)
	{
		*this = *this * q_;

		return *this;
	}

	std::istream& operator >>(std::istream& Stream, Quaternion& q_)
	{
		return Stream >> q_.x >> q_.y >> q_.z >> q_.w;
	}

	std::ostream& operator <<(std::ostream& Stream, const Quaternion& Quaternion)
	{
		return Stream << Quaternion.x << " " << Quaternion.y << " " << Quaternion.z << " " << Quaternion.w;
	}
}