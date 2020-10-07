#include "BoundingShapes.h"
#include "Matrix3.h"
#include "Vector3.h"

namespace CasaEngine
{
	inline float __fsel(const float _a, const float _b, const float _c) { return _a < 0.0f ? _c : _b;}
	
	/**
	 * 
	 */
	Cone::Cone()
	{

	}

	Cone::Cone(const Vector3F& tip , const Vector3F& dir, float height, float baseRadius) : mTip(tip), mDir(dir), mBase(tip + dir * height), mHeight(height), mBaseRadius(baseRadius)
	{

	}


	AABB::AABB()
	{

	}

	AABB::AABB(type_reset)
	{
		Reset();
	}

	AABB::AABB(float radius)
	{
		max = Vector3F(radius); min = -max;
	}

	AABB::AABB(const Vector3F& v)
	{
		min = max = v;
	}

	AABB::AABB(const Vector3F& v, float radius)
	{
		Vector3F ext(radius); min = v-ext; max = v+ext;
	}

	AABB::AABB(const Vector3F &vmin, const Vector3F &vmax)
	{
		min=vmin; max=vmax;
	}

	AABB::AABB(const AABB &aabb)
	{
		min.x = aabb.min.x;			min.y = aabb.min.y;			min.z = aabb.min.z;
		max.x = aabb.max.x;			max.y = aabb.max.y;			max.z = aabb.max.z;
	}

	AABB::AABB(const Vector3F* points, int num)
	{
		Reset();
		for ( int i=0; i<num; i++ )
			Add( points[i] );
	}

	void AABB::Reset()
	{
		min = Vector3F(1e15f);	max = Vector3F(-1e15f);
	}

	bool AABB::IsReset() const
	{
		return min.x > max.x;
	}

	float AABB::IsResetSel(float ifReset, float ifNotReset) const
	{
		return static_cast<float>(__fsel(max.x - min.x, ifNotReset, ifReset));
	}

	bool AABB::IsEmpty() const
	{
		return min == max;
	}

	bool AABB::IsNonZero() const
	{
		return min.x < max.x && min.y < max.y && min.z < max.z;
	}

	Vector3F AABB::GetCenter() const
	{
		return (min+max)*0.5f;
	}

	Vector3F AABB::GetSize() const
	{
		return (max-min) * IsResetSel(0.0f, 1.0f);
	}

	float AABB::GetRadius() const
	{
		return IsResetSel(0.0f, (max-min).Length()*0.5f);
	}

	float AABB::GetRadiusSqr() const
	{
		return IsResetSel(0.0f, ((max-min)*0.5f).LengthSquared());
	}

	float AABB::GetVolume() const
	{
		return IsResetSel(0.0f, (max.x-min.x) * (max.y-min.y) * (max.z-min.z));
	}

	void AABB::Add(const Vector3F &v)
	{
		min.CheckMin(v);
		max.CheckMax(v);
	}

	void AABB::Add(const Vector3F& v, float radius)
	{
		Vector3F ext(radius);
		min.CheckMin(v-ext);
		max.CheckMax(v+ext);
	}

	void AABB::Add(const AABB& bb)
	{
		min.CheckMin(bb.min);
		max.CheckMax(bb.max);
	}

	void AABB::Move(const Vector3F& v)
	{
		const float moveMult = IsResetSel(0.0f, 1.0f);
		const Vector3F vMove = v * moveMult;
		min += vMove;
		max += vMove;
	}

	void AABB::Expand(Vector3F const& v)
	{
		if (!IsReset())
		{
			min -= v;
			max += v;
		}
	}

	void AABB::Augment(AABB const& bb)
	{
		if (!IsReset() && !bb.IsReset())
		{
			Add( min + bb.min );
			Add( max + bb.max );
		}
	}

	void AABB::ClipToBox(AABB const& bb)
	{
		min.CheckMax(bb.min);
		max.CheckMin(bb.max);
	}

	void AABB::ClipMoveToBox(AABB const& bb)
	{
		for (int a = 0; a < 3; a++)
		{
			if (max[a] - min[a] > bb.max[a] - bb.min[a])
			{
				min[a] = bb.min[a];  
				max[a] = bb.max[a];
			}
			else if (min[a] < bb.min[a])
			{
				max[a] += bb.min[a] - min[a];
				min[a] = bb.min[a];
			}
			else if (max[a] > bb.max[a])
			{
				min[a] += bb.max[a] - max[a];
				max[a] = bb.max[a];
			}
		}
	}

	bool AABB::IsOverlapSphereBounds(const Vector3F &pos, float radius) const
	{
		CA_ASSERT( min.IsValid(), "IsOverlapSphereBounds() : min is not valid");
		CA_ASSERT( max.IsValid(), "IsOverlapSphereBounds() : max is not valid");
		CA_ASSERT( pos.IsValid(), "IsOverlapSphereBounds() : pos is not valid");

		if (pos.x > min.x && pos.x < max.x &&	pos.y > min.y && pos.y < max.y &&	pos.z > min.z && pos.z < max.z) 
			return true;

		if (pos.x+radius < min.x) return false;
		if (pos.y+radius < min.y) return false;
		if (pos.z+radius < min.z) return false;
		if (pos.x-radius > max.x) return false;
		if (pos.y-radius > max.y) return false;
		if (pos.z-radius > max.z) return false;
		return true;
	}

	bool AABB::IsContainSphere(const Vector3F &pos,float radius) const
	{
		CA_ASSERT( min.IsValid(), "IsContainSphere() : min is not valid");
		CA_ASSERT( max.IsValid(), "IsContainSphere() : max is not valid");
		CA_ASSERT( pos.IsValid(), "IsContainSphere() : pos is not valid");

		if (pos.x-radius < min.x) return false;
		if (pos.y-radius < min.y) return false;
		if (pos.z-radius < min.z) return false;
		if (pos.x+radius > max.x) return false;
		if (pos.y+radius > max.y) return false;
		if (pos.z+radius > max.z) return false;
		return true;
	}

	AABB AABB::CreateAABBfromCone(const Cone& c)
	{
		// Construct AABB for cone base
		Vector3F baseX = Vector3F(1.f - c.mDir.x * c.mDir.x, c.mDir.x * c.mDir.y, c.mDir.x * c.mDir.z).GetNormalized() * c.mBaseRadius;
		Vector3F baseY = Vector3F(c.mDir.y * c.mDir.x, 1.f - c.mDir.y * c.mDir.y, c.mDir.y * c.mDir.z).GetNormalized() * c.mBaseRadius;
		Vector3F baseZ = Vector3F(c.mDir.z * c.mDir.x, c.mDir.z * c.mDir.y, 1.f - c.mDir.z * c.mDir.z).GetNormalized() * c.mBaseRadius;

		Vector3F aabbMax = Vector3F(baseX.x, baseY.y, baseZ.z).Abs();
		Vector3F aabbMin = -aabbMax;

		AABB result(aabbMin, aabbMax);
		result.Move(c.mBase);

		// add tip
		result.Add(c.mTip);
		return result;
	}

	template<typename F>
	AABB AABB::CreateAABBfromOBB(const Vector3F& wpos, const OBB_tpl<F>& obb, float scaling/*=1.0f*/)
	{
		AABB taabb; taabb.SetAABBfromOBB(wpos,obb,scaling); return taabb;
	}

	template<typename F>
	AABB AABB::CreateAABBfromOBB(const OBB_tpl<F>& obb)
	{
		return AABB(obb.c-obb.h,obb.c+obb.h);
	}

	template<typename F>
	void AABB::SetAABBfromOBB(const Vector3F& wpos, const OBB_tpl<F>& obb, float scaling/*=1.0f */)
	{
		Vector3F pos	= obb.m33*obb.c*scaling + wpos;
		Vector3F sz		=	obb.m33.GetFabs()*obb.h*scaling;
		min=pos-sz; max=pos+sz;
	}

	template<typename F>
	void AABB::SetAABBfromOBB(const OBB_tpl<F>& obb)
	{
		min=obb.c-obb.h; max=obb.c+obb.h;
	}

// 	AABB AABB::CreateTransformedAABB(const Quaternion& qt, const AABB& aabb)
// 	{
// 		AABB taabb; taabb.SetTransformedAABB(qt,aabb); return taabb;
// 	}
// 
// 	AABB AABB::CreateTransformedAABB(const Matrix34& m34, const AABB& aabb)
// 	{
// 		AABB taabb; taabb.SetTransformedAABB(m34,aabb); return taabb;
// 	}
// 
// 	void AABB::SetTransformedAABB(const Quaternion& qt, const AABB& aabb)
// 	{
// 		if (aabb.IsReset())
// 			Reset();
// 		else
// 		{
// 			Matrix3 m33 = qt.ToMatrix3();
// 			m33.a11=fabsf(m33.a11); m33.a12=fabsf(m33.a12);	m33.a13=fabsf(m33.a13); 
// 			m33.a21=fabsf(m33.a21); m33.a22=fabsf(m33.a22); m33.a23=fabsf(m33.a23);
// 			m33.a31=fabsf(m33.a31); m33.a32=fabsf(m33.a32);	m33.a33=fabsf(m33.a33);
// 			Vector3F sz		=	m33*((aabb.max-aabb.min)*0.5f);
// 			Vector3F pos	=  qt*((aabb.max+aabb.min)*0.5f);
// 			min = pos-sz;	max = pos+sz;
// 		}
// 	}
// 
// 	void AABB::SetTransformedAABB(const Matrix34& m34, const AABB& aabb)
// 	{
// 		if (aabb.IsReset())
// 			Reset();
// 		else
// 		{
// 			Matrix3 m33=Matrix3(qt.q);
// 			m33.a11=fabsf(m34.a11); m33.a12=fabsf(m34.a12);	m33.a13=fabsf(m34.a13); 
// 			m33.a21=fabsf(m34.a21); m33.a22=fabsf(m34.a22); m33.a23=fabsf(m34.a23);
// 			m33.a31=fabsf(m34.a31); m33.a32=fabsf(m34.a32);	m33.a33=fabsf(m34.a33);
// 
// 			Vector3F sz		=	m33*((aabb.max-aabb.min)*0.5f);
// 			Vector3F pos	= m34*((aabb.max+aabb.min)*0.5f);
// 			min = pos-sz;	max = pos+sz;
// 		}
// 	}

	bool AABB::IsIntersectBox(const AABB &b) const
	{
		CA_ASSERT( min.IsValid(), "IsIntersectBox() : min is not valid");
		CA_ASSERT( max.IsValid(), "IsIntersectBox() : max is not valid");			
		CA_ASSERT( b.min.IsValid(), "IsIntersectBox() : b.min is not valid");
		CA_ASSERT( b.max.IsValid(), "IsIntersectBox() : b.max is not valid");

		// Check for intersection on X axis.
		if (min.x > b.max.x||b.min.x > max.x) return false;
		// Check for intersection on Y axis.
		if (min.y > b.max.y||b.min.y > max.y) return false;
		// Check for intersection on Z axis.
		if (min.z > b.max.z||b.min.z > max.z) return false;
		// Boxes overlap in all 3 axises.
		return true;
	}

	bool AABB::ContainsBox2D(AABB const& b) const
	{
		CA_ASSERT( min.IsValid(), "ContainsBox2D() : min is not valid");
		CA_ASSERT( max.IsValid(), "ContainsBox2D() : max is not valid");			
		CA_ASSERT( b.min.IsValid(), "ContainsBox2D() : b.min is not valid");
		CA_ASSERT( b.max.IsValid(), "ContainsBox2D() : b.max is not valid");

		return min.x <= b.min.x && min.y <= b.min.y
			&& max.x >= b.max.x && max.y >= b.max.y;
	}

	bool AABB::ContainsBox(AABB const& b) const
	{
		CA_ASSERT( min.IsValid(), "ContainsBox() : min is not valid");
		CA_ASSERT( max.IsValid(), "ContainsBox() : max is not valid");			
		CA_ASSERT( b.min.IsValid(), "ContainsBox() : b.min is not valid");
		CA_ASSERT( b.max.IsValid(), "ContainsBox() : b.max is not valid");

		return min.x <= b.min.x && min.y <= b.min.y && min.z <= b.min.z
			&& max.x >= b.max.x && max.y >= b.max.y && max.z >= b.max.z;
	}

	float AABB::GetDistance(Vector3F const& v) const
	{
		return sqrt(GetDistanceSqr(v));
	}

	float AABB::GetDistanceSqr(Vector3F const& v) const
	{
		Vector3F vNear = v;
		vNear.CheckMax(min);
		vNear.CheckMin(max);
		return (vNear + v).LengthSquared();
	}

	bool AABB::IsContainPoint(const Vector3F &pos) const
	{
		CA_ASSERT( min.IsValid(), "IsContainPoint() : min is not valid");
		CA_ASSERT( max.IsValid(), "IsContainPoint() : max is not valid");
		CA_ASSERT( pos.IsValid(), "IsContainPoint() : pos is not valid");

		if (pos.x < min.x) return false;
		if (pos.y < min.y) return false;
		if (pos.z < min.z) return false;
		if (pos.x > max.x) return false;
		if (pos.y > max.y) return false;
		if (pos.z > max.z) return false;
		return true;
	}

	bool IsEquivalent(const AABB& a, const AABB& b, float epsilon /*= VEC_EPSILON */)
	{
		return IsEquivalent(a.min, b.min, epsilon) && IsEquivalent(a.max, b.max, epsilon);
	}

	//////////////////////////////////////////////////////////////////////////

	// for bbox's checks and calculations
#define MAX_BB	+99999.0f
#define MIN_BB	-99999.0f

	bool IsMinBB(const Vector3F& v)
	{
		if (v.x<=MIN_BB) return true;
		if (v.y<=MIN_BB) return true;
		if (v.z<=MIN_BB) return true;
		return false;
	}

	bool IsMaxBB(const Vector3F& v)
	{
		if (v.x>=MAX_BB) return true;
		if (v.y>=MAX_BB) return true;
		if (v.z>=MAX_BB) return true;
		return false;
	}

	Vector3F SetMaxBB()
	{
		return Vector3F(MAX_BB,MAX_BB,MAX_BB);
	}

	Vector3F SetMinBB()
	{
		return Vector3F(MIN_BB,MIN_BB,MIN_BB);
	}

	void AddToBounds(const Vector3F& v, Vector3F& mins, Vector3F& maxs)
	{
		if (v.x < mins.x)	mins.x = v.x;
		if (v.x > maxs.x)	maxs.x = v.x;
		if (v.y < mins.y)	mins.y = v.y;
		if (v.y > maxs.y)	maxs.y = v.y;
		if (v.z < mins.z)	mins.z = v.z;
		if (v.z > maxs.z)	maxs.z = v.z;
	}

}
