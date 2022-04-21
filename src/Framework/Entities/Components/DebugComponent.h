#pragma once

#include "CA_Export.h"
#include "Game/Line3DRendererComponent.h"

namespace CasaEngine
{
	class CA_EXPORT DebugComponent :
		public Component
	{
	public:
		DebugComponent(BaseEntity* pEntity_);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		bool DisplayPosition() const;
		void DisplayPosition(bool val);
		bool DisplayAnimation2DCollisions() const;
		void DisplayAnimation2DCollisions(bool val);

	private:
		bool m_DisplayPosition;
		bool m_DisplayAnimation2DCollisions;
		Line3DRendererComponent* m_LineRenderer;
	};
}
