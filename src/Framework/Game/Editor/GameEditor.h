#ifndef GAME_EDITOR_H
#define GAME_EDITOR_H

#include "Game/Game.h"
#include "Sprite\SpriteRenderer.h"
#include "Game\Input.h"
#include "Game\Line3DRendererComponent.h"
#include "World\World.h"

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
		SpriteRenderer*	m_SpriteRenderer;
		Line3DRendererComponent *m_pLineRenderer;

		World *m_pWorld;
	};	
}

#endif // GAME_EDITOR_H
