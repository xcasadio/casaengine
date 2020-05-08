
#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

#include "CA_Export.h"
#include "Maths/Vector3.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector2.h"
#include "Renderer/Enums.h"
#include "Textures/Texture.h"
#include "Maths/Rectangle.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	///
	class CA_EXPORT RenderTarget :
		public AllocatedObject<RenderTarget>
	{
	public:
		RenderTarget();
		const RenderTarget& operator = (const RenderTarget& rsh_);
		virtual ~RenderTarget();

		/**
		 * 
		 */
		CRectangleI GetArea() const;

		/**
		 * 
		 */
		void SetArea(const CRectangleI& val);

		/**
		 * 
		 */
		virtual void Release() = 0;

		/**
		 * 
		 */
		virtual void Activate() = 0;

		/**
		 * 
		 */
		virtual void Deactivate() = 0;

		/**
		 * 
		 */
		virtual bool IsImageryCache() const = 0;

		/**
		 * 
		 */
		virtual bool IsRenderingInverted() const = 0;

	protected:
		///< Size of the RenderTarget
		CRectangleI m_Area;
	};

} 

#endif //_RENDERTARGET_H_
