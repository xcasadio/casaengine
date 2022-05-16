#include "TiledMapCreator.h"
#include "Datas/TileData.h"
#include "StaticTile.h"
#include "AnimatedTile.h"
#include "Datas/Animation2DData.h"
#include "Datas/SpriteData.h"
#include "TileComponent.h"
#include "AutoTile.h"
#include "EmptyTile.h"
#include "Game/Game.h"
#include "Serializer/Serializer.h"
#include "Sprite/SpritePhysicsHelper.h"

#include <fstream>
#include <filesystem>

namespace CasaEngine
{
	void TiledMapCreator::LoadMapFromFile(std::string fileName, World& world)
	{
		auto* tiledMapData = new TiledMapData();

		{
			auto* file = Game::Instance().GetMediaManager().FindMedia(fileName, false);
			std::stringstream ss;
			ss << file->GetBuffer();
			json j;
			ss >> j;
			from_json(j, *tiledMapData);
		}

		TileSetData tileSetData;

		{
			auto* file = Game::Instance().GetMediaManager().FindMedia(tiledMapData->tileSetFileName, false);
			std::stringstream ss;
			ss << file->GetBuffer();
			json j;
			ss >> j;
			from_json(j, tileSetData);
		}

		AutoTileSetData autoTileSetData;

		{
			auto* file = Game::Instance().GetMediaManager().FindMedia(tiledMapData->autoTileSetFileName, false);
			std::stringstream ss;
			ss << file->GetBuffer();
			json j;
			ss >> j;
			from_json(j, autoTileSetData);
		}

		std::filesystem::path path(fileName);
		

		Create(path.stem().string(), autoTileSetData, tileSetData, *tiledMapData, world);
	}

	void TiledMapCreator::Create(std::string prefixName, AutoTileSetData& autoTileSetData, TileSetData& tileSetData, TiledMapData& tiledMapData, World& world)
	{
		auto* mapEntity = new BaseEntity();
		std::ostringstream oss;
		oss << "map_" << prefixName;
		mapEntity->SetName(oss.str());
		mapEntity->GetCoordinates() = tiledMapData.coordinates;
		// TODO : Add tile map component : does nothing, here only for saving purpose
		//mapEntity->IsPersistent(false);
		world.AddEntity(mapEntity);

		auto* physics_world = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld();
		auto layerIndex = 0;

		for (auto& layer : tiledMapData.layers)
		{
			auto* layerEntity = new BaseEntity();
			oss.str("");
			oss << "layer_" << layerIndex << "_" << prefixName;
			layerEntity->SetName(oss.str());
			const auto layerPos = layerEntity->GetCoordinates().GetLocalPosition();
			layerEntity->GetCoordinates().SetLocalPosition(Vector3(layerPos.x, layerPos.y, layerPos.z + layer.zOffset));
			layerEntity->IsPersistent(false);
			layerEntity->SetParent(mapEntity);
			world.AddEntity(layerEntity);
			int index = 0;

			for (const auto& tileId : layer.tilesId)
			{
				int x = (index % tiledMapData.mapSize.x);
				int y = (index / tiledMapData.mapSize.x);
				const int posX = x * tileSetData.tileSize.x;
				const int posY = y * tileSetData.tileSize.y;

				auto* tileEntity = new BaseEntity();
				oss.str("");
				oss << "tile_" << index << "_" << layerIndex << "_" << prefixName;
				tileEntity->SetName(oss.str());
				tileEntity->IsPersistent(false);
				tileEntity->SetParent(layerEntity);
				tileEntity->GetCoordinates().SetLocalPosition(Vector3(posX, 	posY, 0.0f));

				ITile* tile = nullptr;
				TileCollisionType collisionType = TileCollisionType::None;

				if (tileId == -1)
				{
					tile = new EmptyTile();
				}
				else
				{
					if (layer.type == TileType::Auto)
					{
						const auto* autoTileTileSetData = autoTileSetData.GetTileSetById(tileId);
						tile = CreateTile(*autoTileTileSetData, tileSetData, &layer, &tiledMapData, x, y);
						collisionType = autoTileTileSetData->tiles[0]->collisionType;
					}
					else
					{
						TileData* tileData = tileSetData.GetTileById(tileId);
						tile = CreateTile(*tileData);
						collisionType = tileData->collisionType;

						if (tileData == nullptr)
						{
							CA_WARN("TileData with id %d is null", tileId);
							continue;
						}
					}
				}

				if (collisionType != TileCollisionType::None)
				{
					auto* shape = new Rectangle(0, 0, tileSetData.tileSize.x, tileSetData.tileSize.y);
					auto position = Vector3(posX + tileSetData.tileSize.x / 2.0f, posY + tileSetData.tileSize.y / 2.0f, 0.0f);
					auto* collisionShape = physics_world->CreateCollisionShape(tileEntity, shape, position, CollisionHitType::Defense, collisionType == TileCollisionType::Blocked ? CollisionFlags::Static : CollisionFlags::NoResponse);
					physics_world->AddCollisionObject(collisionShape);
				}
				
				auto* tileComponent = new TileComponent(tileEntity);
				tileComponent->Tile(tile);
				tileEntity->GetComponentMgr()->AddComponent(tileComponent);
				world.AddEntity(tileEntity);

				index++;
			}

			layerIndex++;
		}
	}

	ITile* TiledMapCreator::CreateTile(TileData& tileData)
	{
		switch (tileData.type)
		{
		case TileType::Static:
		{
			auto* staticTileParams = static_cast<StaticTileData*>(&tileData);
			auto* sprite = Game::Instance().GetAssetManager().GetAsset<SpriteData>(staticTileParams->spriteId);
			return new StaticTile(new Sprite(*sprite));
		}

		case TileType::Animated:
		{
			auto* animatedTileParams = static_cast<AnimatedTileData*>(&tileData);
			auto* animation = Game::Instance().GetAssetManager().GetAsset<Animation2DData>(animatedTileParams->animation2DId);
			return new AnimatedTile(new Animation2D(*animation));
		}
		}

		CA_WARN("The type of tile %d is not supported", tileData.type);

		return nullptr;
	}

	ITile* TiledMapCreator::CreateTile(const AutoTileTileSetData& autoTileTileSetData, const TileSetData& tileSetData, TiledMapLayerData* layer, const TiledMapData* map, int x, int y)
	{
		std::vector<ITile*> tiles;

		for (auto* tileData : autoTileTileSetData.tiles)
		{
			tiles.push_back(CreateTile(*tileData));
		}

		auto* autoTile = new AutoTile();
		autoTile->SetTileInfo(tiles, tileSetData.tileSize, map->mapSize, layer, x, y);
		return autoTile;
	}

}
