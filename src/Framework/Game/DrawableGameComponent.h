
#ifndef _DRAWABLEGAMECOMPONENT_H_
#define _DRAWABLEGAMECOMPONENT_H_

#include "CA_Export.h"
#include "GameComponent.h"
#include "GameTime.h"

namespace CasaEngine
{
	class Game;

	/////////////////////////////////////////////////////////////
	/// CDrawableGameComponent
	/////////////////////////////////////////////////////////////
	class CA_EXPORT DrawableGameComponent :
		public IGameComponent
	{
	public:
		virtual void OnLoadContent();
		virtual void Draw() = 0;

		int DrawOrder() const;
		void DrawOrder(int val);

		//EventHandler<int> DrawOrderChanged;

	protected :
		DrawableGameComponent(Game* pGame_);
		virtual ~DrawableGameComponent();

		virtual void Update( const GameTime& gameTime_ ) = 0;

	private:
		int m_DrawOrder;		
	};

}

#endif // _DRAWABLEGAMECOMPONENT_H_
