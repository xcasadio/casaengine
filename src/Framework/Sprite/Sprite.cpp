#include "Base.h"

#include "Sprite/Sprite.h"
#include "Parsers/Xml/tinyxml2.h"
#include <iosfwd>
#include "Maths/Vector2.h"
#include "Maths/Rectangle.h"
#include "Graphics/Textures/Texture.h"
#include "Resources/ResourceManager.h"


namespace CasaEngine
{
	Sprite::Sprite() :
		m_pTexture2D(nullptr)
	{

	}

	Sprite::~Sprite()
	{
		Clear();
	}

	Texture* Sprite::GetTexture2D() const
	{
		return m_pTexture2D;
	}

	CRectangleI Sprite::GetPositionInTexture() const
	{
		return m_PositionInTexture;
	}

	Vector2I Sprite::GetOrigin() const
	{
		return m_Origin;
	}

	std::string Sprite::GetAssetFileName() const
	{
		return m_AssetFileName;
	}

	void Sprite::Clear()
	{
		for (std::vector<IShape*>::iterator it = m_CollisionShapes.begin();
			it != m_CollisionShapes.end();
			it++)
		{
			DELETE_AO* it;
		}

		m_CollisionShapes.clear();
	}

	/**
	 *
	 */
	void Sprite::Read(const tinyxml2::XMLElement& el_)
	{
		Clear();
		IAssetable::Read(el_);

		const tinyxml2::XMLElement* pElem, * pChild;

		m_AssetFileName = el_.FirstChildElement("AssetFileName")->GetText();
		//m_Name = el_->Attribute("name");
		//m_Name = el_->Attribute("id");
		SetName(el_.Attribute("id")); // TODO : ID is not the name

		Texture* pTexture = ResourceManager::Instance().Get<Texture>(m_AssetFileName.c_str());
		
		if (nullptr == pTexture)
		{
			pTexture = Texture::loadTexture(m_AssetFileName.c_str());
			ResourceManager::Instance().Add(m_AssetFileName.c_str(), pTexture);
		}
		
		m_pTexture2D = pTexture;

		pElem = el_.FirstChildElement("PositionInTexture");
		int x, y, w, h;
		pElem->QueryIntAttribute("x", &x);
		pElem->QueryIntAttribute("y", &y);
		pElem->QueryIntAttribute("width", &w);
		pElem->QueryIntAttribute("height", &h);
		m_PositionInTexture.Set(x, y, w, h);

		pElem = el_.FirstChildElement("HotSpot");
		pElem->QueryIntAttribute("x", &m_Origin.x);
		pElem->QueryIntAttribute("y", &m_Origin.y);

		pElem = el_.FirstChildElement("CollisionList");
		pChild = pElem->FirstChildElement("Shape");

		while (pChild != nullptr)
		{
			IShape* pShape = IShape::LoadShape(*pChild);
			m_CollisionShapes.push_back(pShape);
			pChild = pChild->NextSiblingElement();
		}
	}

	/**
	 *
	 */
	void Sprite::Read(std::ifstream& /*in*/)
	{

	}

	//#ifdef EDITOR

	void Sprite::SetTexture2D(Texture* val)
	{
		m_pTexture2D = val;
	}

	void Sprite::SetPositionInTexture(CRectangleI val)
	{
		m_PositionInTexture = val;
	}

	void Sprite::SetOrigin(Vector2I val)
	{
		m_Origin = val;
	}

	void Sprite::SetAssetFileName(std::string val)
	{
		m_AssetFileName = val;
	}

	void Sprite::Write(const tinyxml2::XMLElement& /*node_*/)
	{

	}

	void Sprite::Write(std::ostream& /*os*/)
	{

	}

	/**
	 *
	 */
	std::vector<IShape*>::iterator Sprite::GetCollisionShapeIterator()
	{
		return m_CollisionShapes.begin();
	}

	/**
	 *
	 */
	std::vector<IShape*>::iterator Sprite::GetCollisionShapeIteratorEnd()
	{
		return m_CollisionShapes.end();
	}

	//#endif // EDITOR

}
