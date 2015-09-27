#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "StringUtils.h"
#include "Exceptions.h"
#include <string>
#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	/**
	 *  
	 */
	class IFunction :
		public AllocatedObject<IFunction>
	{
	public :

		/**
		 *  
		 */
		virtual ~IFunction() {}

		/**
		 *  
		 */
		virtual std::string Execute(const std::string& Params) = 0;
	};

	/**
	 *  
	 */
	class Functor
	{
	public :
		/**
		 *  
		 */
		Functor(IFunction* Func = nullptr);
		
		/**
		 *  
		 */
		std::string operator ()(const std::string& Params = "") const;

	private :
		IFunction *m_pFunction;
	};

	#include "Functor.inl"

} // namespace CasaEngine

#endif // FUNCTOR_H
