#include  "Plane.hpp"

namespace CasaEngine
{
	Plane::Plane(float A, float B, float C, float D) :
		n(A, B, C),
		d(D)
	{
	}

	Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) :
		n(0, 0, 0),
		d(0)
	{
		BuildFromPoints(v0, v1, v2);
	}

	Plane::Plane(const Vector3& Normal, const Vector3& Point) :
		n(Normal),
		d(Point.Length())
	{
	}

	Plane::Plane(const Vector3& Normal, float Point) :
		n(Normal),
		d(Point)
	{
	}

	void Plane::BuildFromPoints(const Vector3& v0, const Vector3& v1, const Vector3& v2)
	{
		n = Vector3::Cross(v1 - v0, v2 - v0);
		n.Normalize();

		d = -Vector3::Dot(n, v0);
	}

	float Plane::DistanceToPoint(const Vector3& Point) const
	{
		return Vector3::Dot(n, Point) + d;
	}

	float Plane::DistanceToPoint(const Vector4& Point) const
	{
		return n.x * Point.x + n.y * Point.y + n.z * Point.z + d * Point.w;
	}

	bool Plane::IntersectLine(const Vector3& p1_, const Vector3& p2_, Vector3* pOut_)
	{
		Vector3 out;
		Vector3 direction, normal;
		float dot, temp;

		normal.x = n.x;
		normal.y = n.y;
		normal.z = n.z;
		direction.x = p2_.x - p1_.x;
		direction.y = p2_.y - p1_.y;
		direction.z = p2_.z - p1_.z;

		dot = Vector3::Dot(normal, direction);

		if (!dot)
		{
			return false;
		}

		temp = (d + Vector3::Dot(normal, p1_)) / dot;

		pOut_->x = p1_.x - temp * direction.x;
		pOut_->y = p1_.y - temp * direction.y;
		pOut_->z = p1_.z - temp * direction.z;

		return true;
	}

	Plane Plane::Normalize(Plane p)
	{
		p.Normalize();
		return p;
	}

	void Plane::Normalize()
	{
		float length = n.Length();
		float factor = 1.0f / length;
		n *= factor;
		d *= factor;
	}

	float Plane::DotNormal(Plane plane, Vector3 value)
	{
		return Vector3::Dot(plane.n, value);
		//return plane.Normal.X * value.X +
		//		plane.Normal.Y * value.Y +
		//		plane.Normal.Z * value.Z;
	}

	bool Plane::operator ==(const Plane& p) const
	{
		return n == p.n && fabs(d - p.d) <= std::numeric_limits<float>::epsilon();
	}

	bool Plane::operator !=(const Plane& p) const
	{
		return !(*this == p);
	}
}

