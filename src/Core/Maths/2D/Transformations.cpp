#include "Base.h"
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
	std::vector<Vector2F> Transformation::WorldTransform(std::vector<Vector2F>& points,
		const Vector2F& pos,
		const Vector2F& forward,
		const Vector2F& side,
		const Vector2F& scale)
	{
		//copy the original vertices into the buffer about to be transformed
		std::vector<Vector2F> TranVector2Fs = points;

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
	std::vector<Vector3F> Transformation::WorldTransform(std::vector<Vector3F>& points,
		const Vector3F& pos,
		const Vector3F& forward,
		const Vector3F& side,
		const Vector3F& scale)
	{
		//copy the original vertices into the buffer about to be transformed
		std::vector<Vector3F> TranVectors = points;

		//create a transformation matrix
		Matrix4 matTransform, matScale, matRot, matTrans;

		//scale
		if (scale.x != 1.0 || scale.y != 1.0)
		{
			matScale.CreateScale(scale.x, 1.0f, scale.y);
		}

		//rotate
		matRot.CreateFromDirection(forward, side, Vector3F::Up());

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
	Vector2F Transformation::PointToWorldSpace(const Vector2F& point,
		const Vector2F& AgentHeading,
		const Vector2F& AgentSide,
		const Vector2F& AgentPosition)
	{
		//make a copy of the point
		Vector2F TransPoint = point;

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
	Vector2F Transformation::VectorToWorldSpace(const Vector2F& vec,
		const Vector2F& AgentHeading,
		const Vector2F& AgentSide)
	{
		//make a copy of the point
		Vector2F TransVec = vec;

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
	Vector2F Transformation::PointToLocalSpace(const Vector2F& point,
		Vector2F& AgentHeading,
		Vector2F& AgentSide,
		Vector2F& AgentPosition)
	{
		//make a copy of the point
		Vector2F TransPoint = point;

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
	Vector2F Transformation::VectorToLocalSpace(const Vector2F& vec,
		const Vector2F& AgentHeading,
		const Vector2F& AgentSide)
	{
		//make a copy of the point
		Vector2F TransPoint = vec;

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
	void Transformation::Vec2DRotateAroundOrigin(Vector2F& v, float ang)
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
	std::vector<Vector2F> Transformation::CreateWhiskers(unsigned int  NumWhiskers,
		float        WhiskerLength,
		float        fov,
		Vector2F      facing,
		Vector2F      origin)
	{
		//this is the magnitude of the angle separating each whisker
		float SectorSize = fov / static_cast<float>(NumWhiskers - 1);

		std::vector<Vector2F> whiskers;
		Vector2F temp;
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