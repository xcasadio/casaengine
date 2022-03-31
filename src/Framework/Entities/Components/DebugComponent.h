#ifndef DebugComponent_H_
#define DebugComponent_H_

#include "CA_Export.h"
#include "Game/Line3DRendererComponent.h"

namespace CasaEngine
{
	class CA_EXPORT DebugComponent :
		public Component
	{
	public:
		DebugComponent(BaseEntity* pEntity_);
		virtual ~DebugComponent();
		
		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		bool DisplayPosition() const;
		void DisplayPosition(bool val);

		
	private:
		bool m_DisplayPosition;
		Line3DRendererComponent* m_LineRenderer;
	};
}

#endif