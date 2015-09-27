
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Resources\Resource.h"
#include "CA_Export.h"
#include "Graphics\Textures\Texture.h"
#include "Maths\Vector2.h"
#include "Memory/MemoryAllocation.h"
#include "bgfx.h"


namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT Material : 
		public IResource
	{
	public:
		Material();
		Material &operator = (const Material &rsh_);
		Material(const Material &rsh_);
		~Material();

		Material* Clone() const;

		Texture *Texture0() const;
		void Texture0(Texture *pVal);

		Vector2F Texture0Repeat() const;
		void Texture0Repeat(Vector2F val);

	private:

		Texture *m_pTexture0;
		Texture *m_pTexture1;
		Texture *m_pTexture2;
		Texture *m_pTexture3;

	public: // TODO : used only for imgui, do it in another way
		Vector2F m_Texture0Repeat;
	};

} // namespace CasaEngine

#endif // MATERIAL_H
