#pragma once

#include "CA_Export.hpp"

#include  "Game/DrawableGameComponent.hpp"
#include  "GameTime.hpp"
#include  "Graphics/Color.hpp"

#include  "Graphics/Textures/Texture.hpp"

#include  "Graphics/Vertices/VertexType.hpp"
#include  "Maths/Rectangle.hpp"
#include  "Maths/Vector2.hpp"
#include  "Sprite/Sprite.hpp"
#include  "Sprite/SpriteTypes.hpp"

#include <vector>

#include  "Graphics/Effects/Program.hpp"

namespace CasaEngine
{
	class CA_EXPORT SpriteRenderer :
		public DrawableGameComponent
	{
	public:
		/// Use to remember how to draw sprite
		struct SpriteDisplayData
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
		struct SpriteBatch
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

		void AddSprite(const Sprite* sprite, const Matrix4& transform, const Color& color_, eSpriteEffects effects_ =
			               eSpriteEffects::SPRITE_EFFECT_NONE);
		void AddSprite(const Texture* tex_, const Rectangle& posInTex, const Vector2I& origin, const Matrix4& transform, const Color& color_,
		               eSpriteEffects effects_ = eSpriteEffects::SPRITE_EFFECT_NONE);
		void AddSprite(const Texture *tex_, 
			const Rectangle &posInTex, const Vector2I &origin, const Vector2 &pos,
			float rot, const Vector2 &scale, const Color &color, float ZOrder_, eSpriteEffects effects = eSpriteEffects::SPRITE_EFFECT_NONE);
		void AddSprite(Sprite* pSprite, const Vector2 &pos_, 
			float rot_, const Vector2 &scale_, const Color &color_, float ZOrder_, eSpriteEffects effects_ = eSpriteEffects::SPRITE_EFFECT_NONE);
		void AddSprite(Sprite* pSprite_, const Vector2& pos_,
				float rot_, const Color& color_, float ZOrder_, eSpriteEffects effects_ = eSpriteEffects::SPRITE_EFFECT_NONE);

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
