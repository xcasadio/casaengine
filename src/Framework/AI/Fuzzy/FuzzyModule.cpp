#pragma warning (disable:4786)

#include "Base.h"
#include "Log/LogManager.h"
#include <iostream>

#include "FuzzyModule.h"
#include "Macro.h"
#include "CA_Assert.h"
#include "Memory\MemoryAllocation.h"


namespace CasaEngine
{

//------------------------------ dtor -----------------------------------------
FuzzyModule::~FuzzyModule()
{
  VarMap::iterator curVar = m_Variables.begin();
  for (curVar; curVar != m_Variables.end(); ++curVar)
  {
    DELETE_AO curVar->second;
  }

  std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
  for (curRule; curRule != m_Rules.end(); ++curRule)
  {
    DELETE_AO *curRule;
  }
}

//----------------------------- AddRule ---------------------------------------
void FuzzyModule::AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence)
{
  m_Rules.push_back(new FuzzyRule(antecedent, consequence));
}

 
//-------------------------- CreateFLV ---------------------------
//
//  creates a new fuzzy variable and returns a reference to it
//-----------------------------------------------------------------------------
FuzzyVariable& FuzzyModule::CreateFLV(const std::string& VarName)
{
  m_Variables[VarName] = NEW_AO FuzzyVariable();

  return *m_Variables[VarName];
}


//---------------------------- WriteAllDOMs -----------------------------------
std::ostream& FuzzyModule::WriteAllDOMs(std::ostream& os)
{
  os << "\n\n";
  
  VarMap::iterator curVar = m_Variables.begin();
  for (curVar; curVar != m_Variables.end(); ++curVar)
  {
    os << "\n--------------------------- " << curVar->first;;
    curVar->second->WriteDOMs(os);

    os << std::endl;
  }

  return os;
}

//----------------------------- Fuzzify ---------------------------------------
//
//  this method calls the Fuzzify method of the variable with the same name
//  as the key
//-----------------------------------------------------------------------------
void FuzzyModule::Fuzzify( const std::string& NameOfFLV, float val )
{
	//first make sure the key exists
	CA_ASSERT(m_Variables.find(NameOfFLV) != m_Variables.end(), "<FuzzyModule::Fuzzify>:key not found");

	m_Variables[NameOfFLV]->Fuzzify(val);
}



//---------------------------- DeFuzzify --------------------------------------
//
//  given a fuzzy variable and a deffuzification method this returns a 
//  crisp value
//-----------------------------------------------------------------------------
inline float
	FuzzyModule::DeFuzzify(const std::string& NameOfFLV, DefuzzifyMethod method)
{
	//first make sure the key exists
	CA_ASSERT(m_Variables.find(NameOfFLV) != m_Variables.end(), "<FuzzyModule::DeFuzzifyMaxAv>:key not found");

	//clear the DOMs of all the consequents of all the rules
	SetConfidencesOfConsequentsToZero();

	//process the rules
	std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
	for (curRule; curRule != m_Rules.end(); ++curRule)
	{
		(*curRule)->Calculate();
	}

	//now defuzzify the resultant conclusion using the specified method
	switch (method)
	{
	case centroid:

		return m_Variables[NameOfFLV]->DeFuzzifyCentroid(NumSamples);

		break;

	case max_av:

		return m_Variables[NameOfFLV]->DeFuzzifyMaxAv();

		break;
	}

	return 0;
}



//-------------------------- ClearConsequents ---------------------------------
//
//  zeros the DOMs of the consequents of each rule
//-----------------------------------------------------------------------------
inline void FuzzyModule::SetConfidencesOfConsequentsToZero()
{
	std::vector<FuzzyRule*>::iterator curRule = m_Rules.begin();
	for (curRule; curRule != m_Rules.end(); ++curRule)
	{
		(*curRule)->SetConfidenceOfConsequentToZero();
	}
}

}
