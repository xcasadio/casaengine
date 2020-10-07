#ifndef MATH_H_
#define MATH_H_

#include "Types.h"
#include <math.h>
#include <limits>

namespace CasaEngine
{
	constexpr float kPi = 3.1415926535897932384626433832795f;
	constexpr float Pi = 3.141592654f;
	constexpr float MATH_2PI = 6.283185307f;
	constexpr float MATH_1_DIV_PI = 0.318309886f;
	constexpr float MATH_1_DIV_2PI = 0.159154943f;
	constexpr float MATH_PI_DIV_2 = 1.570796327f;
	constexpr float MATH_PI_DIV_4 = 0.785398163f;

	constexpr float Epsilon = 4.8875809e-4f;  // smallest such that 1.0 + epsilon != 1.0

	constexpr int     MinInt = (std::numeric_limits<int>::min)();
	constexpr int     MaxInt = (std::numeric_limits<int>::max)();
	constexpr unsigned int MinUInt = (std::numeric_limits<unsigned int>::min)();
	constexpr unsigned int MaxUInt = (std::numeric_limits<unsigned int>::max)();
	constexpr double  MaxDouble = (std::numeric_limits<double>::max)();
	constexpr double  MinDouble = (std::numeric_limits<double>::min)();
	constexpr float   MaxFloat = (std::numeric_limits<float>::max)();
	constexpr float   MinFloat = (std::numeric_limits<float>::min)();


	inline float ToRadian(float degree)
	{
		return degree * (Pi / 180.0f);
	}

	inline float ToDegree(float radian)
	{
		return radian * (180.0f / Pi);
	}

	/**
	 * returns true if the parameter is equal to zero
	 */
	inline bool IsZero(double val)
	{
		return -MinDouble < val&& val < MinDouble;
	}

	/**
	 * returns true if the parameter is equal to zero
	 */
	inline bool IsZero(float val)
	{
		return -MinFloat < val&& val < MinFloat;
	}

	/**
	 * returns true is the third parameter is in the range described by the
	 * first two
	 */
	inline bool InRange(double start, double end, double val)
	{
		if (start < end)
		{
			if (val > start && val < end) return true;
			return false;
		}
		if (val < start && val > end) return true;
		return false;
	}

	/**
	 * returns true is the third parameter is in the range described by the
	 * first two
	 */
	inline bool InRange(float start, float end, float val)
	{
		if (start < end)
		{
			if (val > start && val < end) return true;
			return false;
		}
		if (val < start && val > end) return true;
		return false;
	}

	/**
	 *
	 */
	inline double Sigmoid(double input, double response)
	{
		return 1.0 / (1.0 + exp(-input / response));
	}

	/**
	 *
	 */
	inline float Sigmoid(float input, float response)
	{
		return 1.0f / (1.0f + static_cast<float>(exp(-input / response)));
	}

	//rounds a double up or down depending on its value
	inline int Rounded(double val)
	{
		int    integral = static_cast<int>(val);
		double mantissa = val - integral;

		if (mantissa < 0.5)
		{
			return integral;
		}
		return integral + 1;
	}

	//rounds a double up or down depending on its value
	inline int Rounded(float val)
	{
		int    integral = static_cast<int>(val);
		float mantissa = val - integral;

		if (mantissa < 0.5f)
		{
			return integral;
		}
		return integral + 1;
	}

	//rounds a double up or down depending on whether its 
	//mantissa is higher or lower than offset
	inline int RoundUnderOffset(double val, double offset)
	{
		int    integral = static_cast<int>(val);
		double mantissa = val - integral;

		if (mantissa < offset)
		{
			return integral;
		}
		return integral + 1;
	}

	//rounds a double up or down depending on whether its 
	//mantissa is higher or lower than offset
	inline int RoundUnderOffset(float val, float offset)
	{
		int    integral = static_cast<int>(val);
		float mantissa = val - integral;

		if (mantissa < offset)
		{
			return integral;
		}
		return integral + 1;
	}

	//compares two real numbers. Returns true if they are equal
	inline bool isEqual(float a, float b)
	{
		if (fabs(a - b) < 1E-12)
		{
			return true;
		}

		return false;
	}

	inline bool isEqual(double a, double b)
	{
		if (fabs(a - b) < 1E-12)
		{
			return true;
		}

		return false;
	}


	/**
	 * returns true if the value is a NaN
	 */
	template <typename T>
	inline bool isNaN(T val)
	{
		return val != val;
	}

	/**
	 * returns the maximum of two values
	 */
	template <class T>
	T MaxOf(const T& v1, const T& v2)
	{
		return v1 > v2 ? v1 : v2;
	}

	/**
	 * returns the minimum of two values
	 */
	template <class T>
	T MinOf(const T& v1, const T& v2)
	{
		return v1 < v2 ? v1 : v2;
	}

	/**
	 * clamps the first argument between the second two
	 */
	template <class T, class U, class V>
	inline void Clamp(T& arg, const U& minVal, const V& maxVal)
	{
		//CA_ASSERT( (static_cast<double>(minVal) < static_cast<double>(maxVal)) && "<Clamp> MaxVal < MinVal");

		if (arg < static_cast<T>(minVal))
		{
			arg = static_cast<T>(minVal);
		}

		if (arg > static_cast<T>(maxVal))
		{
			arg = static_cast<T>(maxVal);
		}
	}

	template<class T>
	inline int Sign(T a)
	{
		return (a < 0) ? -1 : 1;
	}

	inline unsigned int NearestPowerOfTwo(unsigned int Value)
	{
		unsigned int Temp = Value;
		unsigned int PowerOfTwo = 0;

		while (Temp > 1)
		{
			Temp >>= 1;
			++PowerOfTwo;
		}

		unsigned int Retval = 1 << PowerOfTwo;

		return Retval == Value ? Retval : Retval << 1;
	}

}

#endif // MATH_H_
