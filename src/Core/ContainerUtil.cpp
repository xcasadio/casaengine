#include "ContainerUtil.h"
#include <vector>
#include <cmath>

namespace CasaEngine
{
	inline double StandardDeviation(const std::vector<double>& v)
	{
		double sd = 0.0;
		const double average = Average(v);

		for (double i : v)
		{
			sd += (i - average) * (i - average);
		}

		sd = sd / v.size();

		return std::sqrt(sd);
	}
}