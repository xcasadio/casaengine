#include "Base.h"

#include "Game/DrawableGameComponent.h"
#include "Game/Game.h"
#include "Sprite/Sprite.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"
#include "Entities/Components/CameraComponent.h"
#include "Game/GameInfo.h"

#include <bx/math.h>

#include <vector>

namespace CasaEngine
{
	SpriteRenderer::SpriteRenderer(Game* pGame_) : 
		DrawableGameComponent(pGame_),
		m_MaxSprite(5000)
	{
		DrawOrder(5000);
	}

	SpriteRenderer::~SpriteRenderer()
	{
		delete[] m_pDatas;

		destroy(m_VertexBuffer);
		destroy(m_IndexBuffer);
		
		delete m_Program;
	}

	void SpriteRenderer::Initialize()
	{
		IGameComponent::Initialize();

		m_SpriteDatas.reserve(m_MaxSprite);
		m_SpriteBatches.reserve(m_MaxSprite);
		m_pDatas = new VertexPositionColorTexture[m_MaxSprite];
		m_VertexBuffer = createDynamicVertexBuffer(m_MaxSprite * 4, VertexPositionColorTexture::ms_layout);

		const int nbIndex = 6;
		auto pIndices = ::new short[nbIndex * 6];

		for (int i=0; i< nbIndex; i++)
		{
			pIndices[i * 6 + 0] = static_cast<short>(0 + i * 4);
			pIndices[i * 6 + 1] = static_cast<short>(2 + i * 4);
			pIndices[i * 6 + 2] = static_cast<short>(1 + i * 4);
			pIndices[i * 6 + 3] = static_cast<short>(0 + i * 4);
			pIndices[i * 6 + 4] = static_cast<short>(3 + i * 4);
			pIndices[i * 6 + 5] = static_cast<short>(2 + i * 4);
		}

		m_IndexBuffer = createIndexBuffer(bgfx::copy(pIndices, sizeof(short) * nbIndex * 6 ));
		delete[] pIndices;

		m_Program = new Program("vs_spritebatch", "fs_spritebatch");
		m_texColor = createUniform("s_texColor", bgfx::UniformType::Sampler);
	}

	void SpriteRenderer::Update(const GameTime& /*gametime_*/ )
	{
		m_SpriteDatas.clear();
	}

	void SpriteRenderer::Draw()
	{
		if (m_SpriteDatas.empty())
		{
			return;
		}

		UpdateBuffer();

		CameraComponent *pCamera = Game::Instance().GetGameInfo().GetActiveCamera();
		bgfx::setViewTransform(0, pCamera->GetViewMatrix(), pCamera->GetProjectionMatrix());

		for (auto i = 0; i < m_SpriteDatas.size(); i++)
		{
			bgfx::setState(BGFX_STATE_WRITE_MASK
				| BGFX_STATE_DEPTH_TEST_LESS
				//| BGFX_STATE_CULL_CW
				//| BGFX_STATE_MSAA
				| BGFX_STATE_BLEND_ALPHA);

			setVertexBuffer(0, m_VertexBuffer, i * 4, 4);
			setIndexBuffer(m_IndexBuffer, 0, 6);
			setTexture(0, m_texColor, m_SpriteDatas[i].Texture->Handle());
			//bgfx::setUniform(m_ColorUniform, m_SpriteDatas[i].Color);
			bgfx::setTransform(m_SpriteDatas[i].transform);
			submit(0, m_Program->Handle());			
		}
	}

	bool sortSpriteDatas(SpriteRenderer::SpriteDisplayData i, SpriteRenderer::SpriteDisplayData j)
	{
		return i.transform.Translation().z < j.transform.Translation().z;
	}

	void SpriteRenderer::UpdateBuffer()
	{
		const int nbVertices = 4;

		std::sort(m_SpriteDatas.begin(), m_SpriteDatas.end(), sortSpriteDatas);
		
		for (auto i = 0; i < m_SpriteDatas.size(); i++)
		{
			const int index = i * nbVertices;

			m_pDatas[index + 0].Position.x = m_SpriteDatas[i].TopLeft.Position.x;
			m_pDatas[index + 0].Position.y = m_SpriteDatas[i].TopLeft.Position.y;
			m_pDatas[index + 0].Position.z = m_SpriteDatas[i].TopLeft.Position.z;
			m_pDatas[index + 0].TexCoords.x = m_SpriteDatas[i].TopLeft.TexCoords.x;
			m_pDatas[index + 0].TexCoords.y = m_SpriteDatas[i].TopLeft.TexCoords.y;
			m_pDatas[index + 0].Color = m_SpriteDatas[i].TopLeft.Color;
			m_pDatas[index + 1].Position.x = m_SpriteDatas[i].TopRight.Position.x;
			m_pDatas[index + 1].Position.y = m_SpriteDatas[i].TopRight.Position.y;
			m_pDatas[index + 1].Position.z = m_SpriteDatas[i].TopRight.Position.z;
			m_pDatas[index + 1].TexCoords.x = m_SpriteDatas[i].TopRight.TexCoords.x;
			m_pDatas[index + 1].TexCoords.y = m_SpriteDatas[i].TopRight.TexCoords.y;
			m_pDatas[index + 1].Color = m_SpriteDatas[i].TopRight.Color;
			m_pDatas[index + 2].Position.x = m_SpriteDatas[i].BottomRight.Position.x;
			m_pDatas[index + 2].Position.y = m_SpriteDatas[i].BottomRight.Position.y;
			m_pDatas[index + 2].Position.z = m_SpriteDatas[i].BottomRight.Position.z;
			m_pDatas[index + 2].TexCoords.x = m_SpriteDatas[i].BottomRight.TexCoords.x;
			m_pDatas[index + 2].TexCoords.y = m_SpriteDatas[i].BottomRight.TexCoords.y;
			m_pDatas[index + 2].Color = m_SpriteDatas[i].BottomRight.Color;
			m_pDatas[index + 3].Position.x = m_SpriteDatas[i].BottomLeft.Position.x;
			m_pDatas[index + 3].Position.y = m_SpriteDatas[i].BottomLeft.Position.y;
			m_pDatas[index + 3].Position.z = m_SpriteDatas[i].BottomLeft.Position.z;
			m_pDatas[index + 3].TexCoords.x = m_SpriteDatas[i].BottomLeft.TexCoords.x;
			m_pDatas[index + 3].TexCoords.y = m_SpriteDatas[i].BottomLeft.TexCoords.y;
			m_pDatas[index + 3].Color = m_SpriteDatas[i].BottomLeft.Color;
		}

		const uint32_t size = m_SpriteDatas.size() * 4 * sizeof(VertexPositionColorTexture);
		update(m_VertexBuffer, 0, bgfx::makeRef(m_pDatas, size));
	}

	void SpriteRenderer::AddSprite(const Sprite* sprite, const Matrix4& transform, const CColor& color_, float z_order, eSpriteEffects effects_)
	{
		if (sprite == nullptr)
		{
			throw new CException("Sprite is null");
		}
		
		AddSprite(sprite->GetTexture2D(), sprite->GetSpriteData()->GetPositionInTexture(), sprite->GetSpriteData()->GetOrigin(), transform, color_, z_order, effects_);
	}

	void SpriteRenderer::AddSprite(const Texture* tex_,
		const RectangleI& posInTex, const Vector2I& origin, const Matrix4& transform, const CColor& color_, float z_order, eSpriteEffects effects_)
	{
		if (tex_ == nullptr)
		{
			throw new CException("Texture is null");
		}
		
		if (m_SpriteDatas.size() >= m_MaxSprite)
		{
			return;
		}

		const unsigned int color = color_.ToABGR();

		auto top = static_cast<float>(posInTex.Top());
		auto bottom = static_cast<float>(posInTex.Bottom());
		auto left = static_cast<float>(posInTex.Left());
		auto right = static_cast<float>(posInTex.Right());

		if (effects_ == eSpriteEffects::SPRITE_EFFECT_FLIP_HORIZONTALLY)
		{
			auto tmp = left;
			left = right;
			right = tmp;
		}
		if (effects_ == eSpriteEffects::SPRITE_EFFECT_FLIP_VERTICALLY)
		{
			auto tmp = top;
			top = bottom;
			bottom = tmp;
		}

		const float texW = tex_->TextureInfo()->width;
		const float texH = tex_->TextureInfo()->height;
		const float texTop = top / texH;
		const float texBottom = bottom / texH;
		const float texLeft = left / texW;
		const float texRight = right / texW;

		SpriteDisplayData spriteData;

		//texture
		spriteData.Texture = tex_;
		Matrix4 worldMatrix = transform;
		Matrix4 offsetMatrix;
		//Todo : get scale
		offsetMatrix = Matrix4::CreateTranslation(-origin.x * transform.m11, -origin.y * transform.m22, 0.0f);
		spriteData.transform = worldMatrix * offsetMatrix;
		//Left-Top
		spriteData.TopLeft.Position.x = 0.0f;
		spriteData.TopLeft.Position.y = 0.0f;
		spriteData.TopLeft.Position.z = z_order;
		spriteData.TopLeft.Color = color;
		spriteData.TopLeft.TexCoords.x = texLeft;
		spriteData.TopLeft.TexCoords.y = texTop;
		//Right-Top
		spriteData.TopRight.Position.x = 1.0f * posInTex.w;
		spriteData.TopRight.Position.y = 0.0f;
		spriteData.TopRight.Position.z = z_order;
		spriteData.TopRight.Color = color;
		spriteData.TopRight.TexCoords.x = texRight;
		spriteData.TopRight.TexCoords.y = texTop;
		//Right-Bottom
		spriteData.BottomRight.Position.x = 1.0f * posInTex.w;
		spriteData.BottomRight.Position.y = 1.0f * posInTex.h;
		spriteData.BottomRight.Position.z = z_order;
		spriteData.BottomRight.Color = color;
		spriteData.BottomRight.TexCoords.x = texRight;
		spriteData.BottomRight.TexCoords.y = texBottom;
		//Left-Bottom
		spriteData.BottomLeft.Position.x = 0.0f;
		spriteData.BottomLeft.Position.y = 1.0f * posInTex.h;
		spriteData.BottomLeft.Position.z = z_order;
		spriteData.BottomLeft.Color = color;
		spriteData.BottomLeft.TexCoords.x = texLeft;
		spriteData.BottomLeft.TexCoords.y = texBottom;

		m_SpriteDatas.push_back(spriteData);
	}

	void SpriteRenderer::AddSprite(const Texture* tex_,
		const RectangleI& posInTex, const Vector2I& origin, const Vector2F& pos,
		float rot, const Vector2F& scale, const CColor& color, float z_order, eSpriteEffects effects)
	{
		if (tex_ == nullptr)
		{
			throw new CException("Texture is null");
		}

		if (m_SpriteDatas.size() >= m_MaxSprite)
		{
			return;
		}

		Quaternion quaternionRotation;
		quaternionRotation.FromAxisAngle(Vector3F::UnitZ(), rot);
		Matrix4 transform;
		//transform.SetTranslation(Vector3F(pos.x, pos.y));
		//transform.CreateScale(scale.x, scale.y, 0.0f);
		transform.Transformation(nullptr,
			nullptr, &Vector3F(scale.x, scale.y, 1.0f),
			&Vector3F(origin.x, origin.y), &quaternionRotation,
			&Vector3F(pos.x, pos.y));
		AddSprite(tex_, posInTex, origin, transform, color, z_order, effects);
	}

	void SpriteRenderer::AddSprite(Sprite* pSprite, const Vector2F &pos_, 
		float rot_, const Vector2F &scale_, const CColor &color_, float ZOrder_, eSpriteEffects effects_)
	{
		if (pSprite->GetTexture2D() == nullptr)
		{
			throw new CException("Sprite is null");
		}

		AddSprite(pSprite->GetTexture2D(), pSprite->GetSpriteData()->GetPositionInTexture(),
			pSprite->GetSpriteData()->GetOrigin(), pos_, rot_, scale_, color_, ZOrder_, effects_);
	}

	void SpriteRenderer::AddSprite(Sprite* pSprite_, const Vector2F& pos_, float rot_, const CColor& color_,
		float ZOrder_, eSpriteEffects effects_)
	{
		AddSprite(pSprite_->GetTexture2D(), pSprite_->GetSpriteData()->GetPositionInTexture(),
			pSprite_->GetSpriteData()->GetOrigin(), pos_, rot_,
			Vector2F(pSprite_->GetSpriteData()->GetPositionInTexture().w, pSprite_->GetSpriteData()->GetPositionInTexture().h),
			color_, ZOrder_, effects_);
	}
}
