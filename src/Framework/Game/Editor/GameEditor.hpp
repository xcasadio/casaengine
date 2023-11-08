#ifndef GAME_EDITOR_H
#define GAME_EDITOR_H

#include  "Game/Game.hpp"
#include  "Sprite/SpriteRenderer.hpp"
#include  "Game/Input.hpp"
#include  "Game/Line3DRendererComponent.hpp"
#include  "World/World.hpp"

namespace CasaEngine
{
	class CA_EXPORT GameEditor :
		public Game
	{
	public:
		GameEditor(sf::WindowHandle handle_);
		~GameEditor() override;

		void Initialize() override;
		void LoadContent() override;

	private:
		SpriteRenderer* m_SpriteRenderer;
		Line3DRendererComponent* m_pLineRenderer;

		World* m_pWorld;
	};
}

#endif // GAME_EDITOR_H
