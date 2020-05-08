#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstdlib>
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Template servant à construire les classes singleton
    ////////////////////////////////////////////////////////////
    template <class T>
    class CSingleton :
		public AllocatedObject<CSingleton<T> >
    {
    public :
        static T& Instance()
        {
            if (!Inst)
                Inst = NEW_AO T;

            return *Inst;
        }

        static void Destroy()
        {
			if (Inst != nullptr)
			{
				DELETE_AO Inst;
				Inst = nullptr;
			}
        }

    protected :
        CSingleton() {}
        ~CSingleton() {}

    private :
        static T* Inst; ///< Instance unique de la classe

        CSingleton(const CSingleton&);
        CSingleton& operator =(const CSingleton&);
    };

    #define MAKE_SINGLETON(Class) \
        public : \
            friend class CasaEngine::CSingleton<Class>; \
            static Class& Instance(); \
        private :

    #define SINGLETON_IMPL(Class) \
        template <> Class* CasaEngine::CSingleton<Class>::Inst = nullptr; \
        Class& Class::Instance() \
        { \
            return CasaEngine::CSingleton<Class>::Instance(); \
        } \

}


#endif // SINGLETON_H
