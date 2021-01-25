#ifndef _VIEWPORTTARGET_H_
#define _VIEWPORTTARGET_H_

#include "CA_Export.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Renderer/Enums.h"
#include "RenderTarget.h"
#include "Maths/Rectangle.h"

namespace CasaEngine
{
	class CA_EXPORT ViewportTarget :
		public RenderTarget
	{
	public:
		ViewportTarget();
		const ViewportTarget& operator = (const ViewportTarget& rsh_);

		void Release();
		void Create(const RectangleF& rect);
		void Activate();
		void Deactivate();
		bool IsImageryCache() const;
		bool IsRenderingInverted() const;
	};
}

#endif
