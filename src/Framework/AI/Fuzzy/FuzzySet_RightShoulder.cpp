#include "FuzzySet_RightShoulder.h"

#include "Maths\Math.h"

namespace CasaEngine
{

float FuzzySet_RightShoulder::CalculateDOM(float val) const
{
  //test for the case where the left or right offsets are zero
  //(to prevent divide by zero errors below)
  if ( (isEqual(m_fRightOffset, 0.0f) && (isEqual(m_fPeakPoint, val))) ||
       (isEqual(m_fLeftOffset, 0.0f) && (isEqual(m_fPeakPoint, val))) )
  {
    return 1.0f;
  }
  
  //find DOM if left of center
  else if ( (val <= m_fPeakPoint) && (val > (m_fPeakPoint - m_fLeftOffset)) )
  {
    float grad = 1.0f / m_fLeftOffset;

    return grad * (val - (m_fPeakPoint - m_fLeftOffset));
  }
  //find DOM if right of center and less than center + right offset
  else if ( (val > m_fPeakPoint) && (val <= m_fPeakPoint+m_fRightOffset) )
  {
    return 1.0f;
  }

  else
  {
    return 0.0f;
  }
}

} 
