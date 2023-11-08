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

#include "CA_Export.hpp"
#include  "FuzzySet.hpp"

namespace CasaEngine
{

	class CA_EXPORT FuzzySet_Triangle : public FuzzySet
	{
	private:

		//the values that define the shape of this FLV
		float   m_fPeakPoint;
		float   m_fLeftOffset;
		float   m_fRightOffset;

	public:

		FuzzySet_Triangle(float mid,
			float lft,
			float rgt) :FuzzySet(mid),
			m_fPeakPoint(mid),
			m_fLeftOffset(lft),
			m_fRightOffset(rgt)
		{}

		//this method calculates the degree of membership for a particular value
		float CalculateDOM(float val)const override;
	};

}

#endif