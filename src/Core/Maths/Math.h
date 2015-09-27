
#ifndef MATH_H_
#define MATH_H_

#include "Types.h"
#include <math.h>
#include <limits>

namespace CasaEngine
{

//===========================================================================
// General purpose utilities
//===========================================================================
#define MATH_PI				3.141592654f
#define MATH_2PI			6.283185307f
#define MATH_1_DIV_PI		0.318309886f
#define MATH_1_DIV_2PI		0.159154943f
#define MATH_PI_DIV_2		1.570796327f
#define MATH_PI_DIV_4		0.785398163f

#define MATH_ToRadian( degree ) ((degree) * (MATH_PI / 180.0f))
#define MATH_ToDegree( radian ) ((radian) * (180.0f / MATH_PI))

//===========================================================================
// 16 bit floating point numbers
//===========================================================================

#define MATH_16F_DIG          3                // # of decimal digits of precision
#define MATH_16F_EPSILON      4.8875809e-4f    // smallest such that 1.0 + epsilon != 1.0
#define MATH_16F_MANT_DIG     11               // # of bits in mantissa
#define MATH_16F_MAX          6.550400e+004    // max value
#define MATH_16F_MAX_10_EXP   4                // max decimal exponent
#define MATH_16F_MAX_EXP      15               // max binary exponent
#define MATH_16F_MIN          6.1035156e-5f    // min positive value
#define MATH_16F_MIN_10_EXP   (-4)             // min decimal exponent
#define MATH_16F_MIN_EXP      (-14)            // min binary exponent
#define MATH_16F_RADIX        2                // exponent radix
#define MATH_16F_ROUNDS       1                // addition rounding: near


	const int     MinInt    = (std::numeric_limits<int>::min)();
	const int     MaxInt    = (std::numeric_limits<int>::max)();
	const int     MinUInt    = (std::numeric_limits<unsigned int>::min)();
	const int     MaxUInt    = (std::numeric_limits<unsigned int>::max)();
	const double  MaxDouble = (std::numeric_limits<double>::max)();
	const double  MinDouble = (std::numeric_limits<double>::min)();
	const float   MaxFloat  = (std::numeric_limits<float>::max)();
	const float   MinFloat  = (std::numeric_limits<float>::min)();

	/**
	 * returns true if the parameter is equal to zero
	 */
	inline bool IsZero(double val)
	{
		return ( (-MinDouble < val) && (val < MinDouble) );
	}

	/**
	 * returns true if the parameter is equal to zero
	 */
	inline bool IsZero(float val)
	{
		return ( (-MinFloat < val) && (val < MinFloat) );
	}

	/**
	 * returns true is the third parameter is in the range described by the
	 * first two
	 */
	inline bool InRange(double start, double end, double val)
	{
		if (start < end)
		{
			if ( (val > start) && (val < end) ) return true;
			else return false;
		}

		else
		{
			if ( (val < start) && (val > end) ) return true;
			else return false;
		}
	}

	/**
	 * returns true is the third parameter is in the range described by the
	 * first two
	 */
	inline bool InRange(float start, float end, float val)
	{
		if (start < end)
		{
			if ( (val > start) && (val < end) ) return true;
			else return false;
		}

		else
		{
			if ( (val < start) && (val > end) ) return true;
			else return false;
		}
	}	

	/**
	 *
	 */
	inline double Sigmoid(double input, double response)
	{
		return ( 1.0 / ( 1.0 + exp(-input / response)));
	}

	/**
	 *
	 */
	inline float Sigmoid(float input, float response)
	{
		return ( 1.0f / ( 1.0f + exp(-input / response)));
	}

	//rounds a double up or down depending on its value
	inline int Rounded(double val)
	{
		int    integral = (int)val;
		double mantissa = val - integral;

		if (mantissa < 0.5)
		{
			return integral;
		}

		else
		{
			return integral + 1;
		}
	}

	//rounds a double up or down depending on its value
	inline int Rounded(float val)
	{
		int    integral = (int)val;
		float mantissa = val - integral;

		if (mantissa < 0.5f)
		{
			return integral;
		}

		else
		{
			return integral + 1;
		}
	}

	//rounds a double up or down depending on whether its 
	//mantissa is higher or lower than offset
	inline int RoundUnderOffset(double val, double offset)
	{
		int    integral = (int)val;
		double mantissa = val - integral;

		if (mantissa < offset)
		{
			return integral;
		}

		else
		{
			return integral + 1;
		}
	}

	//rounds a double up or down depending on whether its 
	//mantissa is higher or lower than offset
	inline int RoundUnderOffset(float val, float offset)
	{
		int    integral = (int)val;
		float mantissa = val - integral;

		if (mantissa < offset)
		{
			return integral;
		}

		else
		{
			return integral + 1;
		}
	}

	//compares two real numbers. Returns true if they are equal
	inline bool isEqual(float a, float b)
	{
		if (fabs(a-b) < 1E-12)
		{
			return true;
		}

		return false;
	}

	inline bool isEqual(double a, double b)
	{
		if (fabs(a-b) < 1E-12)
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

		if (arg < (T)minVal)
		{
			arg = (T)minVal;
		}

		if (arg > (T)maxVal)
		{
			arg = (T)maxVal;
		}
	}

	template<class T>
	inline int Sign(T a)
	{
		return (a < 0) ? -1 : 1;
	}

} // namespace CasaEngine

#endif // MATH_H_
