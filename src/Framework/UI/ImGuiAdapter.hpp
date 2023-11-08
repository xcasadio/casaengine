#pragma once

#include "CA_Export.hpp"
#include  "Graphics/Materials/Material.hpp"
#include <map>
#include <SFML/Window/Event.hpp>

#include  "GameTime.hpp"

namespace CasaEngine
{
	class CA_EXPORT ImGuiAdapter
	{
	public:
		static void Create(float _fontSize = 18.0f);
		static void Destroy();

		static void Update(const GameTime& gameTime);
		static void UpdateInput(const sf::Event& event);

		static void BeginFrame(unsigned short _width, unsigned short _height, unsigned char _view = 255);
		static void EndFrame();

		static void DisplayUI4Material(Material& mat_, int x_, int y_, int width_, int height_, bool enabled_);

	private:
		static std::map<int, int> m_Vars;
	};
}