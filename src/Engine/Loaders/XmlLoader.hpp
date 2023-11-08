#ifndef _XMLLOADER_H
#define _XMLLOADER_H

#include "CA_Export.h"
#include "Loaders/Loader.h"
#include "Parsers/Xml/tinyxml2.h"
#include "IO/IFile.h"

namespace CasaEngine
{
    /**
     * 
     */
    class CA_EXPORT XmlLoader : 
		public ILoader<tinyxml2::XMLDocument>
    {
    public :
        XmlLoader();
        ~XmlLoader();
    	
        tinyxml2::XMLDocument* LoadFromFile(IFile *pFile_);
        virtual void SaveToFile(const tinyxml2::XMLDocument* Object, const std::string& Filename);
    };

}


#endif // _XMLLOADER_H
