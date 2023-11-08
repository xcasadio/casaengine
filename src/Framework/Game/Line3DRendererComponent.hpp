#pragma once

#include "CA_Export.hpp"

#include  "GameTime.hpp"
#include  "DrawableGameComponent.hpp"
#include  "Maths/Vector3.hpp"

#include  "Graphics/Color.hpp"
#include <vector>

#include <bgfx/bgfx.h>
#include  "Graphics/Effects/Program.hpp"

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
			Vector3 Start, End;
			unsigned long StartColor, EndColor;
		};

	public:
		Line3DRendererComponent(Game* pGame_);
		~Line3DRendererComponent() override;

		void OnLoadContent() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		void AddLine(const Vector3& start_, const Vector3& end_, const Color& color_);
		void AddLine(const Vector3& start_, const Vector3& end_, const unsigned int color_);
		void AddLine(const Vector3& start_, const Color& startColor_, const Vector3& end_, const Color& endColor_);
		void AddLine(const Vector3& start_, const unsigned int& startColor_, const Vector3& end_, const unsigned int& endColor_);

	private:
		void BuildVB();

		Program* m_pProgram;
		bgfx::DynamicVertexBufferHandle m_VertexBuffer;
		std::vector<LineRenderer3DData*> m_Lines;
		bool m_bRecomputeVB;
		unsigned int m_NbLines;
	};

}