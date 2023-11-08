#ifndef FUZZY_OPERATORS_H
#define FUZZY_OPERATORS_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzyOperators.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   classes to provide the fuzzy AND and OR operators to be used in
//          the creation of a fuzzy rule base
//-----------------------------------------------------------------------------
#include <vector>

#include "CA_Export.hpp"
#include  "FuzzyTerm.hpp"

namespace CasaEngine
{

	///////////////////////////////////////////////////////////////////////////////
	//
	//  a fuzzy AND operator class
	//
	///////////////////////////////////////////////////////////////////////////////
	class CA_EXPORT FzAND :
		public FuzzyTerm
	{
	private:

		//an instance of this class may AND together up to 4 terms
		std::vector<FuzzyTerm*> m_Terms;

		//disallow assignment
		FzAND& operator=(const FzAND&);

	public:

		~FzAND() override;

		//copy ctor
		FzAND(const FzAND& fa);

		//ctors accepting fuzzy terms.
		FzAND(FuzzyTerm& op1, FuzzyTerm& op2);
		FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3);
		FzAND(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4);

		//virtual ctor
		FuzzyTerm* Clone()const override { return new FzAND(*this); }

		float GetDOM()const override;
		void  ClearDOM() override;
		void  ORwithDOM(float val) override;
	};


	///////////////////////////////////////////////////////////////////////////////
	//
	//  a fuzzy OR operator class
	//
	///////////////////////////////////////////////////////////////////////////////
	class CA_EXPORT FzOR : public FuzzyTerm
	{
	private:

		//an instance of this class may AND together up to 4 terms
		std::vector<FuzzyTerm*> m_Terms;

		//no assignment op necessary
		FzOR& operator=(const FzOR&);

	public:

		~FzOR() override;

		//copy ctor
		FzOR(const FzOR& fa);

		//ctors accepting fuzzy terms.
		FzOR(FuzzyTerm& op1, FuzzyTerm& op2);
		FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3);
		FzOR(FuzzyTerm& op1, FuzzyTerm& op2, FuzzyTerm& op3, FuzzyTerm& op4);

		//virtual ctor
		FuzzyTerm* Clone()const override { return new FzOR(*this); }

		float GetDOM()const override;

		//unused
		void ClearDOM() override;
		void ORwithDOM(float val) override;
	};

}

#endif

