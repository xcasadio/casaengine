
#ifndef _LINE2DRENDERERCOMPONENT_H_
#define _LINE2DRENDERERCOMPONENT_H_

#include "CA_Export.h"



#include "GameTime.h"
#include "DrawableGameComponent.h"
#include "Maths/Vector2.h"

#include "Graphics/Color.h"
#include "Memory/ObjectPool.h"

#include <vector>
#include <bgfx/bgfx.h>


namespace CasaEngine
{
	class Game;

	/////////////////////////////////////////////////////////////
	/// CLine2DRendererComponent
	/////////////////////////////////////////////////////////////
	class CA_EXPORT Line2DRendererComponent :
		public DrawableGameComponent
	{
	private:
		/**
		 * 
		 */
		class LineRenderer2DData : 
			public ObjectPool<LineRenderer2DData>
		{
		public:
			Vector2F Start, End;
			unsigned long StartColor, EndColor;
		};

	public:
		Line2DRendererComponent(Game* pGame_);
		virtual ~Line2DRendererComponent();

		virtual void OnLoadContent();
		virtual void Update( const GameTime& gameTime_ );
		virtual void Draw();

		/**
		 * Add line
		 */
		void AddLine(const Vector2F &start_, const CColor &startColor_,
			const Vector2F &end_, const CColor &endColor_);

		/**
		 * Add line
		 */
		void AddLine(const Vector2F &start_, const unsigned int &startColor_,
			const Vector2F &end_, const unsigned int &endColor_);
		
	private:
		void BuildVB();

	private:
		bgfx::DynamicVertexBufferHandle m_VertexBuffer;
		std::vector<LineRenderer2DData *> m_Lines;
		bool m_bRecomputeVB;
		unsigned int m_NbLines;

		//bgfx::ProgramHandle m_pEffect;
	};

}

#endif // _LINE2DRENDERERCOMPONENT_H_
