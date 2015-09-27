
#include "Base.h"

#include "CEGUIViewportTarget.h"
#include "Maths\Matrix4.h"
#include "Maths\Vector3.h"
#include "CEGUI/GeometryBuffer.h"
#include "CEGUI/RenderQueue.h"
#include "Maths/Vector2.h"
#include "Game/GameInfo.h"
#include "Maths/Plane.h"
#include "Graphics/ViewportTarget.h"




namespace CasaEngine
{
	/**
	 * 
	 */
	CEGUIViewportTarget::CEGUIViewportTarget(ViewportTarget *pViewportTarget_) :
		CEGUIRenderTarget<>(pViewportTarget_)
	{
		CA_ASSERT(pViewportTarget_ != nullptr, "CEGUIViewportTarget() : ViewportTarget is nullptr");
		//m_pRenderTarget = pViewportTarget_;

		m_Area.d_min.d_x = static_cast<float>(pViewportTarget_->GetArea().Origin.x);
		m_Area.d_min.d_y = static_cast<float>(pViewportTarget_->GetArea().Origin.y);
		m_Area.d_max.d_x = static_cast<float>(pViewportTarget_->GetArea().Width());
		m_Area.d_max.d_y = static_cast<float>(pViewportTarget_->GetArea().Height());
	}

	/**
	 * 
	 */
	/*const CEGUIViewportTarget& CEGUIViewportTarget::operator=( const CEGUIViewportTarget& rsh_ )
	{
		m_pRenderTarget = rsh_.m_pRenderTarget;
		return *this;
	}*/

	/**
	 * 
	 */
	CEGUIViewportTarget::~CEGUIViewportTarget()
	{
	}

} // namespace CasaEngine

#include "CEGUIRenderTarget.inl"
