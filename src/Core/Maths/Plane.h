#pragma once

#include <Maths/Vector3.h>
#include <Maths/Vector4.h>

namespace CasaEngine
{
	class Plane
	{
	public:
		explicit Plane(float A, float B, float C, float D);
		explicit Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2);
		explicit Plane(const Vector3& Normal, const Vector3& Point);
		explicit Plane(const Vector3& Normal, float Point);

		void BuildFromPoints(const Vector3& v0, const Vector3& v1, const Vector3& v2);
		float DistanceToPoint(const Vector3& Point) const;
		float DistanceToPoint(const Vector4& Point) const;
		bool IntersectLine(const Vector3& p1_, const Vector3& p2_, Vector3* pOut_);

		static Plane Normalize(Plane p);
		void Normalize();

		static float DotNormal(Plane plane, Vector3 value);

		bool operator ==(const Plane& p) const;
		bool operator !=(const Plane& p) const;

		Vector3 n;
		float d;
	};
}
