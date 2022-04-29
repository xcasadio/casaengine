#pragma once

#include "CA_Export.h"

#include "AI/Messaging/Telegram.h"
#include "GameTime.h"

namespace CasaEngine
{
	class BaseEntity;

	class CA_EXPORT Component
	{
	public:
		virtual ~Component();

		virtual void Initialize() = 0;
		virtual void Update(const GameTime& gameTime_) = 0;
		virtual void Draw();
		virtual bool HandleMessage(const Telegram& msg);
		
		BaseEntity* GetEntity();
		int Type() const;

#if EDITOR
		virtual void ShowDebugWidget();
#endif

	protected:
		Component(BaseEntity* entity, int type);

	private:
		BaseEntity* m_pEntity;
		int m_Type;
	};

}
