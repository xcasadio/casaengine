#include "DX9SpriteBatch.h"
#include "Graphics/Textures/Texture.h"
#include "Maths/Rectangle.h"
#include "Maths/Vector2.h"
#include "Graphics/SpriteTypes.h"
#include "DX9Texture.h"
#include "DX9Macro.h"
#include "Exceptions.h"

namespace CasaEngine
{

DX9SpriteBatch::DX9SpriteBatch(ID3DXSprite *spriteBatch) :
	m_D3DSprite(spriteBatch)
{
	if (m_D3DSprite == NULL)
	{
		throw new CArgumentNullException("DX9SpriteBatch() : ID3DXSprite is NULL");
	}
}


DX9SpriteBatch::~DX9SpriteBatch()
{
}

//////////////////////////////////////////////////////////////////////////////
// D3DXSPRITE flags:
// -----------------
// D3DXSPRITE_DONOTSAVESTATE
//   Specifies device state is not to be saved and restored in Begin/End.
// D3DXSPRITE_DONOTMODIFY_RENDERSTATE
//   Specifies device render state is not to be changed in Begin.  The device
//   is assumed to be in a valid state to draw vertices containing POSITION0, 
//   TEXCOORD0, and COLOR0 data.
// D3DXSPRITE_OBJECTSPACE
//   The WORLD, VIEW, and PROJECTION transforms are NOT modified.  The 
//   transforms currently set to the device are used to transform the sprites 
//   when the batch is drawn (at Flush or End).  If this is not specified, 
//   WORLD, VIEW, and PROJECTION transforms are modified so that sprites are 
//   drawn in screenspace coordinates.
// D3DXSPRITE_BILLBOARD
//   Rotates each sprite about its center so that it is facing the viewer.
// D3DXSPRITE_ALPHABLEND
//   Enables ALPHABLEND(SRCALPHA, INVSRCALPHA) and ALPHATEST(alpha > 0).
//   ID3DXFont expects this to be set when drawing text.
// D3DXSPRITE_SORT_TEXTURE
//   Sprites are sorted by texture prior to drawing.  This is recommended when
//   drawing non-overlapping sprites of uniform depth.  For example, drawing
//   screen-aligned text with ID3DXFont.
// D3DXSPRITE_SORT_DEPTH_FRONTTOBACK
//   Sprites are sorted by depth front-to-back prior to drawing.  This is 
//   recommended when drawing opaque sprites of varying depths.
// D3DXSPRITE_SORT_DEPTH_BACKTOFRONT
//   Sprites are sorted by depth back-to-front prior to drawing.  This is 
//   recommended when drawing transparent sprites of varying depths.
// D3DXSPRITE_DO_NOT_ADDREF_TEXTURE
//   Disables calling AddRef() on every draw, and Release() on Flush() for
//   better performance.
//////////////////////////////////////////////////////////////////////////////
/*
#define D3DXSPRITE_DONOTSAVESTATE               (1 << 0)
#define D3DXSPRITE_DONOTMODIFY_RENDERSTATE      (1 << 1)
#define D3DXSPRITE_OBJECTSPACE                  (1 << 2)
#define D3DXSPRITE_BILLBOARD                    (1 << 3)
#define D3DXSPRITE_ALPHABLEND                   (1 << 4)
#define D3DXSPRITE_SORT_TEXTURE                 (1 << 5)
#define D3DXSPRITE_SORT_DEPTH_FRONTTOBACK       (1 << 6)
#define D3DXSPRITE_SORT_DEPTH_BACKTOFRONT       (1 << 7)
#define D3DXSPRITE_DO_NOT_ADDREF_TEXTURE        (1 << 8)
*/
void DX9SpriteBatch::Begin(int flags)
{
	DXCheck(m_D3DSprite->Begin(D3DXSPRITE_ALPHABLEND));
}

void DX9SpriteBatch::End()
{
	DXCheck(m_D3DSprite->Flush());
	DXCheck(m_D3DSprite->End());
}

void DX9SpriteBatch::Draw(
	ITextureBase *Texture2D, CRectangle &PositionInTexture, 
	Vector2I &Origin, Vector2F &Position, 
	float Rotation, Vector2F &Scale, CColor &Color, 
	float ZOrder, eSpriteEffects SpriteEffect )
{
	CDX9Texture *tex = dynamic_cast<CDX9Texture *>(Texture2D);
	RECT src;
	src.left = PositionInTexture.Left();
	src.right = PositionInTexture.Right();
	src.top = PositionInTexture.Top();
	src.bottom = PositionInTexture.Bottom();
	D3DXVECTOR2 center(static_cast<float>(Origin.x), static_cast<float>(Origin.y));
	D3DXVECTOR2 pos(Position.x - Origin.x, Position.y - Origin.y);

	D3DXMATRIX transform;
	DXCheck(D3DXMatrixTransformation2D(&transform, NULL, NULL, &D3DXVECTOR2(Scale.x, Scale.y), &center, Rotation, &pos));

	if (SUCCEEDED(DXCheck(m_D3DSprite->SetTransform(&transform))))
	{
		DXCheck(m_D3DSprite->Draw( tex->GetDxTexture(), &src, NULL, NULL,
				D3DCOLOR_RGBA(Color.GetRed(), Color.GetGreen(), Color.GetBlue(), Color.GetAlpha()) ));
	}	
}

} // namespace CasaEngine
