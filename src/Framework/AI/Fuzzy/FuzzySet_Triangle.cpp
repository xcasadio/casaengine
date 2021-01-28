#include "Maths/Math.h"
#include "FuzzySet_Triangle.h"

namespace CasaEngine
{

float FuzzySet_Triangle::CalculateDOM(float val)const
{
  //test for the case where the triangle's left or right offsets are zero
  //(to prevent divide by zero errors below)
  if ( (isEqual(m_fRightOffset, 0.0f) && (isEqual(m_fPeakPoint, val))) ||
       (isEqual(m_fLeftOffset, 0.0f) && (isEqual(m_fPeakPoint, val))) )
  {
    return 1.0f;
  }

  //find DOM if left of center
  if ( (val <= m_fPeakPoint) && (val >= (m_fPeakPoint - m_fLeftOffset)) )
  {
    float grad = 1.0f / m_fLeftOffset;

    return grad * (val - (m_fPeakPoint - m_fLeftOffset));
  }
  //find DOM if right of center
  else if ( (val > m_fPeakPoint) && (val < (m_fPeakPoint + m_fRightOffset)) )
  {
    float grad = 1.0f / -m_fRightOffset;

    return grad * (val - m_fPeakPoint) + 1.0f;
  }
  //out of range of this FLV, return zero
  else
  {
    return 0.0f;
  }
}

}
