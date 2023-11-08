
#ifndef _CEGUIIMAGECODEC_H_
#define _CEGUIIMAGECODEC_H_

#include "CA_Export.h"
#include "CEGUI\ImageCodec.h"
#include "CEGUI\Texture.h"
#include "CEGUI\DataContainer.h"

namespace CasaEngine
{
	///
	class CA_EXPORT CEGUIImageCodec : 
		public CEGUI::ImageCodec
	{
	public:
		/**
		 * 
		 */
		CEGUIImageCodec();
		
		/**
		 * 
		 */
		~CEGUIImageCodec();

		/**
		 *
		 */
		CEGUI::Texture* load(const CEGUI::RawDataContainer& data, CEGUI::Texture* result);
	};

}  // namespace CasaEngine

#endif //_CEGUIIMAGECODEC_H_
