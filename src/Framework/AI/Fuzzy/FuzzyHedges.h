#ifndef FUZZY_HEDGES_H
#define FUZZY_HEDGES_H
//-----------------------------------------------------------------------------
//
//  Name:   FuzzyHedges.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   classes to implement fuzzy hedges 
//-----------------------------------------------------------------------------

#include "CA_Export.h"
#include "FuzzySet.h"
#include "FuzzyTerm.h"

namespace CasaEngine
{

	class CA_EXPORT FzVery : public FuzzyTerm
	{
	private:

		FuzzySet& m_Set;

		//prevent copying and assignment by clients
		FzVery(const FzVery& inst) :m_Set(inst.m_Set) {}
		FzVery& operator=(const FzVery&);


	public:

		FzVery(FzSet& ft) :m_Set(ft.m_Set) {}

		float GetDOM()const override
		{
			return m_Set.GetDOM() * m_Set.GetDOM();
		}

		FuzzyTerm* Clone()const override { return new FzVery(*this); }

		void ClearDOM() override { m_Set.ClearDOM(); }
		void ORwithDOM(float val) override { m_Set.ORwithDOM(val * val); }
	};

	///////////////////////////////////////////////////////////////////////////////
	class CA_EXPORT FzFairly : public FuzzyTerm
	{
	private:

		FuzzySet& m_Set;

		//prevent copying and assignment
		FzFairly(const FzFairly& inst) :m_Set(inst.m_Set) {}
		FzFairly& operator=(const FzFairly&);

	public:

		FzFairly(FzSet& ft) :m_Set(ft.m_Set) {}

		float GetDOM()const override
		{
			return sqrt(m_Set.GetDOM());
		}

		FuzzyTerm* Clone()const override { return new FzFairly(*this); }

		void ClearDOM() override { m_Set.ClearDOM(); }
		void ORwithDOM(float val) override { m_Set.ORwithDOM(sqrt(val)); }
	};

}

#endif