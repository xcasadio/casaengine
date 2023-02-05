#ifndef FUZZYSET_RIGHTSHOULDER_H
#define FUZZYSET_RIGHTSHOULDER_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzySet_RightShoulder.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   definition of a fuzzy set that has a right shoulder shape. (the
//          maximum value this variable can accept is *any* value greater than 
//          the midpoint.
//-----------------------------------------------------------------------------

#include "CA_Export.h"
#include "FuzzySet.h"

namespace CasaEngine
{

	class CA_EXPORT FuzzySet_RightShoulder : public FuzzySet
	{
	private:

		//the values that define the shape of this FLV
		float   m_fPeakPoint;
		float   m_fLeftOffset;
		float   m_fRightOffset;

	public:

		FuzzySet_RightShoulder(float peak,
			float LeftOffset,
			float RightOffset) :

			FuzzySet((peak + RightOffset + peak) / 2),
			m_fPeakPoint(peak),
			m_fLeftOffset(LeftOffset),
			m_fRightOffset(RightOffset)

		{}

		//this method calculates the degree of membership for a particular value
		float CalculateDOM(float val)const;
	};

}

#endif