#ifndef FUZZYSET_SINGLETON_H
#define FUZZYSET_SINGLETON_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzySet_Singleton.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   This defines a fuzzy set that is a singleton (a range
//          over which the DOM is always 1.0)
//-----------------------------------------------------------------------------

#include "CA_Export.h"
#include "FuzzySet.h"

namespace CasaEngine
{

class CA_EXPORT FuzzySet_Singleton : public FuzzySet
{
private:

    //the values that define the shape of this FLV
  float   m_fMidPoint;
  float   m_fLeftOffset;
  float   m_fRightOffset;

public:
  
  FuzzySet_Singleton(float       mid,
                     float       lft,
                     float       rgt):FuzzySet(mid),
                                      m_fMidPoint(mid),
                                      m_fLeftOffset(lft),
                                      m_fRightOffset(rgt)
  {}

  //this method calculates the degree of membership for a particular value
  float     CalculateDOM(float val)const; 
};

} // namespace CasaEngine

#endif
