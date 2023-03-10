#pragma once

#include <cmath>
#include <limits>

namespace CasaEngine
{
	class Math
	{
	public:
		constexpr static float kPi = 3.1415926535897932384626433832795f;
		constexpr static float Pi = 3.141592654f;
		constexpr static float MATH_2PI = 6.283185307f;
		constexpr static float MATH_1_DIV_PI = 0.318309886f;
		constexpr static float MATH_1_DIV_2PI = 0.159154943f;
		constexpr static float PI_OVER_2 = 1.570796327f;
		constexpr static float PI_OVER_4 = 0.785398163f;

		constexpr static float Epsilon = 4.8875809e-4f;  // smallest such that 1.0 + epsilon != 1.0

		constexpr static int     MinInt = (std::numeric_limits<int>::min)();
		constexpr static int     MaxInt = (std::numeric_limits<int>::max)();
		constexpr static unsigned int MinUInt = (std::numeric_limits<unsigned int>::min)();
		constexpr static unsigned int MaxUInt = (std::numeric_limits<unsigned int>::max)();
		constexpr static double  MaxDouble = (std::numeric_limits<double>::max)();
		constexpr static double  MinDouble = (std::numeric_limits<double>::min)();
		constexpr static float   MaxFloat = (std::numeric_limits<float>::max)();
		constexpr static float   MinFloat = (std::numeric_limits<float>::min)();

		inline static float ToRadian(float degree)
		{
			return degree * (Pi / 180.0f);
		}

		inline static float ToDegree(float radian)
		{
			return radian * (180.0f / Pi);
		}

		/**
		 * returns true if the parameter is equal to zero
		 */
		template<typename T>
		static bool IsZero(T val)
		{
			return -std::numeric_limits<T>::min < val&& val < std::numeric_limits<T>::min;
		}

		/**
		 * returns true is the third parameter is in the range described by the
		 * first two
		 */
		template<typename T>
		static bool InRange(T start, T end, T val)
		{
			if (start < end)
			{
				return val > start && val < end;
			}

			return val < start&& val > end;
		}

		/**
		 *
		 */
		template<typename T>
		static double Sigmoid(T input, T response)
		{
			return static_cast<T>(1.0) / (static_cast<T>(1.0) + exp(-input / response));
		}

		//rounds a double up or down depending on its value
		template<typename T>
		static int Rounded(T val)
		{
			return RoundUnderOffset(val, static_cast<T>(0.5));
		}

		//rounds a double up or down depending on whether its
		//mantissa is higher or lower than offset
		template<typename T>
		static int RoundUnderOffset(T val, T offset)
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
		inline static bool isEqual(float a, float b)
		{
			if (fabsf(a - b) < Epsilon)
			{
				return true;
			}

			return false;
		}

		inline static bool isEqual(double a, double b)
		{
			if (fabs(a - b) < Epsilon)
			{
				return true;
			}

			return false;
		}

		inline static float NaN() noexcept
		{
			return std::numeric_limits<float>::signaling_NaN();
		}

		template <typename T>
		bool IsNaN(T val)
		{
			return /*std::isnan(val);*/val != val;
		}

		template <typename T>
		static bool IsPositiveInfinity(T val)
		{
			return /*std::isinf(val)*/val >= MaxFloat && val > 0.0f;
			//return val == std::numeric_limits<float>::max();
		}

		template <typename T>
		static bool IsNegativeInfinity(T val)
		{
			return /*std::isinf(val)*/val <= MaxFloat && val < 0.0f;
			//return val == std::numeric_limits<float>::lowest();
		}

		/**
		 * returns the maximum of two values
		 */
		template <class T>
		static T MaxOf(const T& v1, const T& v2)
		{
			return v1 > v2 ? v1 : v2;
		}

		/**
		 * returns the minimum of two values
		 */
		template <class T>
		static T MinOf(const T& v1, const T& v2)
		{
			return v1 < v2 ? v1 : v2;
		}

		/**
		 * clamps the first argument between the second two
		 */
		template <class T, class U, class V>
		static void Clamp(T& arg, const U& minVal, const V& maxVal)
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
		static T Sign(T a)
		{
			return a < static_cast<T>(0) ? static_cast<T>(-1) : static_cast<T>(1);
		}

		inline static unsigned int NearestPowerOfTwo(unsigned int value)
		{
			unsigned int temp = value;
			unsigned int powerOfTwo = 0;

			while (temp > 1)
			{
				temp >>= 1;
				++powerOfTwo;
			}

			const unsigned int result = 1 << powerOfTwo;

			return result == value ? result : result << 1;
		}
	};
}
