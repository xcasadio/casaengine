#ifndef RESOURCE_H
#define RESOURCE_H

#include "CA_Export.h"
#include <string>
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
    class CA_EXPORT IResource :
		public AllocatedObject<IResource>
    {
    public :
        IResource();
        virtual ~IResource() = 0;

        const std::string& GetName() const;
        void AddRef();
        int Release();

    private :
        friend class ResourceManager;

        IResource(IResource&) = delete;
        void operator =(IResource&) = delete;
    	
        std::string m_Name;
        int         m_RefCount;
    };
}

#endif
