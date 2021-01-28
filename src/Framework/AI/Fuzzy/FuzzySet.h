
#ifndef FUZZYSET_H
#define FUZZYSET_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzySet.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to define an interface for a fuzzy set
//-----------------------------------------------------------------------------

#include "CA_Export.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{

class CA_EXPORT FuzzySet :
	public AllocatedObject<FuzzySet>
{
protected:
  
  //this will hold the degree of membership of a given value in this set 
  float        m_fDOM;

  //this is the maximum of the set's membership function. For instamce, if
  //the set is triangular then this will be the peak point of the triangular.
  //if the set has a plateau then this value will be the mid point of the 
  //plateau. This value is set in the constructor to avoid run-time
  //calculation of mid-point values.
  float        m_fRepresentativeValue;

public:

  FuzzySet(float RepVal);

  //return the degree of membership in this set of the given value. NOTE,
  //this does not set m_fDOM to the DOM of the value passed as the parameter.
  //This is because the centroid defuzzification method also uses this method
  //to determine the DOMs of the values it uses as its sample points.
  virtual float      CalculateDOM(float val)const = 0;

  //if this fuzzy set is part of a consequent FLV, and it is fired by a rule 
  //then this method sets the DOM (in this context, the DOM represents a
  //confidence level)to the maximum of the parameter value or the set's 
  //existing m_fDOM value
  void               ORwithDOM(float val);

  //accessor methods
  float             GetRepresentativeVal()const;
  
  void               ClearDOM();
  float             GetDOM()const;
  void               SetDOM(float val);
};

}

#endif