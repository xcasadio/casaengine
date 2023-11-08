#include  "Maths/Math.hpp"
#include  "FuzzySet_LeftShoulder.hpp"

namespace CasaEngine
{

	float FuzzySet_LeftShoulder::CalculateDOM(float val)const
	{
		//test for the case where the left or right offsets are zero
		//(to prevent divide by zero errors below)
		if (Math::isEqual(m_fRightOffset, 0.0f) && Math::isEqual(m_fPeakPoint, val) ||
			Math::isEqual(m_fLeftOffset, 0.0f) && Math::isEqual(m_fPeakPoint, val))
		{
			return 1.0f;
		}

		//find DOM if right of center
		if (val >= m_fPeakPoint && val < m_fPeakPoint + m_fRightOffset)
		{
			float grad = 1.0f / -m_fRightOffset;

			return grad * (val - m_fPeakPoint) + 1.0f;
		}

		//find DOM if left of center
		if (val < m_fPeakPoint && val >= m_fPeakPoint - m_fLeftOffset)
		{
			return 1.0f;
		}

		//out of range of this FLV, return zero
		return 0.0f;
	}

}
