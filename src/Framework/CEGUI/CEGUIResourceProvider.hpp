
#ifndef _CEGUIRESOURCEPROVIDER_H_
#define _CEGUIRESOURCEPROVIDER_H_

#include "CA_Export.h"

#include "IO/IFile.h"

#include "CEGUI/ResourceProvider.h"
#include "CEGUI/String.h"

#include <map>


namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT CEGUIResourceProvider : 
		public CEGUI::ResourceProvider
	{
	public:
		/**
		 * 
		 */
		void loadRawDataContainer( const CEGUI::String& filename, CEGUI::RawDataContainer& output, const CEGUI::String& resourceGroup );

		/**
		 * 
		 */
		void unloadRawDataContainer( CEGUI::RawDataContainer& );

		/**
		 * 
		 */
		size_t getResourceGroupFileNames( std::vector<CEGUI::String>& out_vec, const CEGUI::String& file_pattern, const CEGUI::String& resource_group );

	private:

		std::map<char *, IFile *> m_OpenedFiles;

	};

}  // namespace CasaEngine

#endif //_CEGUIRESOURCEPROVIDER_H_
