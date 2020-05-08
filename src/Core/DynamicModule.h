#ifndef PLUGIN_H
#define PLUGIN_H

#include "CA_Export.h"
#include "Memory\MemoryAllocation.h"
#include <string>

namespace CasaEngine
{

/*!
\brief
    Class that wraps and gives access to a dynamically linked module
    (.dll, .so, etc...)
*/
class CA_EXPORT DynamicModule :
	public AllocatedObject<DynamicModule>
{
public:
    /*!
    \brief
        Construct the DynamicModule object by loading the dynamic loadable
        module specified.

    \param name
        String object holding the name of a loadable module.
    */
    DynamicModule(const std::string& name);

    /*!
    \brief
        Destroys the DynamicModule object and unloads the associated loadable
        module.
    */
    ~DynamicModule();

    /*!
    \brief
        Return a String containing the name of the dynamic module.
    */
    const std::string& getModuleName() const;

    /*!
    \brief
        Return the address of the specified symbol.

    \param symbol
        String holding the symbol to look up in the module.

    \return
        Pointer to the requested symbol.

    \exception
        InvalidRequestException thrown if the symbol does not exist.
    */
    void* getSymbolAddress(const std::string& symbol) const;

private:
    struct Impl;
    Impl* d_pimpl;
};

}


#endif // PLUGIN_H
