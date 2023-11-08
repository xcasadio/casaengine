#ifndef GEOMETRY_H
#define GEOMETRY_H

//Desc:   useful 2D geometry functions
//Author: Mat Buckland (fup@ai-junkie.com)

#include  "Maths/Vector2.hpp"
#include "CA_Export.hpp"
#include <vector>

namespace CasaEngine
{
	class CA_EXPORT Geometry
	{
	public:

		//given a plane and a ray this function determins how far along the ray
		//an interestion occurs. Returns negative if the ray is parallel
		static float DistanceToRayPlaneIntersection(Vector2 RayOrigin,
			Vector2 RayHeading,
			Vector2 PlanePoint,  //any point on the plane
			Vector2 PlaneNormal);

		//------------------------- WhereIsPoint --------------------------------------
		enum span_type { plane_backside, plane_front, on_plane };

		static span_type WhereIsPoint(Vector2 point,
			Vector2 PointOnPlane, //any point on the plane
			Vector2 PlaneNormal);

		//-------------------------- GetRayCircleIntersec -----------------------------
		static float GetRayCircleIntersect(Vector2 RayOrigin,
			Vector2 RayHeading,
			Vector2 CircleOrigin,
			float  radius);

		//----------------------------- DoRayCircleIntersect --------------------------
		static bool DoRayCircleIntersect(Vector2 RayOrigin,
			Vector2 RayHeading,
			Vector2 CircleOrigin,
			float     radius);

		//------------------------------------------------------------------------
		//  Given a point P and a circle of radius R centered at C this function
		//  determines the two points on the circle that intersect with the
		//  tangents from P to the circle. Returns false if P is within the circle.
		//
		//  thanks to Dave Eberly for this one.
		//------------------------------------------------------------------------
		static bool GetTangentPoints(Vector2 C, float R, Vector2 P, Vector2& T1, Vector2& T2);

		//------------------------- DistToLineSegment ----------------------------
		//
		//  given a line segment AB and a point P, this function calculates the
		//  perpendicular distance between them
		//------------------------------------------------------------------------
		static float DistToLineSegment(Vector2 A,
			Vector2 B,
			Vector2 P);

		//------------------------- DistToLineSegmentSq ----------------------------
		//
		//  as above, but avoiding sqrt
		//------------------------------------------------------------------------
		static float DistToLineSegmentSq(Vector2 A,
			Vector2 B,
			Vector2 P);

		//--------------------LineIntersection2D-------------------------
		//
		//	Given 2 lines in 2D space AB, CD this returns true if an
		//	intersection occurs.
		//
		//-----------------------------------------------------------------

		static bool LineIntersection2D(Vector2 A,
			Vector2 B,
			Vector2 C,
			Vector2 D);

		//--------------------LineIntersection2D-------------------------
		//
		//	Given 2 lines in 2D space AB, CD this returns true if an
		//	intersection occurs and sets dist to the distance the intersection
		//  occurs along AB
		//
		//-----------------------------------------------------------------

		static bool LineIntersection2D(Vector2 A,
			Vector2 B,
			Vector2 C,
			Vector2 D,
			float& dist);

		//-------------------- LineIntersection2D-------------------------
		//
		//	Given 2 lines in 2D space AB, CD this returns true if an
		//	intersection occurs and sets dist to the distance the intersection
		//  occurs along AB. Also sets the 2d vector point to the point of
		//  intersection
		//-----------------------------------------------------------------
		static bool LineIntersection2D(Vector2   A,
			Vector2   B,
			Vector2   C,
			Vector2   D,
			float& dist,
			Vector2& point);

		//----------------------- ObjectIntersection2D ---------------------------
		//
		//  tests two polygons for intersection. *Does not check for enclosure*
		//------------------------------------------------------------------------
		static bool ObjectIntersection2D(const std::vector<Vector2>& object1,
			const std::vector<Vector2>& object2);

		//----------------------- SegmentObjectIntersection2D --------------------
		//
		//  tests a line segment against a polygon for intersection
		//  *Does not check for enclosure*
		//------------------------------------------------------------------------
		static bool SegmentObjectIntersection2D(const Vector2& A,
			const Vector2& B,
			const std::vector<Vector2>& object);

		//----------------------------- TwoCirclesOverlapped ---------------------
		//
		//  Returns true if the two circles overlap
		//------------------------------------------------------------------------
		static bool TwoCirclesOverlapped(float x1, float y1, float r1,
			float x2, float y2, float r2);

		//----------------------------- TwoCirclesOverlapped ---------------------
		//
		//  Returns true if the two circles overlap
		//------------------------------------------------------------------------
		static bool TwoCirclesOverlapped(Vector2 c1, float r1,
			Vector2 c2, float r2);

		//--------------------------- TwoCirclesEnclosed ---------------------------
		//
		//  returns true if one circle encloses the other
		//-------------------------------------------------------------------------
		static bool TwoCirclesEnclosed(float x1, float y1, float r1,
			float x2, float y2, float r2);

		//------------------------ TwoCirclesIntersectionPoints ------------------
		//
		//  Given two circles this function calculates the intersection points
		//  of any overlap.
		//
		//  returns false if no overlap found
		//
		// see http://astronomy.swin.edu.au/~pbourke/geometry/2circle/
		//------------------------------------------------------------------------
		static bool TwoCirclesIntersectionPoints(float x1, float y1, float r1,
			float x2, float y2, float r2,
			float& p3X, float& p3Y,
			float& p4X, float& p4Y);

		//------------------------ TwoCirclesIntersectionArea --------------------
		//
		//  Tests to see if two circles overlap and if so calculates the area
		//  defined by the union
		//
		// see http://mathforum.org/library/drmath/view/54785.html
		//-----------------------------------------------------------------------
		static float TwoCirclesIntersectionArea(float x1, float y1, float r1,
			float x2, float y2, float r2);

		//-------------------------------- CircleArea ---------------------------
		//
		//  given the radius, calculates the area of a circle
		//-----------------------------------------------------------------------
		static float CircleArea(float radius);

		//----------------------- PointInCircle ----------------------------------
		//
		//  returns true if the point p is within the radius of the given circle
		//------------------------------------------------------------------------
		static bool PointInCircle(Vector2 Pos,
			float    radius,
			Vector2 p);

		//--------------------- LineSegmentCircleIntersection ---------------------------
		//
		//  returns true if the line segemnt AB intersects with a circle at
		//  position P with radius radius
		//------------------------------------------------------------------------
		static bool   LineSegmentCircleIntersection(Vector2 A,
			Vector2 B,
			Vector2 P,
			float    radius);

		//------------------- GetLineSegmentCircleClosestIntersectionPoint ------------
		//
		//  given a line segment AB and a circle position and radius, this function
		//  determines if there is an intersection and stores the position of the
		//  closest intersection in the reference IntersectionPoint
		//
		//  returns false if no intersection point is found
		//-----------------------------------------------------------------------------
		static bool GetLineSegmentCircleClosestIntersectionPoint(Vector2 A,
			Vector2 B,
			Vector2 pos,
			float    radius,
			Vector2& IntersectionPoint);
	};
}

#endif
