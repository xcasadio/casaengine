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
		~GameEditor();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void Update( const GameTime& gameTime_ );
		virtual void Draw();

	private:
		SpriteRenderer*	m_SpriteRenderer;
		Line3DRendererComponent *m_pLineRenderer;

		World *m_pWorld;
	};	
}

#endif // GAME_EDITOR_H
