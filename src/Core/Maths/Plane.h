#ifndef PLANE_H
#define PLANE_H

#include <Maths/Vector3.h>
#include <Maths/Vector4.h>
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	class CPlane :
		public AllocatedObject<CPlane>
	{
	public:
		CPlane(float A = 0.0f, float B = 0.0f, float C = 0.0f, float D = 0.0f);
		CPlane(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2);
		CPlane(const Vector3F& Normal, const Vector3F& Point);

		void BuildFromPoints(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2);
		float DistanceToPoint(const Vector3F& Point) const;
		float DistanceToPoint(const Vector4F& Point) const;
		bool IntersectLine(const Vector3F& p1_, const Vector3F& p2_, Vector3F* pOut_);

		bool operator ==(const CPlane& p) const;
		bool operator !=(const CPlane& p) const;

		Vector3F n; ///< Normale du plan
		float    d; ///< Distance du plan à l'originie
	};

	std::istream& operator >>(std::istream& Stream, CPlane& Plane);
	std::ostream& operator <<(std::ostream& Stream, const CPlane& Plane);

#include "Plane.inl"
}

#endif // PLANE_H
