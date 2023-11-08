
#ifndef _CEGUIGEOMETRYBUFFER_H_
#define _CEGUIGEOMETRYBUFFER_H_

#include "CA_Export.h"
#include "Maths/Vector3.h"
#include "Maths/Matrix4.h"
#include "Maths/Quaternion.h"
#include "Graphics/Vertices/VertexType.h"
#include "CEGUITexture.h"

#include "Graphics/Textures/TextureBase.h"

#include "CEGUI/GeometryBuffer.h"
#include "CEGUI/Quaternion.h"
#include "CEGUI/Vector.h"
#include "CEGUI/Rect.h"
#include "CEGUI/Base.h"
#include "CEGUI/RenderEffect.h"

#include <vector>
#include "Graphics/Vertices/Declaration.h"
#include "Graphics/Vertices/Buffer.h"


namespace CasaEngine
{
	///
	class CA_EXPORT CEGUIGeometryBuffer : 
		public CEGUI::GeometryBuffer
	{
	public:

		/**
		 * 
		 */
		CEGUIGeometryBuffer();

		/**
		 * 
		 */
		~CEGUIGeometryBuffer();

		void draw() const;

		void setTranslation( const CEGUI::Vector3f& v );

		void setRotation( const CEGUI::Quaternion& r );

		void setPivot( const CEGUI::Vector3f& p );

		void setClippingRegion( const CEGUI::Rectf& region );

		void appendVertex( const CEGUI::Vertex& vertex );

		void appendGeometry( const CEGUI::Vertex* const vbuff, CEGUI::uint vertex_count );

		void setActiveTexture( CEGUI::Texture* texture );

		void reset();

		CEGUI::Texture* getActiveTexture() const;

		CEGUI::uint getVertexCount() const;

		CEGUI::uint getBatchCount() const;

		void setRenderEffect( CEGUI::RenderEffect* effect );

		CEGUI::RenderEffect* getRenderEffect();

		void setClippingActive( const bool active );

		bool isClippingActive() const;

		/**
		 * 
		 */
		Matrix4 GetMatrix() const;

	private:

		/**
		 * 
		 */
		void PerformBatchManagement();

		/**
		 * 
		 */
		void InitializeBuffers();

		/**
		 * 
		 */
		void UpdateBuffers();

		/**
		 * 
		 */
		void UpdateMatrix() const;

		//! type to track info for per-texture sub batches of geometry
		struct BatchInfo
		{
			ITextureBase* pTexture;
			unsigned int vertexCount;
			bool clip;
		};

		//! type of container that tracks BatchInfos.
		typedef std::vector<BatchInfo> BatchList;
		//! list of texture batches added to the geometry buffer
		BatchList m_Batches;

		//! type of container used to queue the geometry
		typedef std::vector<VertexPositionColorTexture> VertexList;
		//! container where added geometry is stored.
		VertexList m_Vertices;

		IDeclaration *m_pDeclaration;
		Buffer<VertexPositionColorTexture> *m_pVertexBuffer;
		unsigned int m_BufferSize;

		CEGUI::Rectf m_ClipRect;
		bool m_IsClippingActive;
		CEGUI::Vector3f m_Translation, m_Pivot;
		CEGUI::Quaternion m_Rotation;
		mutable Matrix4 m_Matrix; //! the world matrix
		mutable bool m_IsMatrixValid; //! if the world matrix need to be computed
		CEGUI::RenderEffect *m_pEffect; //! active effect
		CEGUITexture *m_pTexture; //! active texture
	};

}  // namespace CasaEngine

#endif //_CEGUIGEOMETRYBUFFER_H_
