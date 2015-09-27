#include "Base.h"

#include "Game/DrawableGameComponent.h"
#include "Game/Game.h"
#include "Graphics/Renderer/Renderer.h"
#include "Sprite/Sprite.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"


#include "Entities/Components/CameraComponent.h"
#include "Game/GameInfo.h"

#include <vector>

namespace CasaEngine
{
	/**
	 * 
	 */
	SpriteRenderer::SpriteRenderer(Game* pGame_) : 
		DrawableGameComponent(pGame_),
		m_MaxSprite(500),
		m_NbElt(0)
	{
		m_SpriteDatas.reserve(m_MaxSprite);
		//m_SpriteBatches.reserve(m_MaxSprite);

		m_pDatas = NEW_AO VertexPositionColorTexture[m_MaxSprite];

		DrawOrder(5000);
	}

	/**
		* 
		*/
	SpriteRenderer::~SpriteRenderer()
	{
		Clear();

		DELETE_AO[] m_pDatas;

		bgfx::destroyDynamicVertexBuffer(m_VertexBuffer);
		bgfx::destroyIndexBuffer(m_IndexBuffer);
		bgfx::destroyProgram(m_Program);
	}

	/**
	 * 
	 */
	void SpriteRenderer::Initialize()
	{
		IGameComponent::Initialize();

		m_VertexBuffer = bgfx::createDynamicVertexBuffer(m_MaxSprite * 4, VertexPositionColorTexture::ms_decl, BGFX_BUFFER_COMPUTE_WRITE);

		short *pIndices = ::new short[m_MaxSprite * 6];

		for (int i=0; i<m_MaxSprite; i++)
		{
			pIndices[i * 6 + 0] = static_cast<short>(0 + i * 4);
			pIndices[i * 6 + 1] = static_cast<short>(2 + i * 4);
			pIndices[i * 6 + 2] = static_cast<short>(1 + i * 4);
			pIndices[i * 6 + 3] = static_cast<short>(0 + i * 4);
			pIndices[i * 6 + 4] = static_cast<short>(3 + i * 4);
			pIndices[i * 6 + 5] = static_cast<short>(2 + i * 4);
		}

		m_IndexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(pIndices, sizeof(short) * m_MaxSprite * 6 ));
		delete[] pIndices;

		//m_pEffect = IRenderer::Get().CreateEffectFromFile("sprite_batch");
	}

	/**
	 * 
	 */
	void SpriteRenderer::Update(const GameTime& /*gametime_*/ )
	{
		m_SpriteBatches.clear();

		UpdateBuffer();
		Clear();

		m_NbElt = 0;
		m_SpriteDatas.clear();
		
	}

	/**
	 * 
	 */
	bool SortByDepth(SpriteRenderer::SpriteDisplayData i, SpriteRenderer::SpriteDisplayData j) 
	{ 
		return i.TopLeft.Position.z < j.TopLeft.Position.z; 
	}

	/**
	 * 
	 */
	void SpriteRenderer::UpdateBuffer()
	{
		m_SpriteBatches.clear();

		if (m_NbElt == 0)
		{
			return;
		}

		std::sort(m_SpriteDatas.begin(), m_SpriteDatas.end(), SortByDepth);

		int nbSprite = 0;
		const Texture *pTexture = m_SpriteDatas[0].Texture;

		for (unsigned int i=0; i<m_NbElt; i++)
		{
			if (pTexture != m_SpriteDatas[i].Texture)
			{
				SpriteBatch batch;
				batch.Texture = pTexture;
				batch.NbSprite = nbSprite;
				m_SpriteBatches.push_back(batch);
			}

			m_pDatas[i * 4 + 0].Position.x = m_SpriteDatas[i].TopLeft.Position.x;
			m_pDatas[i * 4 + 0].Position.y = m_SpriteDatas[i].TopLeft.Position.y;
			m_pDatas[i * 4 + 0].Position.z = m_SpriteDatas[i].TopLeft.Position.z;
			m_pDatas[i * 4 + 0].TexCoords.x = m_SpriteDatas[i].TopLeft.TexCoords.x;
			m_pDatas[i * 4 + 0].TexCoords.y = m_SpriteDatas[i].TopLeft.TexCoords.y;
			m_pDatas[i * 4 + 0].Color = m_SpriteDatas[i].TopLeft.Color;
			m_pDatas[i * 4 + 1].Position.x = m_SpriteDatas[i].TopRight.Position.x;
			m_pDatas[i * 4 + 1].Position.y = m_SpriteDatas[i].TopRight.Position.y;
			m_pDatas[i * 4 + 1].Position.z = m_SpriteDatas[i].TopRight.Position.z;
			m_pDatas[i * 4 + 1].TexCoords.x = m_SpriteDatas[i].TopRight.TexCoords.x;
			m_pDatas[i * 4 + 1].TexCoords.y = m_SpriteDatas[i].TopRight.TexCoords.y;
			m_pDatas[i * 4 + 1].Color = m_SpriteDatas[i].TopRight.Color;
			m_pDatas[i * 4 + 2].Position.x = m_SpriteDatas[i].BottomRight.Position.x;
			m_pDatas[i * 4 + 2].Position.y = m_SpriteDatas[i].BottomRight.Position.y;
			m_pDatas[i * 4 + 2].Position.z = m_SpriteDatas[i].BottomRight.Position.z;
			m_pDatas[i * 4 + 2].TexCoords.x = m_SpriteDatas[i].BottomRight.TexCoords.x;
			m_pDatas[i * 4 + 2].TexCoords.y = m_SpriteDatas[i].BottomRight.TexCoords.y;
			m_pDatas[i * 4 + 2].Color = m_SpriteDatas[i].BottomRight.Color;
			m_pDatas[i * 4 + 3].Position.x = m_SpriteDatas[i].BottomLeft.Position.x;
			m_pDatas[i * 4 + 3].Position.y = m_SpriteDatas[i].BottomLeft.Position.y;
			m_pDatas[i * 4 + 3].Position.z = m_SpriteDatas[i].BottomLeft.Position.z;
			m_pDatas[i * 4 + 3].TexCoords.x = m_SpriteDatas[i].BottomLeft.TexCoords.x;
			m_pDatas[i * 4 + 3].TexCoords.y = m_SpriteDatas[i].BottomLeft.TexCoords.y;
			m_pDatas[i * 4 + 3].Color = m_SpriteDatas[i].BottomLeft.Color;

			if (pTexture != m_SpriteDatas[i].Texture)
			{
				//reinit
				nbSprite = 1;
				pTexture = m_SpriteDatas[i].Texture;
			}
			else
			{
				nbSprite++;
			}
		}

		bgfx::updateDynamicVertexBuffer(m_VertexBuffer, 0, bgfx::copy(m_pDatas, (uint32_t)m_NbElt * 4 * sizeof(VertexPositionColorTexture) ) );

		//the last batch
		SpriteBatch batch;
		batch.Texture = pTexture;
		batch.NbSprite = nbSprite;
		m_SpriteBatches.push_back(batch);
	}

	/**
	 * 
	 */
	void SpriteRenderer::Draw()
	{
		if (m_NbElt == 0)
		{
			return;
		}

		int indexPos = 0;
		CameraComponent *pCamera = GameInfo::Instance().GetActiveCamera();

		//std::vector<IEffectPass *>::iterator it;

		bgfx::setState(BGFX_STATE_RGB_WRITE | BGFX_STATE_ALPHA_WRITE | BGFX_STATE_DEPTH_WRITE
			| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA));

		bgfx::setVertexBuffer(m_VertexBuffer);
		bgfx::setIndexBuffer(m_IndexBuffer);

// 		m_pEffect->Begin();
// 
// 		for (it = m_pEffect->PassesBeginIterator();
// 			it != m_pEffect->PassesEndIterator();
// 			it++)
// 		{
// 			(*it)->Begin();
// 			
// 			(*it)->GetShader()->SetParameter("ModelViewProj", pCamera->GetViewMatrix() * pCamera->GetProjectionMatrix());
// 
// 			for (int i=0; i<m_SpriteBatches.size(); i++)
// 			{
// 				IRenderer::Get().SetTexture(0, m_SpriteBatches[i].Texture);
// 				// TODO : display all in one pass ?
// 				IRenderer::Get().DrawIndexedPrimitives(PrimitiveType::TriangleList, indexPos * 6, m_SpriteBatches[i].NbSprite * 2);
// 				indexPos += m_SpriteBatches[i].NbSprite;
// 			}
// 
// 			(*it)->End();			
// 		}
// 
// 		m_pEffect->End();

		bgfx::setState(BGFX_STATE_DEFAULT);

	}

	/**
	 * 
	 */
	void SpriteRenderer::Clear()
	{

	}

	/**
	 * 
	 */
	void SpriteRenderer::AddSprite(const Texture *tex_, 
		const CRectangle &src_, const Vector2I &origin, const Vector2F &pos_, 
		float /*rot_*/, const Vector2F &scale_, const CColor &color_, float ZOrder_, eSpriteEffects /*effects_*/)
	{
		if (tex_ == nullptr)
		{
			throw NEW_AO CException("SpriteRenderer.AddSprite() : Texture is nullptr");
		}

		if (m_NbElt >= (unsigned int) m_MaxSprite)
		{
			CA_ERROR("SpriteRenderer : number of sprite exceed (%d)\n", m_MaxSprite);
			return;
		}

		//m_SpriteTextures.push_back(tex_->GetTexture());

		//used to convert the size of the texture to a "3D size"
		//ratio : 100px => 1.0
		const float sizeCoeff = 100.0f;

		unsigned int color = color_.ToRGBA();

		float texW = 512; // (float) tex_->GetTexture()->GetSize().x;
		float texH = 512; //(float) tex_->GetTexture()->GetSize().y;
		float texTop =		(float) src_.Top()		/ texH;
		float texBottom =	(float) src_.Bottom()	/ texH;
		float texLeft =		(float) src_.Left()		/ texW;
		float texRight =	(float) src_.Right()	/ texW;

		float top =		pos_.y + (float) origin.y							* scale_.y / sizeCoeff;
		float bottom =	pos_.y + ((float) origin.y - (float) src_.Height())	* scale_.y / sizeCoeff;
		float left =	pos_.x + (float) origin.x							* scale_.x / sizeCoeff;
		float right =	pos_.x + ((float) origin.x - (float) src_.Width())	* scale_.x / sizeCoeff;

		SpriteDisplayData spriteData;

		//texture
		//spriteData.Texture = tex_->GetTexture();
		//Left-Top
		spriteData.TopLeft.Position.x = left;
		spriteData.TopLeft.Position.y = top;
		spriteData.TopLeft.Position.z = ZOrder_;
		spriteData.TopLeft.Color = color;
		spriteData.TopLeft.TexCoords.x = texLeft;
		spriteData.TopLeft.TexCoords.y = texTop;
		//Right-Top
		spriteData.TopRight.Position.x = right;
		spriteData.TopRight.Position.y = top;
		spriteData.TopRight.Position.z = ZOrder_;
		spriteData.TopRight.Color = color;
		spriteData.TopRight.TexCoords.x = texRight;
		spriteData.TopRight.TexCoords.y = texTop;
		//Right-Bottom
		spriteData.BottomRight.Position.x = right;
		spriteData.BottomRight.Position.y = bottom;
		spriteData.BottomRight.Position.z = ZOrder_;
		spriteData.BottomRight.Color = color;
		spriteData.BottomRight.TexCoords.x = texRight;
		spriteData.BottomRight.TexCoords.y = texBottom;
		//Left-Bottom
		spriteData.BottomLeft.Position.x = left;
		spriteData.BottomLeft.Position.y = bottom;
		spriteData.BottomLeft.Position.z = ZOrder_;
		spriteData.BottomLeft.Color = color;
		spriteData.BottomLeft.TexCoords.x = texLeft;
		spriteData.BottomLeft.TexCoords.y = texBottom;

		m_SpriteDatas.push_back(spriteData);

		m_NbElt++;
	}

	/**
	 *	
	 */
	void SpriteRenderer::AddSprite(Sprite* pSprite_, const Vector2F &pos_, 
		float rot_, const Vector2F &scale_, const CColor &color_, float ZOrder_, eSpriteEffects effects_)
	{
		if (pSprite_->GetTexture2D() == nullptr)
		{
			throw NEW_AO CException("CSpriteRenderer.AddSprite() : Sprite.GetTexture() is nullptr");
		}

		AddSprite(pSprite_->GetTexture2D(), pSprite_->GetPositionInTexture(), 
			pSprite_->GetOrigin(), pos_, rot_, scale_, color_, ZOrder_, effects_);
	}

} // namespace CasaEngine
