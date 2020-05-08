
#include "Base.h"

#include "ViewportTarget.h"
#include "Maths\Matrix4.h"
#include "Maths\Vector3.h"

#include "Viewport.h"
#include "Renderer/Renderer.h"
#include "Log/LogManager.h"



namespace CasaEngine
{
	/**
	 * 
	 */
	ViewportTarget::ViewportTarget()
	{
		CA_TRACE("ViewportTarget(%p) created\n", this);
	}

	/**
	 * 
	 */
	const ViewportTarget& ViewportTarget::operator = (const ViewportTarget& rsh_)
	{
		SetArea(rsh_.m_Area);
		return *this;
	}
	
	/**
	 * 
	 */
	void ViewportTarget::Release()
	{

	}

	/**
	 *
	 */
	void ViewportTarget::Create(const CRectangleI &rect)
	{
		SetArea(rect);
	}

	/**
	 * 
	 */
	void ViewportTarget::Activate()
	{
		//TODO : use view id
		bgfx::setViewRect(254, 
			static_cast<float>(m_Area.x),
			static_cast<float>(m_Area.y),
			static_cast<float>(m_Area.w),
			static_cast<float>(m_Area.h));
	}

	/**
	 * 
	 */
	void ViewportTarget::Deactivate()
	{

	}

	/**
	 * 
	 */
	bool ViewportTarget::IsImageryCache() const
	{
		return false;
	}

	/**
	 * 
	 */
	bool ViewportTarget::IsRenderingInverted() const
	{
		return false;
	}

}
