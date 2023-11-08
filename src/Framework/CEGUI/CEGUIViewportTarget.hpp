
#ifndef _CEGUIVIEWPORTTARGET_H_
#define _CEGUIVIEWPORTTARGET_H_

#include "CA_Export.h"

#include "CEGUIRenderTarget.h"
#include "Maths/Vector3.h"
#include "Maths/Matrix4.h"

#include "Graphics/RenderTarget.h"
#include "Graphics/ViewportTarget.h"


namespace CasaEngine
{
	///
	class CA_EXPORT CEGUIViewportTarget : 
		public CEGUIRenderTarget<>
	{
	public:
		/**
		 * 
		 */
		CEGUIViewportTarget(ViewportTarget *pViewportTarget_);

		/**
		 * 
		 */
		//const CEGUIViewportTarget& operator = (const CEGUIViewportTarget& rsh_);
		
		/**
		 * 
		 */
		~CEGUIViewportTarget();

	};

}  // namespace CasaEngine

#endif //_CEGUIVIEWPORTTARGET_H_
