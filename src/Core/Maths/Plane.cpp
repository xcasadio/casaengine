#include "Plane.h"

namespace CasaEngine
{
	inline Plane::Plane(float A, float B, float C, float D) :
		n(A, B, C),
		d(D)
	{
	}

	inline Plane::Plane(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2)
	{
		BuildFromPoints(v0, v1, v2);
	}

	inline Plane::Plane(const Vector3F& Normal, const Vector3F& Point) :
		n(Normal),
		d(Point.Length())
	{
	}

	inline void Plane::BuildFromPoints(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2)
	{
		// Calcul de la normale du plan
		n = Vector3F::Cross(v1 - v0, v2 - v0);
		n.Normalize();

		// Calcul de la distance � l'origine
		d = -Vector3F::Dot(n, v0);
	}

	inline float Plane::DistanceToPoint(const Vector3F& Point) const
	{
		return Vector3F::Dot(n, Point) + d;
	}

	inline float Plane::DistanceToPoint(const Vector4F& Point) const
	{
		return n.x * Point.x + n.y * Point.y + n.z * Point.z + d * Point.w;
	}

	inline bool Plane::IntersectLine(const Vector3F& p1_, const Vector3F& p2_, Vector3F* pOut_)
	{
		Vector3F out;
		Vector3F direction, normal;
		float dot, temp;

		normal.x = n.x;
		normal.y = n.y;
		normal.z = n.z;
		direction.x = p2_.x - p1_.x;
		direction.y = p2_.y - p1_.y;
		direction.z = p2_.z - p1_.z;

		dot = Vector3F::Dot(normal, direction);

		if (!dot) return false;

		temp = (d + Vector3F::Dot(normal, p1_)) / dot;

		pOut_->x = p1_.x - temp * direction.x;
		pOut_->y = p1_.y - temp * direction.y;
		pOut_->z = p1_.z - temp * direction.z;

		return true;
	}

	void Plane::Normalize()
	{
		float length = n.Length();
		float factor = 1.0f / length;
		n *= factor;
		d *= factor;
	}

	inline bool Plane::operator ==(const Plane& p) const
	{
		return n == p.n && fabs(d - p.d) <= std::numeric_limits<float>::epsilon();
	}

	inline bool Plane::operator !=(const Plane& p) const
	{
		return !(*this == p);
	}

	inline std::istream& operator >>(std::istream& Stream, Plane& Plane)
	{
		return Stream >> Plane.n >> Plane.d;
	}

	inline std::ostream& operator <<(std::ostream& Stream, const Plane& Plane)
	{
		return Stream << Plane.n << " " << Plane.d;
	}
}
