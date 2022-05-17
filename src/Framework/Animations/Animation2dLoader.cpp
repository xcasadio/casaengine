#include "Base.h"
#include "Animation2dLoader.h"
#include "Datas/Animation2DData.h"
#include "Game/Game.h"
#include "Serializer/Serializer.h"

namespace CasaEngine
{
	std::vector<Animation2DData> Animation2dLoader::LoadFromFile(const std::string& fileName)
	{
		std::vector<Animation2DData> animations;
		auto* file = Game::Instance().GetMediaManager().FindMedia(fileName, false);
		std::stringstream ss;
		ss << file->GetBuffer();
		json j;
		ss >> j;
		from_json(j["animations"], animations);

		for (const auto& animation : animations)
		{
			Game::Instance().GetAssetManager().AddAsset(animation.GetName(), animation.Copy());
		}

		return animations;
	}
}
