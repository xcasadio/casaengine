#ifndef FUZZYTERM_H
#define FUZZYTERM_H

//-----------------------------------------------------------------------------
//
//  Name:   FuzzyTerm.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   abstract class to provide an interface for classes able to be
//          used as terms in a fuzzy if-then rule base.
//-----------------------------------------------------------------------------

#include "CA_Export.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{

class CA_EXPORT FuzzyTerm :
	public AllocatedObject<FuzzyTerm>
{  
public:

  virtual ~FuzzyTerm(){}

  //all terms must implement a virtual constructor
  virtual FuzzyTerm* Clone()const = 0;

  //retrieves the degree of membership of the term
  virtual float      GetDOM()const=0;

  //clears the degree of membership of the term
  virtual void       ClearDOM()=0;

  //method for updating the DOM of a consequent when a rule fires
  virtual void       ORwithDOM(float val)=0;

   
};

} //  namespace CasaEngine

#endif