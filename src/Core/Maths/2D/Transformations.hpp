//  Name:   Transformations.h
//  Desc:   Functions for converting 2D vectors between World and Local space.

#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <vector>

#include  "Maths/Vector2.hpp"
#include "CA_Export.hpp"
#include  "Maths/Vector3.hpp"

namespace CasaEngine
{
	class CA_EXPORT Transformation
	{
	public:

		//--------------------------- WorldTransform -----------------------------
		//
		//  given a std::vector of 2D vectors, a position, orientation and scale,
		//  this function transforms the 2D vectors into the object's world space
		//------------------------------------------------------------------------
		static std::vector<Vector2> WorldTransform(std::vector<Vector2>& points,
			const Vector2& pos,
			const Vector2& forward,
			const Vector2& side,
			const Vector2& scale);

		//--------------------------- WorldTransform -----------------------------
		//
		//  given a std::vector of 2D vectors, a position and  orientation
		//  this function transforms the 2D vectors into the object's world space
		//------------------------------------------------------------------------
		static std::vector<Vector3> WorldTransform(std::vector<Vector3>& points,
			const Vector3& pos,
			const Vector3& forward,
			const Vector3& side,
			const Vector3& scale);

		//--------------------- PointToWorldSpace --------------------------------
		//
		//  Transforms a point from the agent's local space into world space
		//------------------------------------------------------------------------
		static Vector2 PointToWorldSpace(const Vector2& point,
			const Vector2& AgentHeading,
			const Vector2& AgentSide,
			const Vector2& AgentPosition);

		//--------------------- VectorToWorldSpace --------------------------------
		//
		//  Transforms a vector from the agent's local space into world space
		//------------------------------------------------------------------------
		static Vector2 VectorToWorldSpace(const Vector2& vec,
			const Vector2& AgentHeading,
			const Vector2& AgentSide);

		//--------------------- PointToLocalSpace --------------------------------
		//
		//------------------------------------------------------------------------
		static Vector2 PointToLocalSpace(const Vector2& point,
			Vector2& AgentHeading,
			Vector2& AgentSide,
			Vector2& AgentPosition);

		//--------------------- VectorToLocalSpace --------------------------------
		//
		//------------------------------------------------------------------------
		static Vector2 VectorToLocalSpace(const Vector2& vec,
			const Vector2& AgentHeading,
			const Vector2& AgentSide);

		//-------------------------- Vec2DRotateAroundOrigin --------------------------
		//
		//  rotates a vector ang rads around the origin
		//-----------------------------------------------------------------------------
		static void Vec2DRotateAroundOrigin(Vector2& v, float ang);

		//------------------------ CreateWhiskers ------------------------------------
		//
		//  given an origin, a facing direction, a 'field of view' describing the
		//  limit of the outer whiskers, a whisker length and the number of whiskers
		//  this method returns a vector containing the end positions of a series
		//  of whiskers radiating away from the origin and with equal distance between
		//  them. (like the spokes of a wheel clipped to a specific segment size)
		//----------------------------------------------------------------------------
		static std::vector<Vector2> CreateWhiskers(unsigned int  NumWhiskers,
			float        WhiskerLength,
			float        fov,
			Vector2      facing,
			Vector2      origin);
	}; // class transformation
}

#endif
