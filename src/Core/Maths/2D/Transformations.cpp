#include "Transformations.h"
#include "Maths/Vector2.h"
#include "Maths/Matrix3.h"
#include <vector>
#include "../Matrix4.h"

namespace CasaEngine
{
	//--------------------------- WorldTransform -----------------------------
	//
	//  given a std::vector of 2D vectors, a position, orientation and scale,
	//  this function transforms the 2D vectors into the object's world space
	//------------------------------------------------------------------------
	std::vector<Vector2> Transformation::WorldTransform(std::vector<Vector2>& points,
		const Vector2& pos,
		const Vector2& forward,
		const Vector2& side,
		const Vector2& scale)
	{
		//copy the original vertices into the buffer about to be transformed
		std::vector<Vector2> TranVector2Fs = points;

		//create a transformation matrix
		Matrix3 matTransform;

		//scale
		if (scale.x != 1.0 || scale.y != 1.0)
		{
			matTransform.Scale(scale.x, scale.y);
		}

		//rotate
		matTransform.Rotate(forward, side);

		//and translate
		matTransform.Translate(pos.x, pos.y);

		//now transform the object's vertices
		matTransform.TransformVector2List(TranVector2Fs);

		return TranVector2Fs;
	}

	//--------------------------- WorldTransform -----------------------------
	//
	//  given a std::vector of 3D vectors, a position, orientation and scale,
	//  this function transforms the 2D vectors into the object's world space
	//------------------------------------------------------------------------
	std::vector<Vector3> Transformation::WorldTransform(std::vector<Vector3>& points,
		const Vector3& pos,
		const Vector3& forward,
		const Vector3& side,
		const Vector3& scale)
	{
		//copy the original vertices into the buffer about to be transformed
		std::vector<Vector3> TranVectors = points;

		//create a transformation matrix
		Matrix4 matTransform, matScale, matRot, matTrans;

		//scale
		if (scale.x != 1.0 || scale.y != 1.0)
		{
			matScale.CreateScale(scale.x, 1.0f, scale.y);
		}

		//rotate
		matRot.CreateFromDirection(forward, side, Vector3::Up());

		//and translate
		matTrans.CreateTranslation(pos.x, 0.0f, pos.y);

		//now transform the object's vertices
		matTransform = matTrans * matRot * matScale;
		matTransform.Transform(TranVectors, TranVectors);

		return TranVectors;
	}

	//--------------------- PointToWorldSpace --------------------------------
	//
	//  Transforms a point from the agent's local space into world space
	//------------------------------------------------------------------------
	Vector2 Transformation::PointToWorldSpace(const Vector2& point,
		const Vector2& AgentHeading,
		const Vector2& AgentSide,
		const Vector2& AgentPosition)
	{
		//make a copy of the point
		Vector2 TransPoint = point;

		//create a transformation matrix
		Matrix3 matTransform;

		//rotate
		matTransform.Rotate(AgentHeading, AgentSide);

		//and translate
		matTransform.Translate(AgentPosition.x, AgentPosition.y);

		//now transform the vertices
		matTransform.TransformVector2F(TransPoint);

		return TransPoint;
	}

	//--------------------- VectorToWorldSpace --------------------------------
	//
	//  Transforms a vector from the agent's local space into world space
	//------------------------------------------------------------------------
	Vector2 Transformation::VectorToWorldSpace(const Vector2& vec,
		const Vector2& AgentHeading,
		const Vector2& AgentSide)
	{
		//make a copy of the point
		Vector2 TransVec = vec;

		//create a transformation matrix
		Matrix3 matTransform;

		//rotate
		matTransform.Rotate(AgentHeading, AgentSide);

		//now transform the vertices
		matTransform.TransformVector2F(TransVec);

		return TransVec;
	}

	//--------------------- PointToLocalSpace --------------------------------
	//
	//------------------------------------------------------------------------
	Vector2 Transformation::PointToLocalSpace(const Vector2& point,
		Vector2& AgentHeading,
		Vector2& AgentSide,
		Vector2& AgentPosition)
	{
		//make a copy of the point
		Vector2 TransPoint = point;

		//create a transformation matrix
		Matrix3 matTransform;

		float Tx = -AgentPosition.Dot(AgentHeading);
		float Ty = -AgentPosition.Dot(AgentSide);

		//create the transformation matrix
		matTransform.a11 = AgentHeading.x;	matTransform.a12 = AgentSide.x;
		matTransform.a21 = AgentHeading.y;	matTransform.a22 = AgentSide.y;
		matTransform.a31 = Tx;				matTransform.a32 = Ty;

		//now transform the vertices
		matTransform.TransformVector2F(TransPoint);

		return TransPoint;
	}

	//--------------------- VectorToLocalSpace --------------------------------
	//
	//------------------------------------------------------------------------
	Vector2 Transformation::VectorToLocalSpace(const Vector2& vec,
		const Vector2& AgentHeading,
		const Vector2& AgentSide)
	{
		//make a copy of the point
		Vector2 TransPoint = vec;

		//create a transformation matrix
		Matrix3 matTransform;

		//create the transformation matrix
		matTransform.a11 = AgentHeading.x; matTransform.a12 = AgentSide.x;
		matTransform.a21 = AgentHeading.y; matTransform.a22 = AgentSide.y;

		//now transform the vertices
		matTransform.TransformVector2F(TransPoint);

		return TransPoint;
	}

	//-------------------------- Vec2DRotateAroundOrigin --------------------------
	//
	//  rotates a vector ang rads around the origin
	//-----------------------------------------------------------------------------
	void Transformation::Vec2DRotateAroundOrigin(Vector2& v, float ang)
	{
		//create a transformation matrix
		Matrix3 mat;

		//rotate
		mat.Rotate(ang);

		//now transform the object's vertices
		mat.TransformVector2F(v);
	}

	//------------------------ CreateWhiskers ------------------------------------
	//
	//  given an origin, a facing direction, a 'field of view' describing the
	//  limit of the outer whiskers, a whisker length and the number of whiskers
	//  this method returns a vector containing the end positions of a series
	//  of whiskers radiating away from the origin and with equal distance between
	//  them. (like the spokes of a wheel clipped to a specific segment size)
	//----------------------------------------------------------------------------
	std::vector<Vector2> Transformation::CreateWhiskers(unsigned int  NumWhiskers,
		float        WhiskerLength,
		float        fov,
		Vector2      facing,
		Vector2      origin)
	{
		//this is the magnitude of the angle separating each whisker
		float SectorSize = fov / static_cast<float>(NumWhiskers - 1);

		std::vector<Vector2> whiskers;
		Vector2 temp;
		float angle = -fov * 0.5f;

		for (unsigned int w = 0; w < NumWhiskers; ++w)
		{
			//create the whisker extending outwards at this angle
			temp = facing;
			Vec2DRotateAroundOrigin(temp, angle);
			whiskers.push_back(origin + WhiskerLength * temp);

			angle += SectorSize;
		}

		return whiskers;
	}
}