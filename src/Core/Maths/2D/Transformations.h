
//------------------------------------------------------------------------
//
//  Name:   Transformations.h
//
//  Desc:   Functions for converting 2D vectors between World and Local
//          space.
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <vector>

#include "Maths/Vector2.h"
#include "CA_Export.h"
#include "Memory//MemoryAllocation.h"
#include "../Vector3.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT Transformation :
		public AllocatedObject<Transformation>
	{
	public:

		//--------------------------- WorldTransform -----------------------------
		//
		//  given a std::vector of 2D vectors, a position, orientation and scale,
		//  this function transforms the 2D vectors into the object's world space
		//------------------------------------------------------------------------
		static std::vector<Vector2F> WorldTransform(std::vector<Vector2F> &points,
			const Vector2F   &pos,
			const Vector2F   &forward,
			const Vector2F   &side,
			const Vector2F   &scale);

		//--------------------------- WorldTransform -----------------------------
		//
		//  given a std::vector of 2D vectors, a position and  orientation
		//  this function transforms the 2D vectors into the object's world space
		//------------------------------------------------------------------------
		static std::vector<Vector3F> WorldTransform(std::vector<Vector3F> &points,
			const Vector3F   &pos,
			const Vector3F   &forward,
			const Vector3F   &side,
			const Vector3F   &scale);

		//--------------------- PointToWorldSpace --------------------------------
		//
		//  Transforms a point from the agent's local space into world space
		//------------------------------------------------------------------------
		static Vector2F PointToWorldSpace(const Vector2F &point,
											const Vector2F &AgentHeading,
											const Vector2F &AgentSide,
											const Vector2F &AgentPosition);

		//--------------------- VectorToWorldSpace --------------------------------
		//
		//  Transforms a vector from the agent's local space into world space
		//------------------------------------------------------------------------
		static Vector2F VectorToWorldSpace(const Vector2F &vec,
											 const Vector2F &AgentHeading,
											 const Vector2F &AgentSide);


		//--------------------- PointToLocalSpace --------------------------------
		//
		//------------------------------------------------------------------------
		static Vector2F PointToLocalSpace(const Vector2F &point,
									 Vector2F &AgentHeading,
									 Vector2F &AgentSide,
									  Vector2F &AgentPosition);

		//--------------------- VectorToLocalSpace --------------------------------
		//
		//------------------------------------------------------------------------
		static Vector2F VectorToLocalSpace(const Vector2F &vec,
									 const Vector2F &AgentHeading,
									 const Vector2F &AgentSide);

		//-------------------------- Vec2DRotateAroundOrigin --------------------------
		//
		//  rotates a vector ang rads around the origin
		//-----------------------------------------------------------------------------
		static void Vec2DRotateAroundOrigin(Vector2F& v, float ang);

		//------------------------ CreateWhiskers ------------------------------------
		//
		//  given an origin, a facing direction, a 'field of view' describing the 
		//  limit of the outer whiskers, a whisker length and the number of whiskers
		//  this method returns a vector containing the end positions of a series
		//  of whiskers radiating away from the origin and with equal distance between
		//  them. (like the spokes of a wheel clipped to a specific segment size)
		//----------------------------------------------------------------------------
		static std::vector<Vector2F> CreateWhiskers(unsigned int  NumWhiskers,
													float        WhiskerLength,
													float        fov,
													Vector2F      facing,
													Vector2F      origin);

	}; // class transformation

}

#endif // TRANSFORMATIONS_H