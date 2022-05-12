#include "Base.h"
#include "Datas/SpriteData.h"
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
		_collisionShapes.clear();
		for (auto coll : rsh._collisionShapes)
		{
			_collisionShapes.push_back(*coll.Copy());
		}

		IAssetable::operator=(rsh);

		return *this;
	}

	SpriteData::~SpriteData()
	{
		Clear();
	}

	Rectangle SpriteData::GetPositionInTexture() const
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
		for (auto it = _collisionShapes.begin();
			it != _collisionShapes.end();
			it++)
		{
			delete it->GetShape();
		}

		_collisionShapes.clear();*/
	}

	SpriteData* SpriteData::Copy()
	{
		return new SpriteData(*this);
	}

//#ifdef EDITOR

	void SpriteData::SetPositionInTexture(Rectangle val)
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

//#endif

}
