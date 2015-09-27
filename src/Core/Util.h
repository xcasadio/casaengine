#ifndef UTIL_H
#define UTIL_H


namespace CasaEngine
{
	//////////////////////////////////////////////////////////////////////////
	// Provide special cast function which mirrors C++ style casts to support aliasing correct type punning casts in gcc with strict-aliasing enabled
	template<typename DestinationType, typename SourceType>
	inline DestinationType alias_cast( SourceType pPtr )
	{
		//STATIC_CHECK(sizeof(DestinationType) == sizeof(SourceType), ALIAS_CAST_BOTH_TYPES_NEED_TO_BE_OF_THE_SAME_SIZE );
#if defined(__SPU__)
		return reinterpret_cast<DestinationType>(pPtr);
#else
		union { 
			SourceType pSrc;
			DestinationType pDst;
		} conv_union;
		conv_union.pSrc = pPtr;
		return conv_union.pDst;
#endif
	}

#if defined(__SPU__)
	template<>
	inline uint32 alias_cast<uint32, float>( float pPtr )
	{
		return *reinterpret_cast<uint32*>(&pPtr);
	}
#endif

    ////////////////////////////////////////////////////////////
    /// Renvoie une valeur approchée d'un nombre à la plus proche
    /// plus grande puissance de 2
    ///
    /// \param Value : Nombre à tester
    ///
    /// \return Puissance de 2 correspondante
    ///
    ////////////////////////////////////////////////////////////
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

} // namespace CasaEngine


#endif // UTIL_H
