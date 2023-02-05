#include "Base.h"

#include "RenderTarget.h"
#include "Maths/Matrix4.h"

#include "Log/LogManager.h"

namespace CasaEngine
{
	RenderTarget::RenderTarget()
		= default;

	RenderTarget& RenderTarget::operator=(const RenderTarget& rsh_)
	{
		SetArea(rsh_._area);
		return *this;
	}

	RenderTarget::~RenderTarget()
		= default;

	Rectangle RenderTarget::GetArea() const
	{
		return _area;
	}

	void RenderTarget::SetArea(const Rectangle& val)
	{
		_area = val;
		CA_TRACE("RenderTarget(%p) area = %d %d %d %d\n", this, _area.x, _area.y, _area.Right(), _area.Bottom());
	}
}