
#include "Base.h"

#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Graphics/Effects/IEffectPass.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Vertices/VertexType.h"

#include "CEGUIGeometryBuffer.h"

#include "Maths\Matrix4.h"
#include "Maths\Vector3.h"
#include "Maths/Vector2.h"
#include "Maths/Plane.h"

#include "CEGUI/Base.h"
#include "CEGUI/Vertex.h"




namespace CasaEngine
{
	/**
	 * 
	 */
	CEGUIGeometryBuffer::CEGUIGeometryBuffer() :
		m_IsMatrixValid(false),
		m_IsClippingActive(true),
		m_pEffect(nullptr),
		m_pTexture(nullptr),
		m_BufferSize(0),
		m_Pivot(0.0f, 0.0f, 0.0f),
		m_pDeclaration(nullptr),
		m_pVertexBuffer(nullptr)
	{
		//CA_TRACE("CEGUIGeometryBuffer(%p) created\n");
		InitializeBuffers();
	}


	/**
	 * 
	 */
	CEGUIGeometryBuffer::~CEGUIGeometryBuffer()
	{
		DELETE_AO m_pDeclaration;

		if (m_pVertexBuffer != nullptr)
		{
			DELETE_AO m_pVertexBuffer;
		}
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::draw() const
	{
		if (m_pVertexBuffer == nullptr) //TODO : why m_pVertexBuffer may be nullptr ?
		{
			return;
		}

		UpdateMatrix();

		CRectangle savedScissor;
		IRenderer::Get().GetScissorRect(&savedScissor);

		CRectangle scissor;
		scissor.Origin.x = static_cast<int>(m_ClipRect.d_min.d_x);
		scissor.Origin.y = static_cast<int>(m_ClipRect.d_min.d_y);
		scissor.End.x = static_cast<int>(m_ClipRect.d_max.d_x);
		scissor.End.y = static_cast<int>(m_ClipRect.d_max.d_y);

		Game::Instance()->GetCEGUIRenderer()->SetBlendMode(d_blendMode);

		size_t pos = 0;
		const int pass_count = m_pEffect ? m_pEffect->getPassCount() : 1;

		IRenderer::Get().SetDeclaration(m_pDeclaration);
		IRenderer::Get().SetVertexBuffer(0, *m_pVertexBuffer);

		std::vector<IEffectPass *>::iterator it = Game::Instance()->GetCEGUIRenderer()->Effect()->PassesBeginIterator();
		IShaderBase* pShader = (*it)->GetShader();
		pShader->SetParameter("ModelViewProj", m_Matrix * Game::Instance()->GetCEGUIRenderer()->GetViewProjMatrix());

		for (int pass = 0; pass < pass_count; ++pass)
		{
			// set up RenderEffect
			if (m_pEffect)
			{
				m_pEffect->performPreRenderFunctions(pass);
			}

			// draw the batches
			for (BatchList::const_iterator i = m_Batches.begin(); 
				i != m_Batches.end(); 
				++i)
			{
				if (i->clip)
				{
					//IRenderer::Get().SetScissorRect(&scissor); // why is wrong ?
				}

				IRenderer::Get().SetTexture(0, i->pTexture);
				pShader->SetParameter("Texture0", i->pTexture);
				IRenderer::Get().DrawPrimitives(PrimitiveType::TriangleList, pos, i->vertexCount / 3);
				pos += i->vertexCount;

				if (i->clip)
				{
					//IRenderer::Get().SetScissorRect(&savedScissor); // why is wrong ?
				}
			}
		}

		// clean up RenderEffect
		if (m_pEffect)
		{
			m_pEffect->performPostRenderFunctions();
		}
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::setTranslation(const CEGUI::Vector3f& v)
	{
		m_Translation = v;
		m_IsMatrixValid = false;
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::setRotation(const CEGUI::Quaternion& r)
	{
		m_Rotation = r;
		m_IsMatrixValid = false;
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::setPivot(const CEGUI::Vector3f& p)
	{
		m_Pivot = CEGUI::Vector3f(p.d_x, p.d_y, p.d_z);
		m_IsMatrixValid = false;
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::setClippingRegion(const CEGUI::Rectf& region)
	{
		m_ClipRect.top(ceguimax(0.0f, region.top()));
		m_ClipRect.left(ceguimax(0.0f, region.left()));
		m_ClipRect.bottom(ceguimax(0.0f, region.bottom()));
		m_ClipRect.right(ceguimax(0.0f, region.right()));
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::appendVertex(const CEGUI::Vertex& vertex)
	{
		appendGeometry(&vertex, 1);
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::appendGeometry(const CEGUI::Vertex* const vbuff, CEGUI::uint vertex_count)
	{
		PerformBatchManagement();

		// update size of current batch
		m_Batches.back().vertexCount += vertex_count;

		// buffer these vertices
		VertexPositionColorTexture vd;
		const CEGUI::Vertex* vs = vbuff;
		for (unsigned int i = 0; i < vertex_count; ++i, ++vs)
		{
			CColor color;
			color.SetFloats(vs->colour_val.getRed(), vs->colour_val.getGreen(), vs->colour_val.getBlue(), vs->colour_val.getAlpha());
			vd.Color = IRenderer::Get().ConvertColor(color);
			vd.TexCoords.x = vs->tex_coords.d_x;
			vd.TexCoords.y = vs->tex_coords.d_y;
			vd.Position.x = vs->position.d_x;
			vd.Position.y = vs->position.d_y;
			vd.Position.z = vs->position.d_z;
			m_Vertices.push_back(vd);

			if (vs->tex_coords.d_x == 0.0f && vs->tex_coords.d_y == 0.0f)
			{
				int x = 0;
				x = 1;
			}
		}

		UpdateBuffers();
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::UpdateMatrix() const
	{
		if (m_IsMatrixValid == true)
		{
			return;
		}

		const Vector3F p(m_Pivot.d_x, m_Pivot.d_y, m_Pivot.d_z);
		const Vector3F t(m_Translation.d_x, m_Translation.d_y, m_Translation.d_z);

		Quaternion r;
		r.x = m_Rotation.d_x;
		r.y = m_Rotation.d_y;
		r.z = m_Rotation.d_z;
		r.w = m_Rotation.d_w;

		m_Matrix.Transformation(0, 0, 0, &p, &r, &t);
		m_IsMatrixValid = true;
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::PerformBatchManagement()
	{
		const ITextureBase* pTex = m_pTexture ?
			(m_pTexture->GetTexture() == nullptr ? nullptr : m_pTexture->GetTexture()->GetTexture()) : nullptr;

		// create a new batch if there are no batches yet, or if the active texture
		// differs from that used by the current batch.
		if (m_Batches.empty() ||
			pTex != m_Batches.back().pTexture ||
			m_IsClippingActive != m_Batches.back().clip)
		{
			const BatchInfo batch = { const_cast<ITextureBase*>(pTex), 0, m_IsClippingActive};
			m_Batches.push_back(batch);
		}
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::InitializeBuffers()
	{
		m_pDeclaration = IRenderer::Get().CreateDeclaration(VertexPositionColorTexture::Elements, VertexPositionColorTexture::NbElements);
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::UpdateBuffers()
	{
		bool needNewBuffer = false;
		unsigned int vertexCount = m_Vertices.size();

		if(m_BufferSize < vertexCount)
		{
			needNewBuffer = true;
			m_BufferSize = vertexCount;
		}

		VertexPositionColorTexture* pData;
		if(m_Vertices.empty())
		{
			pData = nullptr;
		}
		else
		{
			pData = &m_Vertices[0];
		}

		if(needNewBuffer)
		{
			if (m_pVertexBuffer != nullptr)
			{
				//CA_TRACE("CEGUIGeometryBuffer(%p) release vertex buffer %p\n", this, m_pVertexBuffer);
				DELETE_AO m_pVertexBuffer;
				m_pVertexBuffer = nullptr;
			}

			m_pVertexBuffer = IRenderer::Get().CreateVertexBuffer(m_BufferSize, BUF_STATIC, pData);

// 			if (m_pVertexBuffer == nullptr)
// 			{
// 				CA_ERROR("CEGUIGeometryBuffer(%p) IRenderer::CreateVertexBuffer() failed\n", this);
// 			}
// 			CA_TRACE("CEGUIGeometryBuffer(%p) create vertex buffer %p\n", this, m_pVertexBuffer);
		}
		else
		{
			m_pVertexBuffer->Fill(pData, m_BufferSize, BUF_STATIC);
			//CA_TRACE("CEGUIGeometryBuffer fill vertex buffer %p\n");
		}
	}

	/**
	 * 
	 */
	Matrix4 CEGUIGeometryBuffer::GetMatrix() const
	{
		UpdateMatrix();
		return m_Matrix;
	}

	/**
	 * 
	 */
	void CEGUIGeometryBuffer::setActiveTexture( CEGUI::Texture* texture )
	{
		m_pTexture = static_cast<CEGUITexture*>(texture);
	}

	void CEGUIGeometryBuffer::reset()
	{
		m_Batches.clear();
		m_Vertices.clear();
		m_pTexture = 0;
	}

	CEGUI::Texture* CEGUIGeometryBuffer::getActiveTexture() const
	{
		return m_pTexture;
	}

	CEGUI::uint CEGUIGeometryBuffer::getVertexCount() const
	{
		return m_Vertices.size();
	}

	CEGUI::uint CEGUIGeometryBuffer::getBatchCount() const
	{
		return m_Batches.size();
	}

	void CEGUIGeometryBuffer::setRenderEffect( CEGUI::RenderEffect* effect )
	{
		m_pEffect = effect;
	}

	CEGUI::RenderEffect* CEGUIGeometryBuffer::getRenderEffect()
	{
		return m_pEffect;
	}

	void CEGUIGeometryBuffer::setClippingActive( const bool active )
	{
		m_IsClippingActive = active;
	}

	bool CEGUIGeometryBuffer::isClippingActive() const
	{
		return m_IsClippingActive;
	}

} // namespace CasaEngine
