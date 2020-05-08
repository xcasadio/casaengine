
#include "Base.h"
#include "Maths/Math.h"
#include "FuzzySet_LeftShoulder.h"

namespace CasaEngine
{

float FuzzySet_LeftShoulder::CalculateDOM(float val)const
{
  //test for the case where the left or right offsets are zero
  //(to prevent divide by zero errors below)
  if ( (isEqual(m_fRightOffset, 0.0f) && (isEqual(m_fPeakPoint, val))) ||
       (isEqual(m_fLeftOffset, 0.0f) && (isEqual(m_fPeakPoint, val))) )
  {
    return 1.0f;
  }

  //find DOM if right of center
  else if ( (val >= m_fPeakPoint) && (val < (m_fPeakPoint + m_fRightOffset)) )
  {
    float grad = 1.0f / -m_fRightOffset;

    return grad * (val - m_fPeakPoint) + 1.0f;
  }

  //find DOM if left of center
  else if ( (val < m_fPeakPoint) && (val >= m_fPeakPoint-m_fLeftOffset) )
  {
    return 1.0f;
  }

  //out of range of this FLV, return zero
  else
  {
    return 0.0f;
  }

}

}
