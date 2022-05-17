#include "SpriteLoader.h"

#include "Game/Game.h"
#include "Serializer/Serializer.h"

namespace CasaEngine
{
	std::vector<SpriteData> SpriteLoader::LoadFromFile(const std::string& fileName)
	{
		std::vector<SpriteData> sprites;
		auto* file = Game::Instance().GetMediaManager().FindMedia(fileName, false);
		std::stringstream ss;
		ss << file->GetBuffer();
		json j;
		ss >> j;
		from_json(j["sprites"], sprites);

		for (const auto& sprite : sprites)
		{
			Game::Instance().GetAssetManager().AddAsset(sprite.GetName(), sprite.Copy());
		}

		return sprites;
	}
}
