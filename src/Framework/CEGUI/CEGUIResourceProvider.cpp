
#include "Base.h"

#include "CEGUIResourceProvider.h"


#include "IO/IOManager.h"
#include "IO/IFile.h"

#include "CEGUI/Base.h"
#include "CEGUI/Exceptions.h"
#include "Resources/MediaManager.h"


namespace CasaEngine
{
	/**
	 * 
	 */
	void CEGUIResourceProvider::loadRawDataContainer( const CEGUI::String& filename, CEGUI::RawDataContainer& output, const CEGUI::String& resourceGroup )
	{
		// Recherche du fichier dans les répertoires enregistrés
		IFile *pFile = MediaManager::Instance().FindMedia(filename.c_str(), true);
		//IFile *pFile = IOManager::OpenFile(filename.c_str(), FileMode::READ);

		if (pFile == nullptr)
		{
			CEGUI_THROW(CEGUI::FileIOException(
				"A problem occurred while reading file: " + filename));
		}

		output.setData(reinterpret_cast<CEGUI::uint8 *>(pFile->GetBuffer()));
		output.setSize(pFile->GetBufferLength());

		m_OpenedFiles[pFile->GetBuffer()] = pFile;
	}

	/**
	 * 
	 */
	void CEGUIResourceProvider::unloadRawDataContainer( CEGUI::RawDataContainer& data)
	{
		std::map<char *, IFile *>::iterator it = m_OpenedFiles.find(reinterpret_cast<char *>(data.getDataPtr()));

		//avoid delete[] when ~RawDataContainer() is called
		data.setData(nullptr);
		data.setSize(0);

		if (it != m_OpenedFiles.end())
		{
			it->second->Close();
			DELETE_AO it->second;
			m_OpenedFiles.erase(it);
		}
		else // error : unknown file
		{

		}
	}

	/**
	 * 
	 */
	size_t CEGUIResourceProvider::getResourceGroupFileNames( std::vector<CEGUI::String>& out_vec, const CEGUI::String& file_pattern, const CEGUI::String& resource_group )
	{
		return 0;
	}

} // namespace CasaEngine
