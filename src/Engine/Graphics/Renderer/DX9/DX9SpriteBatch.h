
#ifndef DX9SPRITEBATCH_H_
#define DX9SPRITEBATCH_H_

#include "Base.h"
#include "Graphics/SpriteBatch.h"
#include "d3dx9core.h"
#include "SmartPtrPolicies.h"
#include "SmartPtr.h"
#include "Graphics/SpriteTypes.h"

namespace CasaEngine
{

	class DX9SpriteBatch :
		public ISpriteBatch
	{
	public:
		DX9SpriteBatch(ID3DXSprite *spriteBatch);
		~DX9SpriteBatch();

		virtual void Begin(int flags);
		virtual void End();
		virtual void Draw(ITextureBase *Texture2D, CRectangle &PositionInTexture, Vector2I &Origin, Vector2F &Position, float Rotation, Vector2F &Scale, CColor &Color, float ZOrder, eSpriteEffects SpriteEffect);

	private:
		SmartPtr<ID3DXSprite, CResourceCOM> m_D3DSprite;
	};

} // namespace CasaEngine

#endif
