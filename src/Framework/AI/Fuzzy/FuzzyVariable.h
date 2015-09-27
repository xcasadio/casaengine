#ifndef FLV_H
#define FLV_H

#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   FuzzyVariable.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   Class to define a fuzzy linguistic variable (FLV).
//
//          An FLV comprises of a number of fuzzy sets  
//
//-----------------------------------------------------------------------------

#include "CA_Export.h"

#include "Memory/MemoryAllocation.h"

#include <map>
#include <iosfwd>
#include <string>

namespace CasaEngine
{

	class FuzzySet;
	class FzSet;
	class FuzzyModule;


	class CA_EXPORT FuzzyVariable :
		public AllocatedObject<FuzzyVariable>
	{
	private:
  
	  typedef std::map<std::string, FuzzySet*>  MemberSets;
    
	private:
  
	  //disallow copies
	  FuzzyVariable(const FuzzyVariable&);
	  FuzzyVariable& operator=(const FuzzyVariable&);

	private:
 
	  //a map of the fuzzy sets that comprise this variable
	  MemberSets   m_MemberSets;

	  //the minimum and maximum value of the range of this variable
	  float        m_fMinRange;
	  float        m_fMaxRange;
  

	  //this method is called with the upper and lower bound of a set each time a
	  //new set is added to adjust the upper and lower range values accordingly
	  void AdjustRangeToFit(float min, float max);

	  //a client retrieves a reference to a fuzzy variable when an instance is
	  //created via FuzzyModule::CreateFLV(). To prevent the client from deleting
	  //the instance the FuzzyVariable destructor is made private and the 
	  //FuzzyModule class made a friend.
	  ~FuzzyVariable();

	  friend class FuzzyModule;


	public:

	  FuzzyVariable():m_fMinRange(0.0),m_fMaxRange(0.0){}
  
	  //the following methods create instances of the sets named in the method
	  //name and add them to the member set map. Each time a set of any type is
	  //added the m_fMinRange and m_fMaxRange are adjusted accordingly. All of the
	  //methods return a proxy class representing the newly created instance. This
	  //proxy set can be used as an operand when creating the rule base.
	  FzSet  AddLeftShoulderSet(std::string name, float minBound, float peak, float maxBound);

	  FzSet  AddRightShoulderSet(std::string name, float minBound, float peak, float maxBound);

	  FzSet  AddTriangularSet(std::string name,
								 float       minBound,
								 float       peak,
								 float       maxBound);

	  FzSet  AddSingletonSet(std::string name,
								float       minBound,
								float       peak,
								float       maxBound);
  
  
	  //fuzzify a value by calculating its DOM in each of this variable's subsets
	  void        Fuzzify(float val);

	  //defuzzify the variable using the max average method
	  float       DeFuzzifyMaxAv()const;

	  //defuzzify the variable using the centroid method
	  float       DeFuzzifyCentroid(int NumSamples)const;



	  std::ostream& WriteDOMs(std::ostream& os);
	};


} // namespace CasaEngine
      
#endif // FLV_H
