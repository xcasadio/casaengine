#pragma once

#include "CA_Export.hpp"
#include  "Assets/Assetable.hpp"
#include  "Graphics/Textures/Texture.hpp"
#include  "Maths/Vector2.hpp"

namespace CasaEngine
{
	class CA_EXPORT Material :
		public IAssetable
	{
	public:
		Material();
		Material& operator = (const Material& rsh_);
		Material(const Material& rsh_);
		~Material() override;

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
