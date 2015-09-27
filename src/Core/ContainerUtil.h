
#ifndef CONTAINERUTIL_H_
#define CONTAINERUTIL_H_

#include <vector>
#include <list>
#include <map>
#include <iomanip>
#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	inline double StandardDeviation(const std::vector<double>& v);

	/*
	 *	
	 */
	template <class T>
	inline double Average(const std::vector<T>& v)
	{
		double average = 0.0;

		for (unsigned int i=0; i < v.size(); ++i)
		{    
			average += (double)v[i];
		}

		return average / (double)v.size();
	}
	
	/*
	 *	
	 */
	template <class container>
	inline void DeleteSTLContainer(container& c)
	{
		for (typename container::iterator it = c.begin(); it!=c.end(); ++it)
		{
			DELETE_AO *it;
			*it = nullptr;
		}
	}

	/*
	 *	
	 */
	template <class map>
	inline void DeleteSTLMap(map& m)
	{
		for (typename map::iterator it = m.begin(); it!=m.end(); ++it)
		{
			DELETE_AO it->second;
			it->second = nullptr;
		}
	}

} // namespace CasaEngine

#endif // CONTAINERUTIL_H_
