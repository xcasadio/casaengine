
#include "Base.h"
#include "Log/LogManager.h"

#include <string>

#include "FuzzySet.h"
#include "Macro.h"
#include "CA_Assert.h"

namespace CasaEngine
{

  FuzzySet::FuzzySet(float RepVal):m_fDOM(0.0), m_fRepresentativeValue(RepVal){}


  //if this fuzzy set is part of a consequent FLV, and it is fired by a rule 
  //then this method sets the DOM (in this context, the DOM represents a
  //confidence level)to the maximum of the parameter value or the set's 
  //existing m_fDOM value
  void               FuzzySet::ORwithDOM(float val){if (val > m_fDOM) m_fDOM = val;}

  //accessor methods
  float             FuzzySet::GetRepresentativeVal()const{return m_fRepresentativeValue;}
  
  void               FuzzySet::ClearDOM(){m_fDOM = 0.0;}  
  float             FuzzySet::GetDOM()const{return m_fDOM;}
  void               FuzzySet::SetDOM(float val)
  {
    CA_ASSERT((val <=1) && (val >= 0), "<FuzzySet::SetDOM>: invalid value");
    m_fDOM = val;
  }

} // namespace CasaEngine
