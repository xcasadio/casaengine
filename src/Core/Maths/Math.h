#ifndef MATH_H_
#define MATH_H_

#include <cmath>
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
	template<typename T>
	bool IsZero(T val)
	{
		return -std::numeric_limits<T>::min < val && val < std::numeric_limits<T>::min;
	}

	/**
	 * returns true is the third parameter is in the range described by the
	 * first two
	 */
	template<typename T>
	bool InRange(T start, T end, T val)
	{
		if (start < end)
		{
			return (val > start && val < end);
		}

		return (val < start && val > end);
	}

	/**
	 *
	 */
	template<typename T>
	double Sigmoid(T input, T response)
	{
		return static_cast<T>(1.0) / (static_cast<T>(1.0) + exp(-input / response));
	}

	//rounds a double up or down depending on its value
	template<typename T>
	int Rounded(T val)
	{
		return RoundUnderOffset(val, static_cast<T>(0.5));
	}

	//rounds a double up or down depending on whether its
	//mantissa is higher or lower than offset
	template<typename T>
	int RoundUnderOffset(T val, T offset)
	{
		int    integral = static_cast<int>(val);
		T mantissa = val - integral;

		if (mantissa < offset)
		{
			return integral;
		}
		return integral + 1;
	}

	//compares two real numbers. Returns true if they are equal
	inline bool isEqual(float a, float b)
	{
		if (fabsf(a - b) < 1E-12)
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
	bool isNaN(T val)
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
	void Clamp(T& arg, const U& minVal, const V& maxVal)
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
	int Sign(T a)
	{
		return (a < static_cast<T>(0)) ? static_cast<T>(-1) : static_cast<T>(1);
	}

	inline unsigned int NearestPowerOfTwo(unsigned int value)
	{
		unsigned int Temp = value;
		unsigned int PowerOfTwo = 0;

		while (Temp > 1)
		{
			Temp >>= 1;
			++PowerOfTwo;
		}

		const unsigned int result = 1 << PowerOfTwo;

		return result == value ? result : result << 1;
	}
}

#endif
