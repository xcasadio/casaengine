#pragma once

#include "TileData.h"
#include "StaticTile.h"
#include "AnimatedTile.h"
#include "Datas/Animation2DData.h"
#include "Datas/SpriteData.h"
#include "TileComponent.h"
#include "AutoTile.h"
#include "Datas/AutoTileSetData.h"
#include "Game/Game.h"

namespace CasaEngine
{

	TileData::TileData(TileType type) :
		x(0),
		y(0),
		type(type)
	{

	}

	StaticTileData::StaticTileData() : TileData(TileType::Static)
	{

	}

	AnimatedTileData::AnimatedTileData() : TileData(TileType::Animated)
	{

	}

	AutoTileData::AutoTileData() : TileData(TileType::Auto)
	{

	}

	void TiledMapCreator::Create(TiledMapData& tiledMapParameters, World& world)
	{
		auto* mapEntity = new BaseEntity();
		mapEntity->GetCoordinates() = tiledMapParameters.coordinates;
		// TODO : Add tile map component : does nothing, here only for saving purpose
		//mapEntity->IsPersistent(false);
		world.AddEntity(mapEntity);

		for (auto& layer : tiledMapParameters.layers)
		{
			auto* layerEntity = new BaseEntity();
			const auto layerPos = layerEntity->GetCoordinates().GetLocalPosition();
			layerEntity->GetCoordinates().SetLocalPosition(Vector3(layerPos.x, layerPos.y, layerPos.z + layer.zOffset));
			layerEntity->IsPersistent(false);
			layerEntity->SetParent(mapEntity);
			world.AddEntity(layerEntity);

			for (const auto& tileParam : layer.tiles)
			{
				auto* tileEntity = new BaseEntity();
				//std::ostringstream oss;
				//oss << "tile_" << tileParam->x << "_" << tileParam->y;
				//tileEntity->SetName(oss.str());
				tileEntity->IsPersistent(false);
				tileEntity->SetParent(layerEntity);
				tileEntity->GetCoordinates().SetLocalPosition(Vector3(tileParam->x * tiledMapParameters.tileSize.x, tileParam->y * tiledMapParameters.tileSize.y, 0.0f));
			
				auto* tile = CreateTile(*tileParam, &layer, &tiledMapParameters);
				auto* tileComponent = new TileComponent(tileEntity);
				tileComponent->Tile(tile);
				tileEntity->GetComponentMgr()->AddComponent(tileComponent);
				world.AddEntity(tileEntity);
			}
		}
	}

	ITile* TiledMapCreator::CreateTile(TileData& tileParameters, TiledMapLayerData* layer, TiledMapData* map)
	{
		switch (tileParameters.type)
		{
		case TileType::Static:
		{
			auto* staticTileParams = static_cast<StaticTileData*>(&tileParameters);
			auto* sprite = Game::Instance().GetAssetManager().GetAsset<SpriteData>(staticTileParams->spriteId);
			return new StaticTile(new Sprite(*sprite));
		}

		case TileType::Animated:
		{
			auto* animatedTileParams = static_cast<AnimatedTileData*>(&tileParameters);
			auto* animation = Game::Instance().GetAssetManager().GetAsset<Animation2DData>(animatedTileParams->animation2DId);
			return new AnimatedTile(new Animation2D(*animation));
		}

		case TileType::Auto:
		{
			auto* autoTileParams = static_cast<AutoTileData*>(&tileParameters);
			auto* autoTileSetData = Game::Instance().GetAssetManager().GetAsset<AutoTileSetData>(autoTileParams->autoTileAssetName);
			auto* autoTile = new AutoTile(autoTileSetData);
			autoTile->SetTileInfo(map, layer, autoTileParams->x, autoTileParams->y);
			return autoTile;
		}
		}

		return nullptr;
	}

}