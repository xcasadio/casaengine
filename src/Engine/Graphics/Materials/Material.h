#ifndef MATERIAL_H
#define MATERIAL_H

#include "CA_Export.h"
#include "Assets/Assetable.h"
#include "Graphics\Textures\Texture.h"
#include "Maths\Vector2.h"

namespace CasaEngine
{
	class CA_EXPORT Material :
		public IAssetable
	{
	public:
		Material();
		Material& operator = (const Material& rsh_);
		Material(const Material& rsh_);
		~Material();

		Material* Clone() const;

		Texture* Texture0() const;
		void Texture0(Texture* pVal);

		Vector2 Texture0Repeat() const;
		void Texture0Repeat(Vector2 val);

	private:

		Texture* m_pTexture0;
		Texture* m_pTexture1;
		Texture* m_pTexture2;
		Texture* m_pTexture3;

	public: // TODO : used only for imgui, do it in another way
		Vector2 m_Texture0Repeat;
	};
}

#endif
