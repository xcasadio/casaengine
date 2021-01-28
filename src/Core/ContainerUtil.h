#ifndef CONTAINERUTIL_H_
#define CONTAINERUTIL_H_

#include <vector>
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
	double Average(const std::vector<T>& v)
	{
		double average = 0.0;

		for (unsigned int i = 0; i < v.size(); ++i)
		{
			average += static_cast<double>(v[i]);
		}

		return average / static_cast<double>(v.size());
	}

	/*
	 *
	 */
	template <class container>
	void DeleteSTLContainer(container& c)
	{
		for (typename container::iterator it = c.begin(); it != c.end(); ++it)
		{
			DELETE_AO* it;
			*it = nullptr;
		}
	}

	/*
	 *
	 */
	template <class map>
	void DeleteSTLMap(map& m)
	{
		for (typename map::iterator it = m.begin(); it != m.end(); ++it)
		{
			DELETE_AO it->second;
			it->second = nullptr;
		}
	}
}

#endif // CONTAINERUTIL_H_
