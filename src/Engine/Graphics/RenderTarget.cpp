
#include "Base.h"

#include "RenderTarget.h"
#include "Maths\Matrix4.h"
#include "Maths\Vector3.h"
#include "EngineInfo.h"
#include "Viewport.h"
#include "Log/LogManager.h"



namespace CasaEngine
{
	/**
	 * 
	 */
	RenderTarget::RenderTarget()
	{
		
	}

	/**
	 * 
	 */
	const RenderTarget& RenderTarget::operator=( const RenderTarget& rsh_)
	{
		SetArea(rsh_.m_Area);
		return *this;
	}

	/**
	 * 
	 */
	RenderTarget::~RenderTarget()
	{
	}

	/**
	 * 
	 */
	CRectangle RenderTarget::GetArea() const
	{
		return m_Area;
	}

	/**
	 * 
	 */
	void RenderTarget::SetArea(const CRectangle& val)
	{
		m_Area = val;
		CA_TRACE("RenderTarget(%p) area = %d %d %d %d\n", this, m_Area.Origin.x, m_Area.Origin.y, m_Area.End.x, m_Area.End.y);
	}

} // namespace CasaEngine
