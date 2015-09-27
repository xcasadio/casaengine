
#ifndef _CEGUITEXTURETARGET_H_
#define _CEGUITEXTURETARGET_H_

#include "CA_Export.h"
#include "Maths/Vector3.h"
#include "Maths/Matrix4.h"
#include "CEGUIRenderTarget.h"
#include "Graphics/TextureTarget.h"

#include "CEGUI/ForwardRefs.h"
#include "CEGUI/TextureTarget.h"
#include "CEGUI/Size.h"
#include "CEGUI/Texture.h"
#include "CEGUITexture.h"


namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT CEGUITextureTarget : 
		public CEGUIRenderTarget<CEGUI::TextureTarget>
	{
	public:

		/**
		 * 
		 */
		CEGUITextureTarget(CasaEngine::TextureTarget *pRenderTarget_);

		/**
		 * 
		 */
		void clear();

		/**
		 * 
		 */
		CEGUI::Texture& getTexture() const;

		/**
		 * 
		 */
		void declareRenderSize(const CEGUI::Sizef& sz);

		/**
		 * 
		 */
		bool isRenderingInverted() const;

	private:

		static unsigned int s_textureNumber;

		CEGUITexture *m_pTexture;
		//CEGUI::Sizef m_Size;
	};

}  // namespace CasaEngine

#endif //_CEGUITEXTURETARGET_H_
