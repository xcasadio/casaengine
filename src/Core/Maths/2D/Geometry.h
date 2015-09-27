
#ifndef GEOMETRY_H
#define GEOMETRY_H

//------------------------------------------------------------------------
//
//Name:   geometry.h 
//
//Desc:   useful 2D geometry functions
//
//Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include "Maths/Vector2.h"
#include "CA_Export.h"
#include <math.h>
#include <vector>

#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT Geometry :
		public AllocatedObject<Geometry>
	{
	public:

		//given a plane and a ray this function determins how far along the ray 
		//an interestion occurs. Returns negative if the ray is parallel
		static float DistanceToRayPlaneIntersection(Vector2F RayOrigin,
													 Vector2F RayHeading,
													 Vector2F PlanePoint,  //any point on the plane
													 Vector2F PlaneNormal);

		//------------------------- WhereIsPoint --------------------------------------
		enum span_type{plane_backside, plane_front, on_plane};

		static span_type WhereIsPoint(Vector2F point,
									  Vector2F PointOnPlane, //any point on the plane
									  Vector2F PlaneNormal);

		//-------------------------- GetRayCircleIntersec -----------------------------
		static float GetRayCircleIntersect(Vector2F RayOrigin,
											Vector2F RayHeading,
											Vector2F CircleOrigin,
											float  radius);

		//----------------------------- DoRayCircleIntersect --------------------------
		static bool DoRayCircleIntersect(Vector2F RayOrigin,
										 Vector2F RayHeading,
										 Vector2F CircleOrigin,
										 float     radius);

		//------------------------------------------------------------------------
		//  Given a point P and a circle of radius R centered at C this function
		//  determines the two points on the circle that intersect with the 
		//  tangents from P to the circle. Returns false if P is within the circle.
		//
		//  thanks to Dave Eberly for this one.
		//------------------------------------------------------------------------
		static bool GetTangentPoints (Vector2F C, float R, Vector2F P, Vector2F& T1, Vector2F& T2);



		//------------------------- DistToLineSegment ----------------------------
		//
		//  given a line segment AB and a point P, this function calculates the 
		//  perpendicular distance between them
		//------------------------------------------------------------------------
		static float DistToLineSegment(Vector2F A,
										Vector2F B,
										Vector2F P);

		//------------------------- DistToLineSegmentSq ----------------------------
		//
		//  as above, but avoiding sqrt
		//------------------------------------------------------------------------
		static float DistToLineSegmentSq(Vector2F A,
										 Vector2F B,
										 Vector2F P);


		//--------------------LineIntersection2D-------------------------
		//
		//	Given 2 lines in 2D space AB, CD this returns true if an 
		//	intersection occurs.
		//
		//----------------------------------------------------------------- 

		static bool LineIntersection2D(Vector2F A,
									   Vector2F B,
									   Vector2F C, 
									   Vector2F D);

		//--------------------LineIntersection2D-------------------------
		//
		//	Given 2 lines in 2D space AB, CD this returns true if an 
		//	intersection occurs and sets dist to the distance the intersection
		//  occurs along AB
		//
		//----------------------------------------------------------------- 

		static bool LineIntersection2D(Vector2F A,
								Vector2F B,
								Vector2F C, 
								Vector2F D,
								float &dist);

		//-------------------- LineIntersection2D-------------------------
		//
		//	Given 2 lines in 2D space AB, CD this returns true if an 
		//	intersection occurs and sets dist to the distance the intersection
		//  occurs along AB. Also sets the 2d vector point to the point of
		//  intersection
		//----------------------------------------------------------------- 
		static bool LineIntersection2D(Vector2F   A,
									   Vector2F   B,
									   Vector2F   C, 
									   Vector2F   D,
									   float&     dist,
									   Vector2F&  point);

		//----------------------- ObjectIntersection2D ---------------------------
		//
		//  tests two polygons for intersection. *Does not check for enclosure*
		//------------------------------------------------------------------------
		static bool ObjectIntersection2D(const std::vector<Vector2F>& object1,
										 const std::vector<Vector2F>& object2);

		//----------------------- SegmentObjectIntersection2D --------------------
		//
		//  tests a line segment against a polygon for intersection
		//  *Does not check for enclosure*
		//------------------------------------------------------------------------
		static bool SegmentObjectIntersection2D(const Vector2F& A,
										 const Vector2F& B,
										 const std::vector<Vector2F>& object);

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
		static bool TwoCirclesOverlapped(Vector2F c1, float r1,
								  Vector2F c2, float r2);

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
										  float &p3X, float &p3Y,
										  float &p4X, float &p4Y);

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
		static bool PointInCircle(Vector2F Pos,
								  float    radius,
								  Vector2F p);

		//--------------------- LineSegmentCircleIntersection ---------------------------
		//
		//  returns true if the line segemnt AB intersects with a circle at
		//  position P with radius radius
		//------------------------------------------------------------------------
		static bool   LineSegmentCircleIntersection(Vector2F A,
													Vector2F B,
													Vector2F P,
													float    radius);

		//------------------- GetLineSegmentCircleClosestIntersectionPoint ------------
		//
		//  given a line segment AB and a circle position and radius, this function
		//  determines if there is an intersection and stores the position of the 
		//  closest intersection in the reference IntersectionPoint
		//
		//  returns false if no intersection point is found
		//-----------------------------------------------------------------------------
		static bool GetLineSegmentCircleClosestIntersectionPoint(Vector2F A,
																 Vector2F B,
																 Vector2F pos,
																 float    radius,
																 Vector2F& IntersectionPoint);
	}; // class Transformation

} // namespace CasaEngine

#endif // GEOMETRY_H
