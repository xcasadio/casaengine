
#include "Base.h"

#include "FileAsset.h"
#include "Log\LogManager.h"
#include "Exceptions.h"
#include "Macro.h"
#include "CA_Assert.h"

namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur à partir d'un std::string
///
/// \param Name : Chemin complet du fichier
///
////////////////////////////////////////////////////////////
FileAsset::FileAsset(AAssetManager *pMgr_) :
	m_pAAsset(NULL)
{
	m_pAAssetManager = pMgr_;
}

/**
 * 
 */
FileAsset::FileAsset(const FileAsset& rsh)
{
	*this = rsh;
}

/**
 * 
 */
const FileAsset& FileAsset::operator = (const FileAsset& rsh)
{
	m_Name = rsh.m_Name;
	m_pAAssetManager = rsh.m_pAAssetManager;
	m_pAAsset = rsh.m_pAAsset;
	//Open(m_Name.c_str());

	return *this;
}

//8 != AAsset_read(assetF, header, 8)


/**
 * 
 */
FileAsset::~FileAsset()
{
	Close();
}


/**
 * AASSET_MODE_UNKNOWN      = 0,
 * AASSET_MODE_RANDOM       = 1,
 * AASSET_MODE_STREAMING    = 2,
 * AASSET_MODE_BUFFER       = 3
 */
bool FileAsset::Open(const char* fileName_, unsigned int mode_)
{
	m_Name = fileName_;
	m_pAAsset = AAssetManager_open(m_pAAssetManager, fileName_, AASSET_MODE_UNKNOWN);
	return m_pAAsset != NULL;
}

/**
 *
 */
bool FileAsset::Create(const char* fileName_, bool append_)
{
	Logging.Log(Error, "FileAsset(%s) : Can't write into an AAsset.\n", fileName_);
	return false;
}

/**
 * 
 */
void FileAsset::Close()
{
	if (m_pAAsset != NULL)
	{
		AAsset_close(m_pAAsset);
		m_pAAsset = NULL;
		DestroyBuffer();
	}
}

/**
 * 
 */
void FileAsset::FillBuffer()
{
	CA_ASSERT(m_pAAsset != NULL, "FileAsset::FillBuffer() : AAsset is NULL");
	
	m_BufferSize = AAsset_getLength(m_pAAsset);
	m_pBuffer = new char[m_BufferSize + 1];
	AAsset_read(m_pAAsset, m_pBuffer, m_BufferSize);
	m_pBuffer[m_BufferSize] = '\0';
}

/**
 * 
 */
bool FileAsset::Exists() const
{
    return m_pAAsset != NULL;
}

/**
 * 
 */
int FileAsset::Read(char *dst_, unsigned int size_)
{
	CA_ASSERT(m_pAAsset != NULL, "Try to read a file which is not opened");
	return AAsset_read(m_pAAsset, dst_, size_);
}

/**
 * 
 */
int FileAsset::Write(char *data_, unsigned int size_)
{
	Logging.Log(Error, "FileAsset(%s) : Can't write into an AAsset.\n", m_Name.c_str());
	return -1;
}

/**
 * 
 */
unsigned int FileAsset::Seek(unsigned int off_, SeekDir::TSeekDir dir_)
{
	CA_ASSERT(m_pAAsset != NULL, "Try to read a file which is not opened");
	return AAsset_seek(m_pAAsset, off_, dir_);
}

} // namespace CasaEngine
