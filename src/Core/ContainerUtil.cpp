#include "Base.h"
#include "ContainerUtil.h"
#include <vector>
#include <map>
#include <iomanip>
#include <cmath>

namespace CasaEngine
{
	/*
	 *	
	 */
	inline double StandardDeviation(const std::vector<double>& v)
	{
		double sd      = 0.0;
		double average = Average(v);

		for (unsigned int i=0; i<v.size(); ++i)
		{     
			sd += (v[i] - average) * (v[i] - average);
		}

		sd = sd / v.size();

		return std::sqrt(sd);
	}

}