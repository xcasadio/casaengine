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
#include "Memory/ObjectPool.h"
#include "Sprite/Sprite.h"
#include "Sprite/SpriteTypes.h"
#include "Memory/MemoryAllocatedObject.h"

#include <string>
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
		};

		/// Use to draw several sprites with the same texture
		/// used only with a Buffer sorted by depth and texture
		struct SpriteBatch :
			public AllocatedObject<SpriteDisplayData>
		{
		public:
			const Texture *Texture;
			int NbSprite;
		};

	public:
		SpriteRenderer(Game* game_);
		~SpriteRenderer();

		void Initialize();

		/// The Sprite list is clear during Update
		/// @remark Must be call at the beginning of the frame (before another Update())
		/// else the sprites added before will be removed
		/// 
		/// @param[in]: CGameTime & gametime_
		/// 
		/// @return void
		void Update(const GameTime& gametime_);
		void Draw();

		/*
		 *	
		 */
		void AddSprite(const Texture *tex_, 
			const CRectangle &src_, const Vector2I &origin, const Vector2F &pos_, 
			float rot_, const Vector2F &scale_, const CColor &color_, float ZOrder_, eSpriteEffects effects_);

		/*
		 *	
		 */
		void AddSprite(Sprite* pSprite_, const Vector2F &pos_, 
			float rot_, const Vector2F &scale_, const CColor &color_, float ZOrder_, eSpriteEffects effects_);

	private:
		void Clear();
		void UpdateBuffer();

	private:
		std::vector<SpriteDisplayData> m_SpriteDatas;
		std::vector<SpriteBatch> m_SpriteBatches;

		int m_MaxSprite;

		bgfx::ProgramHandle m_Program;
		bgfx::DynamicVertexBufferHandle m_VertexBuffer;
		bgfx::IndexBufferHandle m_IndexBuffer;
		VertexPositionColorTexture *m_pDatas;

		unsigned int m_NbElt;
	};
} // namespace CasaEngine

#endif //_SPRITERENDERER_H_
