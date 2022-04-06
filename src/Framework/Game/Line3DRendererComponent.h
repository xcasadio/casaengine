#ifndef _LINE3DRENDERERCOMPONENT_H_
#define _LINE3DRENDERERCOMPONENT_H_

#include "CA_Export.h"

#include "GameTime.h"
#include "DrawableGameComponent.h"
#include "Maths/Vector3.h"

#include "Graphics/Color.h"
#include <vector>

#include <bgfx/bgfx.h>
#include "Graphics/Effects/Program.h"

namespace CasaEngine
{
	class Game;

	class CA_EXPORT Line3DRendererComponent :
		public DrawableGameComponent
	{
	private:
		class LineRenderer3DData
		{
		public:
			Vector3F Start, End;
			unsigned long StartColor, EndColor;
		};

	public:
		Line3DRendererComponent(Game* pGame_);
		~Line3DRendererComponent() override;

		void OnLoadContent() override;
		void Update( const GameTime& gameTime_ ) override;
		void Draw() override;

		void AddLine(const Vector3F& start_, const Vector3F& end_, const CColor& color_);
		void AddLine(const Vector3F& start_, const Vector3F& end_, const unsigned int color_);
		void AddLine(const Vector3F &start_, const CColor &startColor_, const Vector3F &end_, const CColor &endColor_);
		void AddLine(const Vector3F &start_, const unsigned int &startColor_, const Vector3F &end_, const unsigned int &endColor_);
		
	private:
		void BuildVB();

		Program *m_pProgram;
		bgfx::DynamicVertexBufferHandle m_VertexBuffer;
		std::vector<LineRenderer3DData *> m_Lines;
		bool m_bRecomputeVB;
		unsigned int m_NbLines;
	};

}

#endif
