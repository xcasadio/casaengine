#ifndef PLANE_H
#define PLANE_H

#include <Maths/Vector3.h>
#include <Maths/Vector4.h>

namespace CasaEngine
{
	class Plane
	{
	public:
		Plane(float A = 0.0f, float B = 0.0f, float C = 0.0f, float D = 0.0f);
		Plane(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2);
		Plane(const Vector3F& Normal, const Vector3F& Point);

		void BuildFromPoints(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2);
		float DistanceToPoint(const Vector3F& Point) const;
		float DistanceToPoint(const Vector4F& Point) const;
		bool IntersectLine(const Vector3F& p1_, const Vector3F& p2_, Vector3F* pOut_);

		void Normalize();

		bool operator ==(const Plane& p) const;
		bool operator !=(const Plane& p) const;

		Vector3F n;
		float    d;
	};

	std::istream& operator >>(std::istream& Stream, Plane& Plane);
	std::ostream& operator <<(std::ostream& Stream, const Plane& Plane);
}

#endif
