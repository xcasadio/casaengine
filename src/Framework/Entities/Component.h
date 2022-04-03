#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "CA_Export.h"

#include "AI/Messaging/Telegram.h"
#include "GameTime.h"

#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	class BaseEntity;

	class CA_EXPORT Component :
		public AllocatedObject<Component>
	{
	public:
		virtual ~Component();

		int Type() const;

		virtual bool HandleMessage(const Telegram& msg);

		virtual void Initialize() = 0;
		virtual void Update(const GameTime& gameTime_) = 0;
		virtual void Draw();
		
		BaseEntity* GetEntity();

		//Editor
		virtual void ShowDebugWidget();

	protected:
		Component(BaseEntity* pEntity_, int type_);

	private:
		BaseEntity* m_pEntity;
		int m_Type;
	};

}

#endif
