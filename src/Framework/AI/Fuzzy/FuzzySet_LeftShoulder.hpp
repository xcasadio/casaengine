#ifndef FUZZYSET_LEFTSHOULDER_H
#define FUZZYSET_LEFTSHOULDER_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzySet_LeftShoulder.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   definition of a fuzzy set that has a left shoulder shape. (the
//          minimum value this variable can accept is *any* value less than the
//          midpoint.
//-----------------------------------------------------------------------------

#include "CA_Export.hpp"
#include  "FuzzySet.hpp"

namespace CasaEngine
{

	class CA_EXPORT FuzzySet_LeftShoulder : public FuzzySet
	{
	private:

		//the values that define the shape of this FLV
		float   m_fPeakPoint;
		float   m_fRightOffset;
		float   m_fLeftOffset;

	public:

		FuzzySet_LeftShoulder(float peak,
			float LeftOffset,
			float RightOffset) :

			FuzzySet((peak - LeftOffset + peak) / 2),
			m_fPeakPoint(peak),
			m_fLeftOffset(LeftOffset),
			m_fRightOffset(RightOffset)
		{}

		//this method calculates the degree of membership for a particular value
		float CalculateDOM(float val)const override;
	};

}

#endif