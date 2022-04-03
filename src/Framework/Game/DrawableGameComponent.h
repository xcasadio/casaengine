#ifndef _DRAWABLEGAMECOMPONENT_H_
#define _DRAWABLEGAMECOMPONENT_H_

#include "CA_Export.h"
#include "GameComponent.h"
#include "GameTime.h"

namespace CasaEngine
{
	class Game;
	
	class CA_EXPORT DrawableGameComponent :
		public IGameComponent
	{
	public:
		virtual void OnLoadContent();
		virtual void Draw() = 0;

		int DrawOrder() const;
		void DrawOrder(int val);

	protected :
		DrawableGameComponent(Game* pGame_);

		void Update( const GameTime& gameTime_ ) override = 0;

	private:
		int m_DrawOrder;		
	};

}

#endif
