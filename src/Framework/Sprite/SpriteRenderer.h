#ifndef _SPRITERENDERER_H_
#define _SPRITERENDERER_H_

#include "CA_Export.h"

#include "Game/DrawableGameComponent.h"
#include "Game/Game.h"
#include "GameTime.h"
#include "Graphics/Color.h"

#include "Graphics/Textures/Texture.h"

#include "Graphics/Vertices/VertexType.h"
#include "Maths/Rectangle.h"
#include "Maths/Vector2.h"
#include "Sprite/Sprite.h"
#include "Sprite/SpriteTypes.h"
#include "Memory/MemoryAllocatedObject.h"

#include <vector>

namespace CasaEngine
{
	class CA_EXPORT SpriteRenderer :
		public DrawableGameComponent
	{
	public:
		/// Use to remember how to draw sprite
		struct SpriteDisplayData/* : 
			public ObjectPool<SpriteDisplayData>*/
			: public AllocatedObject<SpriteDisplayData>
		{
		public:
			VertexPositionColorTexture TopLeft;
			VertexPositionColorTexture TopRight;
			VertexPositionColorTexture BottomLeft;
			VertexPositionColorTexture BottomRight;
			const Texture *Texture;

			Matrix4 transform;
		};

		/// Use to draw several sprites with the same texture
		/// used only with a Buffer sorted by depth and texture
		struct SpriteBatch :
			public AllocatedObject<SpriteDisplayData>
		{
		public:
			const Texture *Texture;
			//const Tra* Texture;
			int NbSprite;
		};

	public:
		SpriteRenderer(Game* game_);
		~SpriteRenderer() override;

		void Initialize() override;
		void Update(const GameTime& gametime_) override;
		void Draw() override;

		void AddSprite(const Sprite* sprite, const Matrix4& transform, const CColor& color_, float z_order, eSpriteEffects effects_ = eSpriteEffects::SPRITE_EFFECT_NONE);
		void AddSprite(const Texture* tex_, const RectangleI& posInTex, const Vector2I& origin, const Matrix4& transform, const CColor& color_, float z_order,
			eSpriteEffects effects_ = eSpriteEffects::SPRITE_EFFECT_NONE);
		void AddSprite(const Texture *tex_, 
			const RectangleI &posInTex, const Vector2I &origin, const Vector2F &pos_,
			float rot_, const Vector2F &scale_, const CColor &color_, float ZOrder_, eSpriteEffects effects_ = eSpriteEffects::SPRITE_EFFECT_NONE);
		void AddSprite(Sprite* pSprite_, const Vector2F &pos_, 
			float rot_, const Vector2F &scale_, const CColor &color_, float ZOrder_, eSpriteEffects effects_ = eSpriteEffects::SPRITE_EFFECT_NONE);
		void AddSprite(Sprite* pSprite_, const Vector2F& pos_,
				float rot_, const CColor& color_, float ZOrder_, eSpriteEffects effects_ = eSpriteEffects::SPRITE_EFFECT_NONE);

	private:
		void UpdateBuffer();
		
	private:
		std::vector<SpriteDisplayData> m_SpriteDatas;
		std::vector<SpriteBatch> m_SpriteBatches;

		int m_MaxSprite;

		bgfx::UniformHandle m_texColor{};
		Program *m_Program{};
		bgfx::DynamicVertexBufferHandle m_VertexBuffer{};
		bgfx::IndexBufferHandle m_IndexBuffer{};
		VertexPositionColorTexture *m_pDatas{};
	};
}

#endif
