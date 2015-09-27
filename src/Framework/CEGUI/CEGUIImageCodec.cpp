
#include "Base.h"

#include "CEGUIImageCodec.h"
#include "Log\LogManager.h"
#include "Memory\MemoryAllocation.h"


namespace CasaEngine
{
	/**
	 * 
	 */
	CEGUIImageCodec::CEGUIImageCodec()
		: ImageCodec("CasaEngine ImageCodec - FreeImage based image codec")
	{
	}

	/**
	 * 
	 */
	CEGUIImageCodec::~CEGUIImageCodec()
	{
	}
	
	/**
	 *
	 */
	CEGUI::Texture* CEGUIImageCodec::load(const CEGUI::RawDataContainer& data, CEGUI::Texture* result)
	{
// 		CImage *img = CImagesLoader::LoadFromMemory(const_cast<unsigned char *>(data.getDataPtr()), data.getSize());
// 		result->loadFromMemory(img->GetData(), 
// 			CEGUI::Sizef(static_cast<float>(img->GetSize().x), static_cast<float>(img->GetSize().y)), 
// 			CEGUI::Texture::PF_RGBA);
// 		DELETE_AO img;
// 		return result;
		throw new std::exception("CEGUIImageCodec::load() not yet implemented with bgfx");

		return nullptr;
	}

} // namespace CasaEngine
