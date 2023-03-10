#ifndef FUZZYSET_TRIANGLE_H
#define FUZZYSET_TRIANGLE_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzySetTriangle.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   This is a simple class to define fuzzy sets that have a triangular 
//          shape and can be defined by a mid point, a left displacement and a
//          right displacement. 
//-----------------------------------------------------------------------------

#include "CA_Export.h"
#include "FuzzySet.h"

namespace CasaEngine
{

	class CA_EXPORT FuzzySet_Triangle :
		public FuzzySet
	{
	private:

		//the values that define the shape of this FLV
		float   m_fMidPoint;
		float   m_fLeftOffset;
		float   m_fRightOffset;

	public:

		FuzzySet_Triangle(std::string name,
			float mid,
			float lft,
			float rgt) :FuzzySet(name),
			m_fMidPoint(mid),
			m_fLeftOffset(lft),
			m_fRightOffset(rgt)
		{}

		//this method calculates the degree of membership for a particular value
		inline float CalculateDOM(float val);

		//for a triangular set this is the range value at the midpoint
		float RepresentativeValue()const { return m_fMidPoint; }

	};

	///////////////////////////////////////////////////////////////////////////////

	inline
		float FuzzySet_Triangle::CalculateDOM(float val)
	{
		//test for the case where the triangle's left or right offsets are zero
		if (Math::isEqual(m_fRightOffset, 0.0) && Math::isEqual(m_fMidPoint, val) ||
			Math::isEqual(m_fLeftOffset, 0.0) && Math::isEqual(m_fMidPoint, val))
		{
			return 1.0;
		}

		//find DOM if left of center
		if (val <= m_fMidPoint && val > m_fMidPoint - m_fLeftOffset)
		{
			float grad = 1.0 / m_fLeftOffset;

			return grad * (val - (m_fMidPoint - m_fLeftOffset));
		}
		//find DOM if right of center
		if (val > m_fMidPoint && val < m_fMidPoint + m_fRightOffset)
		{
			float grad = 1.0 / -m_fRightOffset;

			return grad * (val - m_fMidPoint) + 1.0;
		}
		//out of range of this FLV, return zero
		return 0.0;
	}

}

#endif