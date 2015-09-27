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

        //----------------------------------------------------------------
        // Copie interdite
        //----------------------------------------------------------------
        CSingleton(const CSingleton&);
        CSingleton& operator =(const CSingleton&);
    };

    ////////////////////////////////////////////////////////////
    /// Macro automatisant la création d'un singleton --
    /// à placer dans la définition de la classe concernée.
    /// La raison pour laquelle il faut redéfinir (et masquer)
    /// la fonction Instance() reste obscure, mais si ce n'est pas
    /// fait le client obtient des erreurs de link sur Inst
    ////////////////////////////////////////////////////////////
    #define MAKE_SINGLETON(Class) \
        public : \
            friend class CasaEngine::CSingleton<Class>; \
            static Class& Instance(); \
        private :

    ////////////////////////////////////////////////////////////
    /// Macro automatisant
    ////////////////////////////////////////////////////////////
    #define SINGLETON_IMPL(Class) \
        template <> Class* CasaEngine::CSingleton<Class>::Inst = nullptr; \
        Class& Class::Instance() \
        { \
            return CasaEngine::CSingleton<Class>::Instance(); \
        } \

} // namespace CasaEngine


#endif // SINGLETON_H
