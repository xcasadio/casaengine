#pragma once

#include "CA_Export.hpp"
#include  "Maths/Rectangle.hpp"

namespace CasaEngine
{
	class CA_EXPORT RenderTarget
	{
	public:
		RenderTarget();
		RenderTarget& operator = (const RenderTarget& rsh_);
		virtual ~RenderTarget();

		Rectangle GetArea() const;
		void SetArea(const Rectangle& val);

		virtual void Release() = 0;
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		virtual bool IsImageryCache() const = 0;
		virtual bool IsRenderingInverted() const = 0;

	protected:
		Rectangle _area;
	};
}
