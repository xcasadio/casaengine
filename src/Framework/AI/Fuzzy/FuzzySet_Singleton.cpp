#include  "FuzzySet_Singleton.hpp"

namespace CasaEngine
{

	float FuzzySet_Singleton::CalculateDOM(float val)const
	{
		if (val >= m_fMidPoint - m_fLeftOffset &&
			val <= m_fMidPoint + m_fRightOffset)
		{
			return 1.0;
		}

		//out of range of this FLV, return zero
		return 0.0;
	}

}
