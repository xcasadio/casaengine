#include "Base.h"
#include "Datas/SpriteData.h"
#include "Game/Game.h"
#include "Maths/Vector2.h"
#include "Maths/Rectangle.h"


namespace CasaEngine
{
	SpriteData::SpriteData()
		= default;

	SpriteData::SpriteData(const SpriteData& rsh)
	{
		*this = rsh;
	}

	SpriteData& SpriteData::operator=(const SpriteData& rsh)
	{
		_assetFileName = rsh._assetFileName;
		_positionInTexture = rsh._positionInTexture;
		_origin = rsh._origin;
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
		return _positionInTexture;
	}

	Vector2I SpriteData::GetOrigin() const
	{
		return _origin;
	}

	std::string SpriteData::GetAssetFileName() const
	{
		return _assetFileName;
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

	SpriteData* SpriteData::Copy() const
	{
		return new SpriteData(*this);
	}

	bool SpriteData::operator==(const SpriteData& rsh) const
	{
		return _positionInTexture == rsh._positionInTexture && _origin == rsh._origin && _assetFileName == rsh._assetFileName;
	}

	//#ifdef EDITOR

	void SpriteData::SetPositionInTexture(Rectangle val)
	{
		_positionInTexture = val;
	}

	void SpriteData::SetOrigin(Vector2I val)
	{
		_origin = val;
	}

	void SpriteData::SetAssetFileName(std::string val)
	{
		_assetFileName = val;
	}

	//#endif

}
