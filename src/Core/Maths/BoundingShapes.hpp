#ifndef BOUNDINGSHAPE_H
#define BOUNDINGSHAPE_H

#include  "Matrix3.hpp"
#include  "Vector3.hpp"
#include  "Quaternion.hpp"

namespace CasaEngine
{
	struct AABB;
	template <typename F> struct OBB_tpl;

	struct Sphere;
	struct Cone;

	/**
	 *
	 */
	struct Cone
	{
		Vector3 mTip;
		Vector3 mDir;
		Vector3 mBase;

		float mHeight{};
		float mBaseRadius{};

		Cone();
		Cone(const Vector3& tip, const Vector3& dir, float height, float baseRadius);
	};

	/**
	 *
	 */
	struct AABB
	{
		Vector3 min;
		Vector3 max;

		/// default AABB constructor (without initialization)
		AABB();
		enum type_reset { RESET };
		// AABB aabb(RESET) generates a reset aabb
		AABB(type_reset);
		explicit AABB(float radius);
		explicit AABB(const Vector3& v);
		AABB(const Vector3& v, float radius);
		AABB(const Vector3& vmin, const Vector3& vmax);
		AABB(const AABB& aabb);
		AABB(const Vector3* points, int num);

		//! Reset Bounding box before calculating bounds.
		//! These values ensure that Add() functions work correctly for Reset bbs, without additional comparisons.
		void Reset();

		bool IsReset() const;

		float IsResetSel(float ifReset, float ifNotReset) const;

		//! Check if bounding box is empty (Zero volume).
		bool IsEmpty() const;

		//! Check if bounding box has valid, non zero volume
		bool IsNonZero() const;

		Vector3 GetCenter() const;

		Vector3 GetSize() const;

		float GetRadius() const;

		float GetRadiusSqr() const;

		float GetVolume() const;

		void Add(const Vector3& v);

		void Add(const Vector3& v, float radius);

		void Add(const AABB& bb);

		void Move(const Vector3& v);

		void Expand(Vector3 const& v);

		// Augment the box on all sides by a box.
		void Augment(AABB const& bb);

		void ClipToBox(AABB const& bb);

		void ClipMoveToBox(AABB const& bb);

		//! Check if this bounding box overlap with bounding box of sphere.
		bool IsOverlapSphereBounds(const Vector3& pos, float radius) const;

		//! Check if this bounding box contain sphere within itself.
		bool IsContainSphere(const Vector3& pos, float radius) const;

		//! Check if this bounding box contains a point within itself.
		bool IsContainPoint(const Vector3& pos) const;

		float GetDistanceSqr(Vector3 const& v) const;

		float GetDistance(Vector3 const& v) const;

		bool ContainsBox(AABB const& b) const;

		bool ContainsBox2D(AABB const& b) const;

		// Check two bounding boxes for intersection.
		bool IsIntersectBox(const AABB& b) const;

		/*!
		* calculate the new bounds of a transformed AABB
		*
		* Example:
		* AABB aabb = AABB::CreateAABBfromOBB(m34,aabb);
		*
		* return values:
		*  expanded AABB in world-space
		*/
		// 	void SetTransformedAABB( const Matrix34& m34, const AABB& aabb );
		// 	static AABB CreateTransformedAABB( const Matrix34& m34, const AABB& aabb );
		//
		// 	void SetTransformedAABB( const Quaternion& qt, const AABB& aabb );
		// 	static AABB CreateTransformedAABB( const Quaternion& qt, const AABB& aabb );

			//create an AABB using just the extensions of the OBB and ignore the orientation.
		template<typename F>
		void SetAABBfromOBB(const OBB_tpl<F>& obb);
		template<typename F>
		static AABB CreateAABBfromOBB(const OBB_tpl<F>& obb);

		/*!
		* converts an OBB into an tight fitting AABB
		*
		* Example:
		* AABB aabb = AABB::CreateAABBfromOBB(wposition,obb,1.0f);
		*
		* return values:
		*  expanded AABB in world-space
		*/
		template<typename F>
		void SetAABBfromOBB(const Vector3& wpos, const OBB_tpl<F>& obb, float scaling = 1.0f);
		template<typename F>
		static AABB CreateAABBfromOBB(const Vector3& wpos, const OBB_tpl<F>& obb, float scaling = 1.0f);

		/* Converts a Cone into a tight fitting AABB */
		static AABB CreateAABBfromCone(const Cone& c);
	};

	bool IsEquivalent(const AABB& a, const AABB& b, float epsilon = Math::Epsilon);

	/**
	 *
	 */
	template <typename F> struct OBB_tpl
	{
		Matrix3 m33; //orientation vectors
		Vector3 h;				//half-length-vector
		Vector3 c;				//center of obb

		//default OBB constructor (without initialization)
		inline OBB_tpl() {}

		inline void SetOBB(const Matrix3& matrix, const Vector3& hlv, const Vector3& center) { m33 = matrix; h = hlv; c = center; }
		inline static OBB_tpl<F> CreateOBB(const Matrix3& m33, const Vector3& hlv, const Vector3& center)
		{
			OBB_tpl<float> obb; obb.m33 = m33; obb.h = hlv; obb.c = center; return obb;
		}

		inline void SetOBBfromAABB(const Matrix3& mat33, const AABB& aabb)
		{
			m33 = mat33;
			h = (aabb.max - aabb.min) * 0.5f;	//calculate the half-length-vectors
			c = (aabb.max + aabb.min) * 0.5f;	//the center is relative to the PIVOT
		}
		inline void SetOBBfromAABB(const Quaternion& q, const AABB& aabb)
		{
			m33 = Matrix3(q);
			h = (aabb.max - aabb.min) * 0.5f;	//calculate the half-length-vectors
			c = (aabb.max + aabb.min) * 0.5f;	//the center is relative to the PIVOT
		}
		inline static OBB_tpl<F> CreateOBBfromAABB(const Matrix3& m33, const AABB& aabb)
		{
			OBB_tpl<float> obb; obb.SetOBBfromAABB(m33, aabb); return obb;
		}
		inline static OBB_tpl<F> CreateOBBfromAABB(const Quaternion& q, const AABB& aabb)
		{
			OBB_tpl<float> obb; obb.SetOBBfromAABB(q, aabb); return obb;
		}

		~OBB_tpl() {};
	};

	//! checks if this has been set to minBB
	bool IsMinBB(const Vector3& v);

	//! checks if this has been set to maxBB
	bool IsMaxBB(const Vector3& v);

	Vector3 SetMaxBB();
	Vector3 SetMinBB();

	void AddToBounds(const Vector3& v, Vector3& mins, Vector3& maxs);
}

#endif