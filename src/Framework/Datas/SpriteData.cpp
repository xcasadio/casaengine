#include "Base.h"

#include "Datas/SpriteData.h"
#include "Parsers/Xml/tinyxml2.h"

#include "Game/Game.h"
#include "Maths/Vector2.h"
#include "Maths/Rectangle.h"


namespace CasaEngine
{
	SpriteData::SpriteData()
	{

	}

	SpriteData::SpriteData(const SpriteData& rsh)
	{
		*this = rsh;
	}

	SpriteData& SpriteData::operator=(const SpriteData& rsh)
	{
		m_AssetFileName = rsh.m_AssetFileName;
		m_PositionInTexture = rsh.m_PositionInTexture;
		m_Origin = rsh.m_Origin;
		m_CollisionShapes.clear();
		for (auto coll : rsh.m_CollisionShapes)
		{
			m_CollisionShapes.push_back(*coll.Copy());
		}

		IAssetable::operator=(rsh);

		return *this;
	}

	SpriteData::~SpriteData()
	{
		Clear();
	}

	RectangleI SpriteData::GetPositionInTexture() const
	{
		return m_PositionInTexture;
	}

	Vector2I SpriteData::GetOrigin() const
	{
		return m_Origin;
	}

	std::string SpriteData::GetAssetFileName() const
	{
		return m_AssetFileName;
	}

	void SpriteData::Clear()
	{/*
		for (auto it = m_CollisionShapes.begin();
			it != m_CollisionShapes.end();
			it++)
		{
			DELETE_AO it->GetShape();
		}

		m_CollisionShapes.clear();*/
	}

	SpriteData* SpriteData::Copy()
	{
		return NEW_AO SpriteData(*this);
	}

//#ifdef EDITOR

	void SpriteData::SetPositionInTexture(RectangleI val)
	{
		m_PositionInTexture = val;
	}

	void SpriteData::SetOrigin(Vector2I val)
	{
		m_Origin = val;
	}

	void SpriteData::SetAssetFileName(std::string val)
	{
		m_AssetFileName = val;
	}

	std::vector<Collision>& SpriteData::GetCollisions()
	{
		return m_CollisionShapes;
	}

//#endif

}
