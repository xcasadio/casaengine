#include  "Base.hpp"
#include  "Animation2dLoader.hpp"
#include  "Datas/Animation2DData.hpp"
#include  "Game/Game.hpp"
#include  "Serializer/Serializer.hpp"

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

		//for (auto& anim : animations)
		//{
		//	for (auto& frame : anim._frames)
		//	{
		//		frame._duration /= 10.0f;
		//	}
		//}
		//
		//std::ofstream os("C:\\Users\\casad\\dev\\repo\\casaengine\\examples\\resources\\datas\\animations2.json");
		//json j2;
		//to_json(j2, animations, "animations");
		//os << std::setw(4) << j2 << std::endl; // pretty json

		for (const auto& animation : animations)
		{
			Game::Instance().GetAssetManager().AddAsset(animation.GetName(), animation.Copy());
		}

		return animations;
	}
}
