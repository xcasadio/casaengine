#pragma once

#include "CA_Export.hpp"

#include  "GameTime.hpp"
#include  "DrawableGameComponent.hpp"
#include  "Maths/Vector2.hpp"

#include  "Graphics/Color.hpp"

#include <vector>
#include <bgfx/bgfx.h>

namespace CasaEngine
{
	class Game;

	class CA_EXPORT Line2DRendererComponent :
		public DrawableGameComponent
	{
	private:
		class LineRenderer2DData
		{
		public:
			Vector2 Start, End;
			unsigned long StartColor, EndColor;
		};

	public:
		Line2DRendererComponent(Game* pGame_);
		~Line2DRendererComponent() override;

		void OnLoadContent() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		void AddLine(const Vector2& start_, const Color& startColor_, const Vector2& end_, const Color& endColor_);
		void AddLine(const Vector2& start_, const unsigned int& startColor_, const Vector2& end_, const unsigned int& endColor_);

	private:
		void BuildVB();

	private:
		bgfx::DynamicVertexBufferHandle m_VertexBuffer{};
		std::vector<LineRenderer2DData*> m_Lines;
		bool m_bRecomputeVB;
		unsigned int m_NbLines;

		//bgfx::ProgramHandle m_pEffect;
	};

}