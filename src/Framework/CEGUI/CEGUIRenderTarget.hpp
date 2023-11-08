
#ifndef _CEGUIRENDERTARGET_H_
#define _CEGUIRENDERTARGET_H_

#include "CA_Export.h"
#include "Memory\MemoryAllocation.h"

#include "CEGUI/ForwardRefs.h"
#include "CEGUI/GeometryBuffer.h"
#include "CEGUI/Rect.h"
#include "CEGUI/RenderQueue.h"
#include "CEGUI/RenderTarget.h"

#include "Entities\Components\CameraComponent.h"
#include "Graphics/RenderTarget.h"
#include "Graphics\Viewport.h"
#include "Maths\Matrix4.h"


namespace CasaEngine
{
	/**
	 * Intermediate implementation of a RenderTarget.
	 */
	template <typename T = CEGUI::RenderTarget>
	class CA_EXPORT CEGUIRenderTarget : 
		public T,
		public AllocatedObject<CEGUIRenderTarget<T> >
		
	{
	public:
		/**
		 * 
		 */
		CEGUIRenderTarget(CasaEngine::RenderTarget *pRenderTarget_);

		/**
		 * 
		 */
		//const CEGUIRenderTarget& operator = (const CEGUIRenderTarget& rsh_);
		
		/**
		 * 
		 */
		virtual ~CEGUIRenderTarget();
		
		/**
		 * 
		 */
		void draw(const CEGUI::GeometryBuffer& buffer);
		/**
		 * 
		 */
		void draw(const CEGUI::RenderQueue& queue);

		/**
		 * 
		 */
		void setArea(const CEGUI::Rectf& area);

		/**
		 * 
		 */
		const CEGUI::Rectf& getArea() const;

		/**
		 * 
		 */
		bool isImageryCache() const;

		/**
		 * 
		 */
		void activate();

		/**
		 * 
		 */
		void deactivate();

		/**
		 * 
		 */
		void unprojectPoint(const CEGUI::GeometryBuffer& buff, const CEGUI::Vector2f& p_in, CEGUI::Vector2f& p_out) const;

	protected:

		void UpdateMatrix() const;

		CasaEngine::RenderTarget *m_pRenderTarget; ///< 
		CEGUI::Rectf m_Area; ///< 
		mutable bool m_IsMatrixValid;
		mutable Matrix4 m_ViewMatrix, m_ProjMatrix, m_ViewProjMatrix;
		mutable float m_ViewDistance;
	};

}  // namespace CasaEngine

#endif //_CEGUIRENDERTARGET_H_
