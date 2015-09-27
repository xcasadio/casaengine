
#ifndef VALIDNUMBER_H_
#define VALIDNUMBER_H_

#include "Util.h"


namespace CasaEngine
{

//--------------------------------------------------------------------------------

// http://www.psc.edu/general/software/packages/ieee/ieee.html

/*
	The IEEE standard for floating point arithmetic
	""""""""""""""""""""""""""""""""""""""""""""""""

	Single Precision
	"""""""""""""""""

	The IEEE single precision floating point standard representation requires a 32 bit word, 
	which may be represented as numbered from 0 to 31, left to right. 
	The first bit is the sign bit, S, 
	the next eight bits are the exponent bits, 'E', 
	and the final 23 bits are the fraction 'F':

	S EEEEEEEE FFFFFFFFFFFFFFFFFFFFFFF
	0 1      8 9                    31

	The value V represented by the word may be determined as follows:

	* If E=255 and F is nonzero, then V=NaN ("Not a number")
	* If E=255 and F is zero and S is 1, then V=-Infinity
	* If E=255 and F is zero and S is 0, then V=Infinity
	* If 0<E<255 then V=(-1)**S * 2 ** (E-127) * (1.F) where "1.F" is intended to represent the binary number created by prefixing F with an implicit leading 1 and a binary point.
	* If E=0 and F is nonzero, then V=(-1)**S * 2 ** (-126) * (0.F) These are "unnormalized" values.
	* If E=0 and F is zero and S is 1, then V=-0
	* If E=0 and F is zero and S is 0, then V=0 



	Double Precision
	"""""""""""""""""

	The IEEE double precision floating point standard representation requires a 64 bit word, 
	which may be represented as numbered from 0 to 63, left to right. 
	The first bit is the sign bit, S, 
	the next eleven bits are the exponent bits, 'E', 
	and the final 52 bits are the fraction 'F':

	S EEEEEEEEEEE FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
	0 1        11 12                                                63

	The value V represented by the word may be determined as follows:

	* If E=2047 and F is nonzero, then V=NaN ("Not a number")
	* If E=2047 and F is zero and S is 1, then V=-Infinity
	* If E=2047 and F is zero and S is 0, then V=Infinity
	* If 0<E<2047 then V=(-1)**S * 2 ** (E-1023) * (1.F) where "1.F" is intended to represent the binary number created by prefixing F with an implicit leading 1 and a binary point.
	* If E=0 and F is nonzero, then V=(-1)**S * 2 ** (-1022) * (0.F) These are "unnormalized" values.
	* If E=0 and F is zero and S is 1, then V=-0
	* If E=0 and F is zero and S is 0, then V=0 

*/

//--------------------------------------------------------------------------------

#define FloatU32(x)						(alias_cast<unsigned int, float>(x))
#define FloatU32ExpMask				(0xFF << 23)
#define FloatU32FracMask			((1 << 23) - 1)
#define FloatU32SignMask			(1 << 31)
#define F32NAN								(0x7F800001)					// Produces rock solid fp-exceptions.
#define F32NAN_SAFE						(FloatU32ExpMask | FloatU32FracMask) // This one is not triggering an fp-exception.

#define DoubleU64(x)					(*( (unsigned long long*) &(x) ))
#define DoubleU64ExpMask			((unsigned long long)255 << 55)
#define DoubleU64FracMask			(((unsigned long long)1 << 55) - (unsigned long long)1)
#define DoubleU64SignMask			((unsigned long long)1 << 63)
#if defined(__GNUC__)
	#define F64NAN								(0x7FF0000000000001ULL)	// Produces rock solid fp-exceptions.
#else
	#define F64NAN								(0x7FF0000000000001)	// Produces rock solid fp-exceptions.
#endif
#define F64NAN_SAFE						(DoubleU64ExpMask | DoubleU64FracMask)  // This one is not triggering an fp-exception.

//--------------------------------------------------------------------------------

inline bool NumberValid(const float& x)
{
	//return ((FloatU32(x) & FloatU32ExpMask) != FloatU32ExpMask);

	unsigned int i = FloatU32(x);
	unsigned int expmask = FloatU32ExpMask;
	unsigned int iexp = i & expmask;
	bool invalid = (iexp == expmask);

	if (invalid)
	{
		union f32_u
		{
			unsigned int uintVal;
			float floatVal;
		};
		f32_u u;	u.uintVal = 0x7F800001;
		float fpe = u.floatVal;
		(void)fpe;
	}

	return !invalid;
}

inline bool NumberNAN(const float& x)
{
	return (((FloatU32(x) & FloatU32ExpMask) == FloatU32ExpMask) && 
					((FloatU32(x) & FloatU32FracMask) != 0));
}

inline bool NumberINF(const float& x)
{
	return (((FloatU32(x) & FloatU32ExpMask) == FloatU32ExpMask) && 
					((FloatU32(x) & FloatU32FracMask) == 0));
}

inline bool NumberDEN(const float& x)
{
	return (((FloatU32(x) & FloatU32ExpMask) == 0) && 
					((FloatU32(x) & FloatU32FracMask) != 0));
}

//--------------------------------------------------------------------------------

inline bool NumberValid(const double& x)
{
	return ((DoubleU64(x) & DoubleU64ExpMask) != DoubleU64ExpMask);
}

inline bool NumberNAN(const double& x)
{
	return (((DoubleU64(x) & DoubleU64ExpMask) == DoubleU64ExpMask) && 
					((DoubleU64(x) & DoubleU64FracMask) != 0));
}

inline bool NumberINF(const double& x)
{
	return (((DoubleU64(x) & DoubleU64ExpMask) == DoubleU64ExpMask) && 
					((DoubleU64(x) & DoubleU64FracMask) == 0));
}

inline bool NumberDEN(const double& x)
{
	return (((DoubleU64(x) & DoubleU64ExpMask) == 0) && 
					((DoubleU64(x) & DoubleU64FracMask) != 0));
}

//--------------------------------------------------------------------------------


inline bool NumberValid(const char /*x*/)
{	
	return true; //integers are always valid
}
inline bool NumberValid(const unsigned char /*x*/)
{	
	return true; //integers are always valid
}
inline bool NumberValid(const short /*x*/)
{	
	return true; //integers are always valid
}
inline bool NumberValid(const unsigned short /*x*/)
{	
	return true; //integers are always valid
}
inline bool NumberValid(const int /*x*/)
{	
	return true; //integers are always valid
}
inline bool NumberValid(const unsigned int /*x*/)
{	
	return true; //integers are always valid
}
inline bool NumberValid(const long long /*x*/)
{	
	return true; //integers are always valid
}
inline bool NumberValid(const unsigned long long /*x*/)
{	
	return true; //integers are always valid
}

} // namespace CasaEngine

#endif // VALIDNUMBER_H_
