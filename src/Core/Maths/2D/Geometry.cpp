#include  "Maths/Math.hpp"
#include  "Maths/Vector2.hpp"
#include  "Geometry.hpp"
#include  "Transformations.hpp"
#include <vector>

namespace CasaEngine
{
	//given a plane and a ray this function determins how far along the ray
	//an interestion occurs. Returns negative if the ray is parallel
	float Geometry::DistanceToRayPlaneIntersection(Vector2 RayOrigin,
		Vector2 RayHeading,
		Vector2 PlanePoint,  //any point on the plane
		Vector2 PlaneNormal)
	{
		float d = -PlaneNormal.Dot(PlanePoint);
		float numer = PlaneNormal.Dot(RayOrigin) + d;
		float denom = PlaneNormal.Dot(RayHeading);

		// normal is parallel to vector
		if (denom < 0.000001 && denom > -0.000001)
		{
			return -1.0;
		}

		return -(numer / denom);
	}

	//------------------------- WhereIsPoint --------------------------------------
	Geometry::span_type Geometry::WhereIsPoint(Vector2 point,
		Vector2 PointOnPlane, //any point on the plane
		Vector2 PlaneNormal)
	{
		Vector2 dir = PointOnPlane - point;

		float d = dir.Dot(PlaneNormal);

		if (d < -0.000001)
		{
			return plane_front;
		}
		if (d > 0.000001)
		{
			return plane_backside;
		}

		return on_plane;
	}

	//-------------------------- GetRayCircleIntersec -----------------------------
	float Geometry::GetRayCircleIntersect(Vector2 RayOrigin,
		Vector2 RayHeading,
		Vector2 CircleOrigin,
		float  radius)
	{
		Vector2 ToCircle = CircleOrigin - RayOrigin;
		float length = ToCircle.Length();
		float v = ToCircle.Dot(RayHeading);
		float d = radius * radius - (length * length - v * v);

		// If there was no intersection, return -1
		if (d < 0.0)
		{
			return -1.0;
		}

		// Return the distance to the [first] intersecting point
		return v - sqrt(d);
	}

	//----------------------------- DoRayCircleIntersect --------------------------
	bool Geometry::DoRayCircleIntersect(Vector2 RayOrigin,
		Vector2 RayHeading,
		Vector2 CircleOrigin,
		float     radius)
	{
		Vector2 ToCircle = CircleOrigin - RayOrigin;
		float length = ToCircle.Length();
		float v = ToCircle.Dot(RayHeading);
		float d = radius * radius - (length * length - v * v);

		// If there was no intersection, return -1
		return d < 0.0;
	}

	//------------------------------------------------------------------------
	//  Given a point P and a circle of radius R centered at C this function
	//  determines the two points on the circle that intersect with the
	//  tangents from P to the circle. Returns false if P is within the circle.
	//
	//  thanks to Dave Eberly for this one.
	//------------------------------------------------------------------------
	bool Geometry::GetTangentPoints(Vector2 C, float R, Vector2 P, Vector2& T1, Vector2& T2)
	{
		Vector2 PmC = P - C;
		float SqrLen = PmC.LengthSquared();
		float RSqr = R * R;
		if (SqrLen <= RSqr)
		{
			// P is inside or on the circle
			return false;
		}

		float InvSqrLen = 1 / SqrLen;
		float Root = sqrt(fabs(SqrLen - RSqr));

		T1.x = C.x + R * (R * PmC.x - PmC.y * Root) * InvSqrLen;
		T1.y = C.y + R * (R * PmC.y + PmC.x * Root) * InvSqrLen;
		T2.x = C.x + R * (R * PmC.x + PmC.y * Root) * InvSqrLen;
		T2.y = C.y + R * (R * PmC.y - PmC.x * Root) * InvSqrLen;

		return true;
	}

	//------------------------- DistToLineSegment ----------------------------
	//
	//  given a line segment AB and a point P, this function calculates the
	//  perpendicular distance between them
	//------------------------------------------------------------------------
	float Geometry::DistToLineSegment(Vector2 A,
		Vector2 B,
		Vector2 P)
	{
		//if the angle is obtuse between PA and AB is obtuse then the closest
		//vertex must be A
		float dotA = (P.x - A.x) * (B.x - A.x) + (P.y - A.y) * (B.y - A.y);

		if (dotA <= 0)
		{
			return (A - P).Length(); //Vec2DDistance(A, P);
		}

		//if the angle is obtuse between PB and AB is obtuse then the closest
		//vertex must be B
		float dotB = (P.x - B.x) * (A.x - B.x) + (P.y - B.y) * (A.y - B.y);

		if (dotB <= 0)
		{
			return (B - P).Length(); //Vec2DDistance(B, P);
		}

		//calculate the point along AB that is the closest to P
		Vector2 Point = A + (B - A) * dotA / (dotA + dotB);

		//calculate the distance P-Point
		return (P - Point).Length();//Vec2DDistance(P,Point);
	}

	//------------------------- DistToLineSegmentSq ----------------------------
	//
	//  as above, but avoiding sqrt
	//------------------------------------------------------------------------
	float Geometry::DistToLineSegmentSq(Vector2 A,
		Vector2 B,
		Vector2 P)
	{
		//if the angle is obtuse between PA and AB is obtuse then the closest
		//vertex must be A
		float dotA = (P.x - A.x) * (B.x - A.x) + (P.y - A.y) * (B.y - A.y);

		if (dotA <= 0)
		{
			return (A - P).LengthSquared(); //Vec2DDistanceSq(A, P);
		}

		//if the angle is obtuse between PB and AB is obtuse then the closest
		//vertex must be B
		float dotB = (P.x - B.x) * (A.x - B.x) + (P.y - B.y) * (A.y - B.y);

		if (dotB <= 0)
		{
			return (B - P).LengthSquared(); //Vec2DDistanceSq(B, P);
		}

		//calculate the point along AB that is the closest to P
		Vector2 Point = A + (B - A) * dotA / (dotA + dotB);

		//calculate the distance P-Point
		return (P - Point).LengthSquared();//Vec2DDistanceSq(P,Point);
	}

	//--------------------LineIntersection2D-------------------------
	//
	//	Given 2 lines in 2D space AB, CD this returns true if an
	//	intersection occurs.
	//
	//-----------------------------------------------------------------

	bool Geometry::LineIntersection2D(Vector2 A,
		Vector2 B,
		Vector2 C,
		Vector2 D)
	{
		float rTop = (A.y - C.y) * (D.x - C.x) - (A.x - C.x) * (D.y - C.y);
		float sTop = (A.y - C.y) * (B.x - A.x) - (A.x - C.x) * (B.y - A.y);

		float Bot = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

		if (Bot == 0)//parallel
		{
			return false;
		}

		float invBot = 1.0f / Bot;
		float r = rTop * invBot;
		float s = sTop * invBot;

		if (r > 0 && r < 1 && s > 0 && s < 1)
		{
			//lines intersect
			return true;
		}

		//lines do not intersect
		return false;
	}

	//--------------------LineIntersection2D-------------------------
	//
	//	Given 2 lines in 2D space AB, CD this returns true if an
	//	intersection occurs and sets dist to the distance the intersection
	//  occurs along AB
	//
	//-----------------------------------------------------------------

	bool Geometry::LineIntersection2D(Vector2 A,
		Vector2 B,
		Vector2 C,
		Vector2 D,
		float& dist)
	{
		float rTop = (A.y - C.y) * (D.x - C.x) - (A.x - C.x) * (D.y - C.y);
		float sTop = (A.y - C.y) * (B.x - A.x) - (A.x - C.x) * (B.y - A.y);

		float Bot = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

		if (Bot == 0)//parallel
		{
			if (Math::isEqual(rTop, 0) && Math::isEqual(sTop, 0))
			{
				return true;
			}
			return false;
		}

		float r = rTop / Bot;
		float s = sTop / Bot;

		if (r > 0 && r < 1 && s > 0 && s < 1)
		{
			dist = (A - B).Length() * r;//Vec2DDistance(A,B) * r;

			return true;
		}
		dist = 0;

		return false;
	}

	//-------------------- LineIntersection2D-------------------------
	//
	//	Given 2 lines in 2D space AB, CD this returns true if an
	//	intersection occurs and sets dist to the distance the intersection
	//  occurs along AB. Also sets the 2d vector point to the point of
	//  intersection
	//-----------------------------------------------------------------
	bool Geometry::LineIntersection2D(Vector2   A,
		Vector2   B,
		Vector2   C,
		Vector2   D,
		float& dist,
		Vector2& point)
	{
		float rTop = (A.y - C.y) * (D.x - C.x) - (A.x - C.x) * (D.y - C.y);
		float rBot = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

		float sTop = (A.y - C.y) * (B.x - A.x) - (A.x - C.x) * (B.y - A.y);
		float sBot = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

		if (rBot == 0 || sBot == 0)
		{
			//lines are parallel
			return false;
		}

		float r = rTop / rBot;
		float s = sTop / sBot;

		if (r > 0 && r < 1 && s > 0 && s < 1)
		{
			dist = (A - B).Length() * r;// Vec2DDistance(A,B) * r;

			point = A + r * (B - A);

			return true;
		}
		dist = 0;

		return false;
	}

	//----------------------- ObjectIntersection2D ---------------------------
	//
	//  tests two polygons for intersection. *Does not check for enclosure*
	//------------------------------------------------------------------------
	bool Geometry::ObjectIntersection2D(const std::vector<Vector2>& object1,
		const std::vector<Vector2>& object2)
	{
		//test each line segment of object1 against each segment of object2
		for (unsigned int r = 0; r < object1.size() - 1; ++r)
		{
			for (unsigned int t = 0; t < object2.size() - 1; ++t)
			{
				if (LineIntersection2D(object2[t],
					object2[t + 1],
					object1[r],
					object1[r + 1]))
				{
					return true;
				}
			}
		}

		return false;
	}

	//----------------------- SegmentObjectIntersection2D --------------------
	//
	//  tests a line segment against a polygon for intersection
	//  *Does not check for enclosure*
	//------------------------------------------------------------------------
	bool Geometry::SegmentObjectIntersection2D(const Vector2& A,
		const Vector2& B,
		const std::vector<Vector2>& object)
	{
		//test AB against each segment of object
		for (unsigned int r = 0; r < object.size() - 1; ++r)
		{
			if (LineIntersection2D(A, B, object[r], object[r + 1]))
			{
				return true;
			}
		}

		return false;
	}

	//----------------------------- TwoCirclesOverlapped ---------------------
	//
	//  Returns true if the two circles overlap
	//------------------------------------------------------------------------
	bool Geometry::TwoCirclesOverlapped(float x1, float y1, float r1,
		float x2, float y2, float r2)
	{
		float DistBetweenCenters = sqrt((x1 - x2) * (x1 - x2) +
			(y1 - y2) * (y1 - y2));

		if (DistBetweenCenters < r1 + r2 || DistBetweenCenters < fabs(r1 - r2))
		{
			return true;
		}

		return false;
	}

	//----------------------------- TwoCirclesOverlapped ---------------------
	//
	//  Returns true if the two circles overlap
	//------------------------------------------------------------------------
	bool Geometry::TwoCirclesOverlapped(Vector2 c1, float r1,
		Vector2 c2, float r2)
	{
		float DistBetweenCenters = sqrt((c1.x - c2.x) * (c1.x - c2.x) +
			(c1.y - c2.y) * (c1.y - c2.y));

		if (DistBetweenCenters < r1 + r2 || DistBetweenCenters < fabs(r1 - r2))
		{
			return true;
		}

		return false;
	}

	//--------------------------- TwoCirclesEnclosed ---------------------------
	//
	//  returns true if one circle encloses the other
	//-------------------------------------------------------------------------
	bool Geometry::TwoCirclesEnclosed(float x1, float y1, float r1,
		float x2, float y2, float r2)
	{
		float DistBetweenCenters = sqrt((x1 - x2) * (x1 - x2) +
			(y1 - y2) * (y1 - y2));

		if (DistBetweenCenters < fabs(r1 - r2))
		{
			return true;
		}

		return false;
	}

	//------------------------ TwoCirclesIntersectionPoints ------------------
	//
	//  Given two circles this function calculates the intersection points
	//  of any overlap.
	//
	//  returns false if no overlap found
	//
	// see http://astronomy.swin.edu.au/~pbourke/geometry/2circle/
	//------------------------------------------------------------------------
	bool Geometry::TwoCirclesIntersectionPoints(float x1, float y1, float r1,
		float x2, float y2, float r2,
		float& p3X, float& p3Y,
		float& p4X, float& p4Y)
	{
		//first check to see if they overlap
		if (!TwoCirclesOverlapped(x1, y1, r1, x2, y2, r2))
		{
			return false;
		}

		//calculate the distance between the circle centers
		float d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

		//Now calculate the distance from the center of each circle to the center
		//of the line which connects the intersection points.
		float a = (r1 - r2 + d * d) / (2 * d);
		//float b = (r2 - r1 + (d * d)) / (2 * d);

		//MAYBE A TEST FOR EXACT OVERLAP?

		//calculate the point P2 which is the center of the line which
		//connects the intersection points
		float p2X, p2Y;

		p2X = x1 + a * (x2 - x1) / d;
		p2Y = y1 + a * (y2 - y1) / d;

		//calculate first point
		float h1 = sqrt(r1 * r1 - a * a);

		p3X = p2X - h1 * (y2 - y1) / d;
		p3Y = p2Y + h1 * (x2 - x1) / d;

		//calculate second point
		float h2 = sqrt(r2 * r2 - a * a);

		p4X = p2X + h2 * (y2 - y1) / d;
		p4Y = p2Y - h2 * (x2 - x1) / d;

		return true;
	}

	//------------------------ TwoCirclesIntersectionArea --------------------
	//
	//  Tests to see if two circles overlap and if so calculates the area
	//  defined by the union
	//
	// see http://mathforum.org/library/drmath/view/54785.html
	//-----------------------------------------------------------------------
	float Geometry::TwoCirclesIntersectionArea(float x1, float y1, float r1,
		float x2, float y2, float r2)
	{
		//first calculate the intersection points
		float iX1, iY1, iX2, iY2;

		if (!TwoCirclesIntersectionPoints(x1, y1, r1, x2, y2, r2, iX1, iY1, iX2, iY2))
		{
			return 0.0; //no overlap
		}

		//calculate the distance between the circle centers
		float d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

		//find the angles given that A and B are the two circle centers
		//and C and D are the intersection points
		float CBD = 2 * acos((r2 * r2 + d * d - r1 * r1) / (r2 * d * 2));

		float CAD = 2 * acos((r1 * r1 + d * d - r2 * r2) / (r1 * d * 2));

		//Then we find the segment of each of the circles cut off by the
		//chord CD, by taking the area of the sector of the circle BCD and
		//subtracting the area of triangle BCD. Similarly we find the area
		//of the sector ACD and subtract the area of triangle ACD.

		float area = 0.5f * CBD * r2 * r2 - 0.5f * r2 * r2 * sin(CBD) +
			0.5f * CAD * r1 * r1 - 0.5f * r1 * r1 * sin(CAD);

		return area;
	}

	//-------------------------------- CircleArea ---------------------------
	//
	//  given the radius, calculates the area of a circle
	//-----------------------------------------------------------------------
	float Geometry::CircleArea(float radius)
	{
		return Math::Pi * radius * radius;
	}

	//----------------------- PointInCircle ----------------------------------
	//
	//  returns true if the point p is within the radius of the given circle
	//------------------------------------------------------------------------
	bool Geometry::PointInCircle(Vector2 Pos,
		float    radius,
		Vector2 p)
	{
		float DistFromCenterSquared = (p - Pos).LengthSquared();

		if (DistFromCenterSquared < radius * radius)
		{
			return true;
		}

		return false;
	}

	//--------------------- LineSegmentCircleIntersection ---------------------------
	//
	//  returns true if the line segemnt AB intersects with a circle at
	//  position P with radius radius
	//------------------------------------------------------------------------
	bool   Geometry::LineSegmentCircleIntersection(Vector2 A,
		Vector2 B,
		Vector2 P,
		float    radius)
	{
		//first determine the distance from the center of the circle to
		//the line segment (working in distance squared space)
		float DistToLineSq = DistToLineSegmentSq(A, B, P);

		if (DistToLineSq < radius * radius)
		{
			return true;
		}
		return false;
	}

	//------------------- GetLineSegmentCircleClosestIntersectionPoint ------------
	//
	//  given a line segment AB and a circle position and radius, this function
	//  determines if there is an intersection and stores the position of the
	//  closest intersection in the reference IntersectionPoint
	//
	//  returns false if no intersection point is found
	//-----------------------------------------------------------------------------
	bool Geometry::GetLineSegmentCircleClosestIntersectionPoint(Vector2 A,
		Vector2 B,
		Vector2 pos,
		float    radius,
		Vector2& IntersectionPoint)
	{
		Vector2 toBNorm = B - A; //Vec2DNormalize(B-A);
		toBNorm.Normalize();

		//move the circle into the local space defined by the vector B-A with origin
		//at A
		Vector2 toBNormPerp = toBNorm.GetOrthogonal();
		Vector2 LocalPos = Transformation::PointToLocalSpace(pos, toBNorm, toBNormPerp, A);

		bool ipFound = false;

		//if the local position + the radius is negative then the circle lays behind
		//point A so there is no intersection possible. If the local x pos minus the
		//radius is greater than length A-B then the circle cannot intersect the
		//line segment
		if (LocalPos.x + radius >= 0 &&
			(LocalPos.x - radius) * (LocalPos.x - radius) <= (B - A).LengthSquared())//Vec2DDistanceSq(B, A)) )
		{
			//if the distance from the x axis to the object's position is less
			//than its radius then there is a potential intersection.
			if (fabs(LocalPos.y) < radius)
			{
				//now to do a line/circle intersection test. The center of the
				//circle is represented by A, B. The intersection points are
				//given by the formulae x = A +/-sqrt(r^2-B^2), y=0. We only
				//need to look at the smallest positive value of x.
				float a = LocalPos.x;
				float b = LocalPos.y;

				float ip = a - sqrt(radius * radius - b * b);

				if (ip <= 0)
				{
					ip = a + sqrt(radius * radius - b * b);
				}

				ipFound = true;

				IntersectionPoint = A + toBNorm * ip;
			}
		}

		return ipFound;
	}
}