
#include "Base.h"

#include "Material.h"
#include "bgfx.h"

namespace CasaEngine
{
	/**
	 * 
	 */
	Material::Material()		
	{
		m_Texture0Repeat = Vector2F::One();
		m_pTexture0 = nullptr;
		m_pTexture1 = nullptr;
		m_pTexture2 = nullptr;
		m_pTexture3 = nullptr;
	}
	/**
	 * 
	 */
	Material &Material::operator=(const Material &rsh_)
	{
		m_pTexture0 = rsh_.m_pTexture0;
		m_pTexture1 = rsh_.m_pTexture1;
		m_pTexture2 = rsh_.m_pTexture2;
		m_pTexture3 = rsh_.m_pTexture3;
		m_Texture0Repeat = rsh_.m_Texture0Repeat;
 		return *this;
	}

	/**
	 * 
	 */
	Material::Material(const Material &rsh_)
	{
		*this = rsh_;
	}

	/**
	 * 
	 */
	Material::~Material()
	{

	}

	/**
	 * 
	 */
	Material* Material::Clone() const
	{
		Material* pRes = NEW_AO Material();
		*pRes = *this;
		return pRes;
	}

	Texture *Material::Texture0() const
	{
		return m_pTexture0;
	}

	void Material::Texture0(Texture *pVal_)
	{
		m_pTexture0 = pVal_;
	}

	Vector2F Material::Texture0Repeat() const
	{
		return m_Texture0Repeat;
	}

	void Material::Texture0Repeat(Vector2F val_)
	{
		m_Texture0Repeat = val_;
	}

} // namespace CasaEngine
