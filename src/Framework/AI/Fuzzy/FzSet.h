#ifndef PROXY_FUZZY_SET
#define PROXY_FUZZY_SET
//-----------------------------------------------------------------------------
//
//  Name:   FzSet.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to provide a proxy for a fuzzy set. The proxy inherits from
//          FuzzyTerm and therefore can be used to create fuzzy rules
//-----------------------------------------------------------------------------

#include "CA_Export.h"
#include "FuzzyTerm.h"
#include "FuzzySet.h"

namespace CasaEngine
{
	class FzAND;

	class CA_EXPORT FzSet : public FuzzyTerm
	{
	private:
  
	  //let the hedge classes be friends 
	  friend class FzVery;
	  friend class FzFairly;

	private:

	  //a reference to the fuzzy set this proxy represents
	  FuzzySet& m_Set;

	public:

	  FzSet(FuzzySet& fs):m_Set(fs){}
	  FzSet& operator = (const FzSet &rsh) { m_Set = rsh.m_Set; return *this;}

	  FuzzyTerm* Clone()const {return new FzSet(*this);}
	  float     GetDOM()const {return m_Set.GetDOM();}
	  void       ClearDOM(){m_Set.ClearDOM();}
	  void       ORwithDOM(float val){m_Set.ORwithDOM(val);}
	};

}

#endif
