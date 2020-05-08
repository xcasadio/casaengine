#ifndef FUZZY_MODULE_H
#define FUZZY_MODULE_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   FuzzyModule.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   this class describes a fuzzy module: a collection of fuzzy variables
//          and the rules that operate on them.
//
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include <map>
#include <iosfwd>

#include "CA_Export.h"
#include "FuzzySet.h"
#include "FuzzyVariable.h"
#include "FuzzyRule.h"
#include "FuzzyOperators.h"
#include "FzSet.h"
#include "FuzzyHedges.h"

namespace CasaEngine
{

class CA_EXPORT FuzzyModule
{
private:

  typedef std::map<std::string, FuzzyVariable*> VarMap;
  
public:

  //you must pass one of these values to the defuzzify method. This module
  //only supports the MaxAv and centroid methods.
  enum DefuzzifyMethod{max_av, centroid};

  //when calculating the centroid of the fuzzy manifold this value is used
  //to determine how many cross-sections should be sampled
  enum {NumSamples = 15};

private:

  //a map of all the fuzzy variables this module uses
  VarMap                   m_Variables;

  //a vector containing all the fuzzy rules
  std::vector<FuzzyRule*>   m_Rules;
 

  //zeros the DOMs of the consequents of each rule. Used by Defuzzify()
  inline void SetConfidencesOfConsequentsToZero();


public:

  ~FuzzyModule();

  //creates a new 'empty' fuzzy variable and returns a reference to it.
  FuzzyVariable&  CreateFLV(const std::string& VarName);
  
  //adds a rule to the module
  void            AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence);

  //this method calls the Fuzzify method of the named FLV 
  inline void     Fuzzify(const std::string& NameOfFLV, float val);

  //given a fuzzy variable and a deffuzification method this returns a 
  //crisp value
  inline float    DeFuzzify(const std::string& key,
                            DefuzzifyMethod    method = max_av);
    
  
  //writes the DOMs of all the variables in the module to an output stream
  std::ostream&   WriteAllDOMs(std::ostream& os);

};

}

#endif